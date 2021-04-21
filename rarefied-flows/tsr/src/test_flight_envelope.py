import unittest
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


if __name__ == '__main__':
    unittest.main()