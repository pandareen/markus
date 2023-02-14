import sys
from classes.EnvironmentFactory import EnvironmentFactory

projectName = sys.argv[1].replace("deps/", "").replace("/", "")
buildType = sys.argv[2]

environment = EnvironmentFactory(projectName).create()

environment.runAllTests(buildType)


