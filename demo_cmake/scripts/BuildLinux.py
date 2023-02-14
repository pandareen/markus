import sys,subprocess

projectName = sys.argv[1].replace("deps/", "").replace("/", "")

if len(sys.argv) < 3:
    buildType = 'Debug'
else:
    buildType : str = sys.argv[2]


subprocess.check_call(['docker-compose', 'run' ,'--rm' ,'--use-aliases', '--service-ports', 'farm', 'python3', 'scripts/Build.py', projectName, buildType])
