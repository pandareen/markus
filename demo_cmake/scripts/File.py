import sys, os, string, subprocess
from prompt_toolkit import prompt
from prompt_toolkit.completion import WordCompleter
from prompt_toolkit.styles import Style

def getDatabaseName():
    database_used = prompt('Enter use database: ', default='general')
  
    if database_used == 'general':
          database_var = ''
    else:
          database_var = 'Q_CLASSINFO("database", %s)' % database_used
    return database_var


def createFile(path, data):
    print(path)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    f = open(path, "w")
    f.write(data)
    f.close()   

def createClass(project, folder, name, header, source):
    pathHeader = os.path.join(os.getcwd(), 'deps', project, folder, name + '.h')
    pathSource = os.path.join(os.getcwd(), 'deps', project, folder, name + '.cpp')
    createFile(pathHeader, header)
    createFile(pathSource, source)
    
def addToCmakeListsSetVar(project, variableName, folder, name):
    pathCmake = os.path.join(os.getcwd(), 'deps', project, folder, 'CMakeLists.txt')
    with open(pathCmake) as f:
        filedata = f.read()
    
    find_set_entity = filedata.find('set('+ variableName)
    pos = filedata.find(')', find_set_entity + 1)
    filedata = filedata[:pos-1] + '\n        ' + name + filedata[pos-1:]

    with open(pathCmake, 'w') as f:
        f.write(filedata)      

def addEntityToCmakeLists(project, name):
    addToCmakeListsSetVar(project, 'Entities', 'Domain', name) 

def addApiPathToCmakeLists(project, name):
    addToCmakeListsSetVar(project, 'ApiPaths', 'Service', name)
    
def addUtilityToCmakeLists(project, name):
    addToCmakeListsSetVar(project, 'Utilities', 'Service', name)

def addValueObjects(namesuggestions, valueObject):
    NameSuggestions =[
    'name', 'hash', 
    'created', 'started', 
    'finished', 'url',
    'percentage','isHidden',
    'isDisabled','isVisible', 
    'file', 'audio', 
    'tag', 'tags', 'image','child','parent', 'count'
    'value', 'size', 
    'status']
    lists = ['QList<' + i + '>' for i in namesuggestions]

    ValueObjects =['no', 'int', 'QDateTime', 'bool', 'Hash', 'QTime', 'QString', 'QUrl', 'float']
    ValueObjects+= namesuggestions
    ValueObjects+= valueObject
    ValueObjects+= lists

    value_object_properties = []
    value_objects = []
    value_object_completer = WordCompleter(ValueObjects, match_middle=True, ignore_case=True)
    name_completer = WordCompleter(NameSuggestions, match_middle=True, ignore_case=True)

    while True:
         variable_to_add = prompt('Want to add value object? ',bottom_toolbar=';'.join(ValueObjects), default='no', completer=value_object_completer)
         if variable_to_add == 'no':
             break
         else:
            variable_name = prompt('name? ', completer=name_completer)
            value_object_properties.append('Q_PROPERTY({0} {1} MEMBER {1})'.format(variable_to_add, variable_name) )
            value_objects.append('{0} {1};'.format(variable_to_add, variable_name) )
    return value_objects, value_object_properties

def readTemplate(path, filename):
      path = os.path.join(os.getcwd(), 'scripts', 'templates', path, filename)
      with open(path) as t:
        return string.Template(t.read())
      return ''

def createBaseResourceApiPath(project, entity, base_class =''):
    templateHeader = readTemplate('', 'api_path.h')
    templateSource = readTemplate('', 'api_path.cpp')

    if base_class != '':
        include= base_class + '/'+ entity
    else:
        include = entity

    header = templateHeader.substitute(
        class_name=entity, 
        include_path=include+'.h', 
        project_name=(project+'Service').upper(), 
    )
    source = templateSource.substitute(
        class_name=entity,
    )
    createClass(project, os.path.join('Service', 'ApiPath', base_class), entity, header, source)
    addApiPathToCmakeLists(project, include)
  
def createClassFile(project, folder):
    templateHeader = readTemplate('', 'simple.h')
    templateSource = readTemplate('', 'simple.cpp')

    file_name = prompt('Enter class name: ')

    header = templateHeader.substitute(
        class_name=file_name, 
    )
    source = templateSource.substitute(
        class_name=file_name, 
    )
    createClass(project, folder, file_name, header, source)

def createUtilityFile(project, folder):
    templateHeader = readTemplate('', 'simple.h')
    templateSource = readTemplate('', 'simple.cpp')

    file_name = prompt('Enter class name: ')

    header = templateHeader.substitute(
        class_name=file_name, 
    )
    source = templateSource.substitute(
        class_name=file_name, 
    )
    createClass(project, folder, file_name, header, source)
    addUtilityToCmakeLists(project, file_name)  

def createEntity(project, namesuggestions, valueObject):
    templateHeader = readTemplate('entity', 'normal.h')
    templateSource = readTemplate('entity', 'normal.cpp')

    file_name = prompt('Enter entity name: ')

    database_var = getDatabaseName()
    valueObjects = addValueObjects(namesuggestions, valueObject)

    header = templateHeader.substitute(
        class_name=file_name, 
        project_name=(project+'domain').upper(), 
        class_info=database_var,
        value_objects='\n\t\t'.join(valueObjects[0]),
        value_object_properties='\n\t\t'.join(valueObjects[1]),
    )
    source = templateSource.substitute(
        class_name=file_name, 
    )
    createClass(project, os.path.join('Domain', 'Types', 'Entity'), file_name, header, source)
    createBaseResourceApiPath(project, file_name)
    addEntityToCmakeLists(project,  file_name)
      
def createAbstractEntity(project, namesuggestions, valueObject):
    templateHeader = readTemplate(os.path.join('entity','abstract'), 'baseClass.h')
    templateSource = readTemplate(os.path.join('entity','abstract'), 'baseClass.cpp')
    
    file_name = prompt('Enter abstract entity name: ')

    database_var = getDatabaseName()
    valueObjects = addValueObjects(namesuggestions, valueObject)
    class_types = []

    while True:
         class_type = createSubClassEntity(project, file_name, namesuggestions, valueObject)
         if class_type == '':
             break
         else: class_types.append(class_type)
    
    header = templateHeader.substitute(
        class_name=file_name, 
        project_name=(project+'domain').upper(), 
        class_info=database_var,
        class_types=',\n\t\t'.join(class_types),
        value_objects='\n\t\t'.join(valueObjects[0]),
        value_object_properties='\n\t\t'.join(valueObjects[1]),
    )
    source = templateSource.substitute(
        class_name=file_name, 
    )
    createClass(project, os.path.join('Domain', 'Types', 'Entity', file_name), file_name, header, source)
    createBaseResourceApiPath(project, file_name, file_name)
    addEntityToCmakeLists(project, file_name + '/' + file_name)

def createSubClassEntity(project, baseName, namesuggestions, valueObject):
    templateHeader = readTemplate(os.path.join('entity','abstract'), 'subClass.h')
    templateSource = readTemplate(os.path.join('entity','abstract'), 'subClass.cpp')

    file_name = prompt('Enter subclass-file name: ')

    if file_name == 'no':
        return ''

    database_var = getDatabaseName()
    valueObjects = addValueObjects(namesuggestions, valueObject)

    header = templateHeader.substitute(
        class_name=file_name, 
        class_name_base=baseName, 
        project_name=(project+'domain').upper(), 
        class_info=database_var,
        value_objects='\n\t\t'.join(valueObjects[0]),
        value_object_properties='\n\t\t'.join(valueObjects[1]),
    )
    source = templateSource.substitute(
        class_name=file_name, 
        class_name_base=baseName, 
    )
    createClass(project, os.path.join('Domain', 'Types', 'Entity', baseName), file_name, header, source)
    createBaseResourceApiPath(project, file_name, baseName)
    addEntityToCmakeLists(project, baseName + '/' + file_name)
    return file_name
    
arrPaths =[]
arrNames =[]


for file in os.listdir('deps/'):
    path = os.path.join('deps', file, 'Domain')
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

entityList = [] 
valueObject = [] 

for path, subdirs, files in os.walk(os.path.join(os.getcwd(), 'deps', project_selection, os.path.join('Domain', 'Types', 'Entity'))):
    for name in files:
        if name.endswith('.h'):
           entityList.append(name.replace('.h','') + '*')

for path, subdirs, files in os.walk(os.path.join(os.getcwd(), 'deps', 'Framework', os.path.join('DomainCore', 'Types', 'ValueObject'))):
    for name in files:
        if name.endswith('.h'):
           valueObject.append(name.replace('.h',''))

file_type = WordCompleter([ 'entity', 'abstract', 'class', 'utility'])
file_selection = prompt('Enter file type: ', default='e', completer=file_type)

if file_selection == 'entity':
    createEntity(project_selection, entityList, valueObject)
elif file_selection == 'abstract':
    createAbstractEntity(project_selection, entityList, valueObject)
elif file_selection == 'class':
    folder = prompt('Enter folder: ', default='Service', completer=WordCompleter([ 'Domain', 'Service', 'Test']))
    createClassFile(project_selection, folder)
elif file_selection == 'utility':
    folder = prompt('Enter folder: ', default='Service/Utility', completer=WordCompleter([ 'Service/Utility']))
    createUtilityFile(project_selection, folder)

should_create = prompt('Create Project?', default='yes', completer=WordCompleter(['yes', 'no'], ignore_case=True))

if should_create == 'yes':
    subprocess.check_call([sys.executable, 'scripts/BuildAndTest.py', project_selection])
