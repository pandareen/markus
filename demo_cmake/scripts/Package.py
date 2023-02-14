import sys


from classes.EnvironmentFactory import EnvironmentFactory


projectName = sys.argv[1].replace("deps/", "").replace("/", "")

if len(sys.argv) < 3:
    version = '1.0.0'
else:
    version : str = sys.argv[2]
    
environment = EnvironmentFactory(projectName).create()

environment.build('All', 'Release')
environment.createPackage(version)






