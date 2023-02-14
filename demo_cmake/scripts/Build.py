import sys
from classes.EnvironmentFactory import EnvironmentFactory

projectName = sys.argv[1].replace("deps/", "").replace("/", "")

if len(sys.argv) < 3:
    buildType = 'Debug'
else:
    buildType : str = sys.argv[2]

environment = EnvironmentFactory(projectName).create()

environment.build('All', buildType)