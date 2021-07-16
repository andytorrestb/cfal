from meta_data_generator import MetaDataGenerator
import case_coordinates as cc

for n_vals in range(100):
    Ma_params = { 'lower' : 1, 'upper' : 5, 'vals' : n_vals }
    h_params = { 'lower' : 1000, 'upper' : 100000, 'vals' : n_vals }
    L_params = { 'lower' : 1, 'upper' : 3, 'vals' :  n_vals }
    H_params = { 'lower' : 1, 'upper' : 1, 'vals' : n_vals }
    params = { 'Ma' : Ma_params, 'h' : h_params,'L' : L_params, 'H' : H_params }

    data = MetaDataGenerator(params)
    print('n_vals ', n_vals, 'shape ', data.df.shape)
    print()