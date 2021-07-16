import unittest
from meta_data_generator import MetaDataGenerator

class TestMetaDataGenerator(unittest.TestCase):

    def test_innit(self):

        for n_vals in range(9):
            Ma_params = { 'lower' : 1, 'upper' : 5, 'vals' : n_vals }
            h_params = { 'lower' : 1000, 'upper' : 100000, 'vals' : n_vals }
            L_params = { 'lower' : 1, 'upper' : 3, 'vals' :  n_vals }
            H_params = { 'lower' : 1, 'upper' : 1, 'vals' : n_vals }
            params = { 'Ma' : Ma_params, 'h' : h_params,'L' : L_params, 'H' : H_params }

            data = MetaDataGenerator(params)

            self.assertEqual(len(data.Ma_range), Ma_params['vals'])   
            self.assertEqual(len(data.h_range), h_params['vals'])
            self.assertEqual(len(data.L_range), L_params['vals'])     
            self.assertEqual(len(data.H_range), H_params['vals'])
            self.assertEqual(data.df.shape, (5 * n_vals ** 3, 9))

            

if __name__ == '__main__':
    unittest.main()