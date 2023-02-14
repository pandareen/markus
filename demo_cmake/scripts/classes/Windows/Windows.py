import os
import glob, shutil
import subprocess
from ..Environment import Environment
from .Vcpkg import Vcpkg
from .FileMover import FileMover

class Windows(Environment):
     def __init__(self, projectName):
          super().__init__(projectName)
          self.vcpkg = Vcpkg(self.getBasicConfig(), self.getProjectPath())

     def runAllTests(self, type='Debug'):
        filePath = self.getBuildBinPath(None, type)
        for file in os.listdir(filePath):
            if file.endswith("Test.exe"):
               subprocess.check_call(os.path.join(filePath, file))
        self.writeTimeLog(self.runAllTests)

     def preBuild(self, type):
         self.vcpkg.installBootstrap()
         self.vcpkg.installQtAndGTest()

         if(os.path.exists(self.getIncludePath())):
             shutil.rmtree(self.getIncludePath())

     def postBuild(self, type):
         hasServiceProject = os.path.exists(os.path.join(self.getDependencyPath(), 'Service'))

         fileMover = FileMover(
           self.vcpkg,
           self.getBuildBinPath('Framework', type),                                     
           self.getBuildBinPath(None, type),  
           self.getInstallBinPath,
           type
         )

         if(self.projectName == 'Framework' or hasServiceProject):
             fileMover.moveSwaggerUi(os.path.join(self.getDependencyPath('Framework'), 'Library', 'Swagger'))
             fileMover.deployQtFilesToBinFolder(type)
             fileMover.moveQuazipDllFiles()

         if(hasServiceProject):
            fileMover.moveFrameworkFiles(type)

     def getConfig(self):
        config = self.getBasicConfig()
        config['VCPKG_ROOT'] = self.vcpkg.path
        config['PATH'] += os.path.pathsep.join([
           os.path.join(self.getInstallPath(), 'bin'),
           os.path.join(config['VCPKG_ROOT'], 'installed', 'x64-windows', 'bin'),
           os.path.join(config['VCPKG_ROOT'], 'installed', 'x64-windows', 'debug', 'bin'),
        ])
        return config
     
     def getCMakePath(self):
         t1 = lambda extra_glob: [
         o
         for o in [
             os.path.join(o, 'cmake.exe')
             for o in os.get_exec_path()
         ]
         if os.path.exists(o)
         ] + glob.glob(extra_glob, recursive=True)
         cmake_path = t1(extra_glob=r'C:\vckpg\downloads\**\cmake.exe')[0]
         return [cmake_path,]