import pandas as pd
import numpy as np
from math import sqrt, exp
import os

# Helper functions for calculating necessary physical properties.
def T(h):
  """ Defines temperature as a function of altitude
      according to NASA's atmopsheripic models.

      h (meters)
      T (celcius)
  """
  # Tropshpere
  if h < 11000:
    return 273.1 + 15.04 - 0.00649 * h
  # Lower Stratoshpere
  elif h < 25000:
    return -56.46 + 273.1
  # Upper Stratosphere
  else:
    return 273.1 - 131.21 + 0.00299 * h

def P(T, h):
  """ Defines pressure as a function of altitude and temperature
      according to NASA's atmopsheripic models.
  """
  # Tropshpere
  if h < 11000:
    return 101.29 * (T / 288.08) ** 5.256
  # Lower Stratoshpere
  elif h < 25000:
    return 22.65 * exp(1.73 - 0.000157 * h)
  # Upper Stratosphere
  else:
    return 2.488 * (216.6 / T) ** 11.388

def u(Ma, T):
  """ Defines velocity as a function of Mach Number and temperature.
      According to the definition of Mach Number. 
  """
  # Assumed at STP conditions for gamma. aka bad assumption
  gamma = 1.4 
  R = 286.9
  return Ma * sqrt(gamma * R * T)

def rho(P, T):
  """ Defines density (rho) as a function of Pressure (P) and
      Temperature (T) according to the perfect gas law. 
  """
  return P / (0.2869 * T)

# Function to make directories
def make_case_dirs(path):
  """ Given a path of correct format. Build a case direcory at the given
      location.  
  """
  setup_initial_conditions(path)
  setup_constant_dir(path)
  setup_system_dir(path)



class MetaDataGenerator:
  """ Generates all the required meta data for producing cases at different
      flight conditions and geometric configurations of an external cavity.
      Pleases refer to pseucode.txt for in depth description of the variables.
  """

  def __init__(self):
    """ If given no parameters, program will prompt user with required data
    """
    print('Set Range of Altitude Values')
    h_lower = int(input('Lower Bound '))
    h_upper = int(input('Upper Bound '))
    h_vals = int(input('Number of Values '))
    self.h_range = list(np.linspace(h_lower, h_upper, h_vals))
  
    print('Set Range of Mach Number Values')
    Ma_lower = float(input('Lower Bound '))
    Ma_upper = float(input('Upper Bound '))
    Ma_vals = int(input('Number of Values '))
    self.Ma_range = list(np.linspace(Ma_lower, Ma_upper, Ma_vals))

    # For geometric properties, n_vals is fixed according to the bounds
    print('Set Range of Length To Depth Ratios ')
    L_lower = int(input("Lower Bound "))
    L_upper = int(input("Upper Bound "))
    L_vals = (L_upper - L_lower) + 1
    self.L_range = list(np.linspace(L_lower, L_upper, L_vals))

    print('Set Range of Rear To Leading Wall Height Ratios ')
    R_lower = int(input("Lower Bound "))
    R_upper = int(input("Upper Bound "))
    R_vals = (R_upper - R_lower) + 1
    self.R_range = list(np.linspace(R_lower, R_upper, R_vals))

    # Don't want to give the user the option for now
    # Theta values are fixed as follows. 
    #                   (90, 60, 57.296, 30, 15)  (degrees)
    self.theta_range = [1.57, 1.0472, 1, 0.5236, 0.2618] # radians

    self.setup_table()
  
  def __init__(self, parameters):
    """ 
      parameters is a dictionary with the following form.

      { 'Ma' : Ma_params, 'h' : h_params, 'L' : L_params, 'H' : H_params }

      Where all the X_params are dictionaries of the following form. 

      { 'upper' : u_val, 'lower' : l_val, 'vals' : n_vals }

    """

    self.Ma_range = list(np.linspace(
        parameters['Ma']['lower'],
        parameters['Ma']['upper'],
        parameters['Ma']['vals']
    ))

    self.h_range = list(np.linspace(
        parameters['h']['lower'],
        parameters['h']['upper'],
        parameters['h']['vals']
    ))

    self.L_range = list(np.linspace(
        parameters['L']['lower'],
        parameters['L']['upper'],
        parameters['L']['vals']
    ))

    self.H_range = list((np.linspace(
        parameters['H']['lower'],
        parameters['H']['upper'],
        parameters['H']['vals']
    )))

    self.theta_range = [1.57, 1.0472, 1.0, 0.5236, 0.2618] # radians

    self.setup_table()


  def setup_table(self):
    """ Helper function for constructor. what else ????
    """
    labels = pd.Index(['h', 'Ma', 'T', 'P', 'rho', 'u', 'L', 'H', 'theta'])
    n_records = len(self.H_range) * len(self.L_range) * len(self.theta_range)
    n_records = n_records * len(self.h_range) * len(self.Ma_range)
    shape = (n_records, len(labels))
    self.df = pd.DataFrame(np.zeros(shape = (n_records, len(labels))))
    self.df.columns = labels
    self.calculate_meta_data()
    # Apperently the for loop makes 66% duplicate data
    # The following cleans that out.  
    self.df = self.df.drop_duplicates()
    self.df = pd.DataFrame(np.array(self.df)) # reset index
    self.df.columns = labels

  def calculate_meta_data(self):
      record = 0 # looping through every recod
      for h in self.h_range:
        for Ma in self.Ma_range:
          for L in self.L_range:
            for H in self.H_range:
              for theta in self.theta_range:
                  # Once inside the record, loop through the features. 
                  for feature in self.df.columns:
                    if feature == 'h':
                      self.df[feature][record] = h
                    if feature == 'Ma':
                      self.df[feature][record] = Ma
                    if feature == 'T':
                      self.df[feature][record] = T(h)
                    if feature == 'P':
                      self.df[feature][record] = P(T(h), h)
                    if feature == 'rho':
                      self.df[feature][record] = rho(P(T(h), h), T(h)) 
                    if feature == 'u': 
                      self.df[feature][record] = u(Ma, T(h))
                    if feature == 'L':
                      self.df[feature][record] = L
                    if feature == 'H':
                      self.df[feature][record] = H
                    if feature == 'theta':
                      self.df[feature][record] = theta
                  record += 1

  def make_case_dirs(self):
      for h in self.h_range:
        os.system("mkdir " + str(h))
        for Ma in self.Ma_range:
          os.system("mkdir " + str(h) + "/" + str(Ma))
          for L in self.L_range:
            os.system("mkdir " + str(h) + "/" + str(Ma) + "/" + str(L))  
            for H in self.H_range:
              os.system("mkdir " + str(h) + "/" + str(Ma) + "/" + str(L) + "/" + str(H))
              for theta in self.theta_range:
                os.system("mkdir " + str(h) + "/" + str(Ma) + "/" + str(L) + "/" + str(H) + "/" + str(theta))