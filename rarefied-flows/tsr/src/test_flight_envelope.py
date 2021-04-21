import unittest
import flight_envelope

class TestCalc(unittest.TestCase):

    def test_add(self):
        result  = flight_envelope.add(10, 5)
        self.assertEqual(result, 15)


if __name__ == '__main__':
    unittest.main()