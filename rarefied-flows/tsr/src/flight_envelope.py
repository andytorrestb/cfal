import numpy as np

class FlightEnvelope:
    """Holds data structures and methods for producing simulation data for a given flight envelope"""

    def __init__(self):

        print('Set Altitude Values')
        h_lower = int(input('Lower Bound '))
        h_upper = int(input('Upper Bound '))
        h_values = int(input('Number of Values '))
        self.h = list(np.linspace(h_lower, h_upper, h_values))

        
        print('Set Mach Numbers Values')
        Ma_lower = float(input('Lower Bound '))
        Ma_upper = float(input('Upper Bound '))
        Ma_values = int(input('Number of Values '))
        self.Ma = list(np.arange(Ma_lower, Ma_upper, Ma_values))

        
        self.f = int(input('Enter level of mesh fidelity '))
        self.t = float(input('Enter simulation duration '))

