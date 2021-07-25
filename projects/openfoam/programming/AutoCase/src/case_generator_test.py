import os
from meta_data_generator import MetaDataGenerator

# Parameters for generating lists used to build cases.
Ma_params = { 'lower' : 1, 'upper' : 5, 'vals' : 10 }
h_params = { 'lower' : 1000, 'upper' : 100000, 'vals' : 10 }
L_params = { 'lower' : 1, 'upper' : 3, 'vals' : 3 - 1 + 1 }
H_params = { 'lower' : 1, 'upper' : 1, 'vals' : 3 - 1 + 1 }
params = { 'Ma' : Ma_params, 'h' : h_params, 'L' : L_params, 'H' : H_params }

# Generate DataFrame containing simulation parameters.
meta_data = MetaDataGenerator(parameters=params)

# # Structure case directories according to records in meta_data
# MetaDataGenerator.make_case_dirs(meta_data)
# 
# # Contains all parameters used to generate unique cases.
# meta_data.df

print(meta_data.df)


# Commented out IPython magic to ensure Python compatibility.

from jinja2 import Environment, FileSystemLoader
from math import tan

# Function to make directories
def make_case_dir(path, record):
  """ Given a path of correct format. Build a case direcory at the given
      location.  
  """
  setup_0_dir(path, record)
  setup_constant_dir(path, record)
  setup_system_dir(path, record)

# Sets up constant folder. 
def setup_constant_dir(path, record):
  # Load template.
  file_loader = FileSystemLoader('case/constant')
  env = Environment(loader = file_loader)
  template = env.get_template('dsmcProperties')

  # Set parameters.
  n_rho = {"O2" : record['rho']}

  # Write to file.
  target_text = template.render(n_rho = n_rho)
  dest_path = path + '/constant/dsmcProperties'
  os.system("mkdir " + path + "/constant")
  open(dest_path, "w").write(target_text)

def get_x_vals(record):
  x_vals = []
  x_data = []

  # Origin
  x_vals.append(0)

  # Front of cavity
  x_vals.append(10)
  x_vals.append(10 * ( 1 + 1 / tan(record['theta'])))

  # Back of cavity
  x_vals.append(10 * ( 1 + 1 / tan(record['theta']) + record['L']))
  x_vals.append(10 * ( 2 + 1 / tan(record['theta']) + record['L']))

  for x in range(len(x_vals)):
    x_data.append({'n_x' : x, 'x_val' : x_vals[x]})

  return x_data

def get_y_vals(record):
  y_vals = []
  y_data = []
  y_vals.append(0)
  y_vals.append(10)
  y_vals.append(3 * 10)

  for y in range(len(y_vals)):
    y_data.append({'n_y' : y, 'y_val' : y_vals[y]})

  return y_data

def get_r_vals(record):
  r_vals = []
  r_data = []
  r_vals.append(5)
  r_vals.append(2 * 5)
  r_vals.append(record['L'] * 5)

  for r in range(len(r_vals)):
    r_data.append()
  return r_vals
   
def get_mesh_params(record):
  # TODO: Convert vals variables to dictionaries.
  r_vals = get_r_vals(record)
  y_vals = get_y_vals(record)
  x_vals = get_x_vals(record)
  params = {'x' : x_val, 'y': y_vals, 'r': r_vals}
  return params

def setup_system_dir(path, record):
  # make directory
  system_path = path + "/system"
  os.system("mkdir " + system_path)

  # Load templates.
  file_loader = FileSystemLoader('case/system')
  env = Environment(loader = file_loader)
  blockMeshDict = env.get_template('blockMeshDict')
  controlDict = env.get_template('controlDict')
  decomposeParDict = env.get_template('decomposeParDict')  
  dsmcInitialiseDict = env.get_template('dsmcInitialiseDict')
  fvSchemes = env.get_template('fvSchemes')
  fvSolution = env.get_template('fvSolution')

  # Set parameters.
  blockMesh_param = get_mesh_params(record)

  # Render templates. 
  

  # Write to file. 
  open(system_path + "/blockMeshDict", "w").write(blockMeshDict.render())
  open(system_path + "/controlDict", "w").write(controlDict.render())
  open(system_path + "/decomposeParDict", "w").write(decomposeParDict.render())
  open(system_path + "/dsmcInitialiseDict", "w").write(dsmcInitialiseDict.render())
  open(system_path + "/fvSchemes", "w").write(fvSchemes.render())
  open(system_path + "/fvSolution", "w").write(fvSolution.render())

def setup_0_dir(path, record):
  # make directory
  path_0 = path + "/0"
  os.system("mkdir " + path_0)

  # Load templates.
  file_loader = FileSystemLoader('case/0')
  env = Environment(loader = file_loader)
  boundaryT = env.get_template('boundaryT')
  boundaryU = env.get_template('boundaryU')
  dsmcRhoN = env.get_template('dsmcRhoN')
  fD = env.get_template('fD')
  iDof = env.get_template('iDof')
  internalIE = env.get_template('internalE')
  linearKE = env.get_template('linearKE')
  momentum = env.get_template('momentum')
  q = env.get_template('q')
  rhoM = env.get_template('rhoM')
  rhoN = env.get_template('rhoN')

  # Write to file. 
  open(path_0 + "/boundaryT", "w").write(boundaryT.render())
  open(path_0 + "/boundaryU", "w").write(boundaryU.render())
  open(path_0 + "/dsmcRhoN", "w").write(dsmcRhoN.render())
  open(path_0 + "/fD", "w").write(fD.render())
  open(path_0 + "/iDof", "w").write(iDof.render())
  open(path_0 + "/internalE", "w").write(internalIE.render())
  open(path_0 + "/linearKE", "w").write(linearKE.render())
  open(path_0 + "/momentum", "w").write(momentum.render())
  open(path_0 + "/q", "w").write(q.render())
  open(path_0 + "/rhoM", "w").write(rhoM.render())
  open(path_0 + "/rhoN", "w").write(rhoN.render())
  
# IN DEVELOPMENT: Code to loop through each record, 
# and generate the appropriate case.
for index, row in meta_data.df.iterrows():
  path_of_row = str(row['h']) + '/' + str(row['Ma']) + '/' + str(row['L']) + '/' + str(row['H']) + '/' + str(row['theta'])
  # make_case_dir(path_of_row, row)
  print('for index = ', index)
  print("      ", get_x_vals(row), row['L'], row['theta'])
  print("      ", get_y_vals(row), row['H'])


