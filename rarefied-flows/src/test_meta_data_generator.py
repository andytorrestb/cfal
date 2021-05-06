import unittest
from meta_data_generator import MetaDataGenerator

class TestMetaDataGenerator(unittest.TestCase):

    def test_innit(self):
        Ma_params = { 'lower' : 1, 'upper' : 5, 'vals' : 10 }
        h_params = { 'lower' : 1000, 'upper' : 100000, 'vals' : 10 }
        L_params = { 'lower' : 1, 'upper' : 3, 'vals' : 3 - 1 + 1 }
        H_params = { 'lower' : 1, 'upper' : 1, 'vals' : 3 - 1 + 1 }
        params = { 'Ma' : Ma_params, 'h' : h_params, 'L' : L_params, 'H' : H_params }

        data = MetaDataGenerator(params)

        self.assertEqual(data.df.shape, (1500, 9))



if __name__ == '__main__':
    unittest.main()