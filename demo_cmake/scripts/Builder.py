import sys, os, string, subprocess
from prompt_toolkit import prompt
from prompt_toolkit.completion import WordCompleter

arrPaths =[]
arrNames =[]

for file in os.listdir('deps/'):
    path = os.path.join('deps', file, 'Service')
    if os.path.exists(path):
        arrPaths.append(path)
        arrNames.append(file)

hasOnlyOneProject = len(arrNames) == 1

if hasOnlyOneProject:
    defaultInput = arrNames[0]
else:
    defaultInput = ''

project_completer = WordCompleter(arrNames, ignore_case=True)
project_selection = prompt('Use project:', default=defaultInput, completer=project_completer)


build_type = WordCompleter([ 'Debug', 'Release', 'Docker Linux(Release)', 'Docker Linux(Debug)'])

file_selection = prompt('Enter build type: ', default='Docker Linux(Debug)', completer=build_type)

if file_selection == 'Debug':
    subprocess.check_call([sys.executable, 'scripts/BuildAndTest.py', project_selection,'All', build_type])
elif file_selection == 'Release':
    subprocess.check_call([sys.executable, 'scripts/BuildAndTest.py', project_selection,'All', build_type])
elif file_selection == 'Docker Linux(Release)':
    subprocess.check_call(['export MSYS_NO_PATHCONV=1; docker-compose run --rm --use-aliases --service-ports farm sudo python3 scripts/BuildAndTest.py', project_selection, 'All', 'Release'])
elif file_selection == 'Docker Linux(Debug)':                                                                                               
    subprocess.check_call(['export MSYS_NO_PATHCONV=1; docker-compose run --rm --use-aliases --service-ports farm sudo python3 scripts/BuildAndTest.py', project_selection, 'All','Debug'])