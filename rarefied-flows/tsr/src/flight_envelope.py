import numpy as np
import pandas as pd

class FlightEnvelope:
    """Holds data structures and methods for producing simulation data for a given flight envelope"""


    def __init__(self):

        # Set up envelope parameters. 
        print('Set Altitude Values')
        h_lower = int(input('Lower Bound '))
        h_upper = int(input('Upper Bound '))
        h_values = int(input('Number of Values '))
        self.h = list(np.linspace(h_lower, h_upper, h_values))

        print('Set Mach Numbers Values')
        Ma_lower = float(input('Lower Bound '))
        Ma_upper = float(input('Upper Bound '))
        Ma_values = int(input('Number of Values '))
        self.Ma = list(np.linspace(Ma_lower, Ma_upper, Ma_values))

        self.f = int(input('Enter level of mesh fidelity '))
        self.t = float(input('Enter simulation duration '))

    # Set up dataframe that holds the unique cases. 
    def setup_envelope(self):

      labels = pd.Index(['Ma', 'h', 'T', 'P', 'rho', 'u', 'Re', 'Kn', 'data'])
      U = len(self.Ma) * len(self.h)

      print(len(self.Ma), len(self.h))
      print(U)
      self.df = pd.DataFrame(np.zeros(shape = (len(fe.Ma) * len(fe.h), 9)))
      self.df.columns = labels


fe = FlightEnvelope()
fe.setup_envelope()
print(fe.df)

