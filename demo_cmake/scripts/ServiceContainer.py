import subprocess,shutil
import sys, os

from classes.EnvironmentFactory import EnvironmentFactory

version = '1.0.0'
projectName = sys.argv[1].replace("deps/", "").replace("/", "")
environment = EnvironmentFactory(projectName).create()

subprocess.check_call(['docker-compose', 'run' ,'--rm' ,'--use-aliases', '--service-ports', 'farm', 'python3', 'scripts/Build.py', 'quazip', 'Release'])
subprocess.check_call(['docker-compose', 'run' ,'--rm' ,'--use-aliases', '--service-ports', 'farm', 'python3', 'scripts/Build.py', 'Framework', 'Release'])

subprocess.check_call(['docker-compose', 'run' ,'--rm' ,'--use-aliases', '--service-ports', 'farm', 'python3', 'scripts/Package.py', projectName])

appImageName = projectName + '-' + version + '-x86_64.AppImage'
appImagePath    = os.path.join(environment.getLinuxDeployPath() ,  appImageName)
runServicePath  = os.path.join(environment.getDockerFolderPath() ,  'RunService')
appImageOutPath = os.path.join(runServicePath, 'service.AppImage')

if os.path.exists(appImageOutPath):
   os.remove(appImageOutPath)

shutil.copy(appImagePath, appImageOutPath)

subprocess.check_call(['docker', 'build', runServicePath, '-t', projectName.lower() + ':' + version])

os.remove(appImageOutPath)
#subprocess.check_call('docker system prune -a')
