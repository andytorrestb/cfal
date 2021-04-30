"""
  Class that contains the meta-data that describes the 
  physical parameters used for producing all the unique casespyt
  within a given "flight envelope". This flight envelope is 
  contained in a tensor that takes a discrete range of 
  Mach numbers (self.Ma_range) and altitude values (self.h_range)
  as input for defining the flow regime to study. 
"""

import numpy as np
import pandas as pd
from math import exp
from math import sqrt

# Helper functions for calculating necessary physical properties.
def T(h):
  """ Defines temperature as a function of altitude
      according to NASA's atmospheric models.

      h (meters)
      T (celcius)
  """
  # Troposphere
  if h < 11000:
    return 273.1 + 15.04 - 0.00649 * h
  # Lower Stratosphere
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
  """
  # Assumed at STP conditions for gamma. aka bad assumption
  gamma = 1.4 
  R = 286.9
  return Ma * sqrt(gamma * R * T)

def rho(P, T):
  """ Defines density (rho) as a function of Pressure (P) and
      Temperature (T) according to the perfect gas law equation. 
  """
  return P / (0.2869 * T)

class FlightEnvelope:
    """Holds data structures and methods for producing simulation
        data for a given flight envelope
    """

    # Default constructor.
    def __init__(self):
      """Sets up basic meta data used to produce cases with varying 
          degree of rarefication accoring to a range of height (h) values,
      """
      # Set up envelope parameters.
      print('Set Altitude Values')
      h_lower = int(input('Lower Bound '))
      h_upper = int(input('Upper Bound '))
      h_values = int(input('Number of Values '))
      self.h_range = list(np.linspace(h_lower, h_upper, h_values))

      print('Set Mach Number Values')
      Ma_lower = float(input('Lower Bound '))
      Ma_upper = float(input('Upper Bound '))
      Ma_values = int(input('Number of Values '))
      self.Ma_range = list(np.linspace(Ma_lower, Ma_upper, Ma_values))

      self.f = int(input('Enter level of mesh fidelity '))
      self.t = float(input('Enter simulation duration '))

      self.setup_envelope()


    def calculate_meta_data(self):      
      # Calculate appropriate met data for each record in the DataFrame.
      i = 0
      for Ma in self.Ma_range:
        for h in self.h_range:
          # Calculate data for each feature in the record.
          for feature in self.df.columns:
            if feature == 'Ma':
              self.df[feature][i] = Ma
            if feature == 'h':
              self.df[feature][i] = h
            if feature == 'T':
              self.df[feature][i] = T(h)
            if feature == 'P':
              self.df[feature][i] = P(self.df['T'][i], h)
            if feature == 'rho':
              self.df[feature][i] = rho(self.df['P'][i], self.df['T'][i]) 
            if feature == 'u': 
              self.df[feature][i] = u(Ma, self.df['T'][i])
          i += 1

    # Set up dataframe that holds the meta data for unique cases. 
    def setup_envelope(self):
      labels = pd.Index(['Ma', 'h', 'T', 'P', 'rho', 'u', 'data'])
      n_records = len(self.Ma_range) * len(self.h_range)
      self.df = pd.DataFrame(np.zeros(shape = (n_records, len(labels))))
      self.df.columns = labels
      self.calculate_meta_data()

fe = FlightEnvelope()
print(fe.df)
print(fe.df.drop_duplicates())
