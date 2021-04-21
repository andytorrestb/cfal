import unittest
import pandas as pdpip
from flight_envelope import FlightEnvelope

class TestFlightEnvelope(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        print('setupClass')

    @classmethod
    def tearDownClass(cls):
        print('teardownClass')

    def setUp(self):
        print('setUp')
        self.fe_1 = FlightEnvelope()

    def test_init(self):
        self.assertIsInstance(self.fe_1.h, list, '')
        self.assertIsInstance(self.fe_1.Ma, list, '')
        self.assertIsInstance(self.fe_1.f, int, '')
        self.assertIsInstance(self.fe_1.t, float, '')

    def test_setup_envelope(self):
      
      fe = self.fe_1
      fe.setup_envelope()

      labels = pd.Index(['Ma', 'h', 'T', 'P', 'rho', 'u', 'Re', 'Kn', 'data'])
      U = (len(fe.Ma * fe.h), len(labels))

      self.assertIsInstance(fe.df, pd.DataFrame, '')
      self.assertEqual(U, fe.df.columns)
      self.assertEqual(labels, fe.df.shape)



if __name__ == '__main__':
    unittest.main()