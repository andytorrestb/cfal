from meta_data_generator import MetaDataGenerator
import case_coordinates as cc
from jinja2 import FileSystemLoader

# Parameters for generating lists used to build cases.
Ma_params = { 'lower' : 1, 'upper' : 5, 'vals' : 10 }
h_params = { 'lower' : 1000, 'upper' : 100000, 'vals' : 10 }
L_params = { 'lower' : 1, 'upper' : 3, 'vals' : 3 - 1 + 1 }
H_params = { 'lower' : 1, 'upper' : 1, 'vals' : 3 - 1 + 1 }
params = { 'Ma' : Ma_params, 'h' : h_params, 'L' : L_params, 'H' : H_params }

# Generate DataFrame containing simulation parameters.
meta_data = MetaDataGenerator(parameters=params)

meta_data.make_case_dirs()

cc.get_coordinates(meta_data)

def path_of_row(row):
    return str(row['h']) + '/' + str(row['Ma']) + '/' + str(row['L']) + '/' + str(row['H']) + '/' + str(row['theta']) 

for index, row in meta_data.df.iterrows():
    path_of_row = path_of_row(row)
    cc.setup_0_dir(path_of_row, row)