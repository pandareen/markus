import subprocess,shutil
import sys, os

from classes.EnvironmentFactory import EnvironmentFactory
from classes.Github import Github

version = '1.0.0'
projectName = sys.argv[1].replace("deps/", "").replace("/", "")
environment = EnvironmentFactory(projectName).create()


#subprocess.check_call(['docker-compose', 'run' ,'--rm' ,'--use-aliases', '--service-ports', 'farm', 'python3', 'scripts/Package.py', projectName])

appImageName = projectName + '-' + version + '-x86_64.AppImage'
appImagePath    = os.path.join(environment.getLinuxDeployPath() ,  appImageName)

Github(projectName).createRelease(version, appImagePath,
                    'tryingt out the description markdown poissible ?# The largest heading \
                    ## The second largest heading\n\
                    ###### The smallest heading\n\
                    **big fat texT**\
                    ')
