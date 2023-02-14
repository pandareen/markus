import os, platform
import sys
import time
import humanize
from datetime import timedelta

from abc import ABC, abstractmethod
from .CMake import CMake

class Environment(ABC):

    @abstractmethod
    def __init__(self, projectName) -> None:
        self.projectName = projectName
        self.start_time = time.time()
    
    def __del__(self):
        print(self.projectName + ' took: {}'.format(self.getTimeDeltaToStartAsString() ))

    def preBuild(self, type):
        pass   

    def postBuild(self, type):
        pass 
 
    def build(self, module = 'All', type = 'Debug'):
        cmake = CMake(self.getCMakePath(), self.getConfig(), self.getIWYU())
        self.preBuild(type)
        cmake.createAndInstall(
            'deps/' + self.projectName,
            self.getBuildPath(),
            self.getInstallPath(), type, module)
        self.postBuild(type)
        self.writeTimeLog(self.build)
        
    def writeTimeLog(self, method):
        print(method.__name__ + ' took: {}'.format(self.getTimeDeltaToStartAsString()) )

    def buildAndRunTests(self, type = 'Debug'):
        self.build(type)
        self.runAllTests(type)

    #building methods
    def runAllTests(self, type='Debug'):
        pass

    def startPackagedApp(self):
        pass

    #building methods
    def createPackage(self, version, test=False):
        pass

    #path methods
    @abstractmethod
    def getCMakePath(self):
        pass

    @abstractmethod
    def getConfig(self):
        pass  

    def getBasicConfig(self):
        config = dict()

        config['PROJECT_ROOT'] = self.getProjectPath()
        config['CACHE_PATH'] = self.getCachePath()
        config['install_path']  = self.getInstallPath()
        config['build_path']  = self.getBuildPath()
        config['PYTHON_PATH'] = self.getPythonPath()
        config.update(dict(os.environ.items()))
        
        return config

    def getPythonPath(self):
        return sys.executable
    
    def getIWYU(self):
        return self.getDependencyPath('include-what-you-use')

    def getProjectPath(self):
        return os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
    
    def getDockerFolderPath(self):
        return os.path.join(self.getProjectPath(), 'docker')
        
    def getDockerFolderPath(self):
        return os.path.join(self.getProjectPath(), 'docker')

    def getCachePath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join(self.getProjectPath(), 'tmp', 'cache', project)  

    def getDeployPath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join(self.getProjectPath(), 'tmp', 'deployment', sys.platform, self.projectName)  
    
    def getLinuxDeployPath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join(self.getProjectPath(), 'tmp', 'deployment', 'linux', self.projectName)  

    def getDependencyPath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join(self.getProjectPath(), 'deps', project)

    def getBuildPath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join( self.getCachePath(project), 'builds', sys.platform )

    def getBuildBinPath(self, project=None, type = 'debug'):
        return os.path.join( self.getBuildPath(project), type.lower(), 'bin') 
   
    def getInstallPath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join(self.getCachePath(project), 'installed',)
   
    def getIncludePath(self, project=None):
        if project is None:
            project = self.projectName
        return os.path.join(self.getCachePath(project), 'installed', 'include')

    def getFrameworkInstallPath(self, type = 'Debug'):
        return os.path.join(self.getCachePath('Framework'), 'installed', type)    

    def getInstallBinPath(self, project=None, type = 'Debug'):
        if project is None:
            project = self.projectName

        if project == 'quazip':
             return os.path.join(self.getInstallPath(project), 'bin',)

        return os.path.join(self.getInstallPath(project), type, 'bin',)

    def osSupported(self, platform):
        return platform in ['cygwin', 'win32', 'linux']

    def getTimeDeltaToStartAsString(self):
        td = timedelta(seconds=time.time() - self.start_time)
        return humanize.precisedelta(td) 
