import os
import subprocess

from ..Environment import Environment
from .AppDeployer import AppDeployer
from ..Github import Github

class Linux(Environment):
     def __init__(self, projectName) -> None:
        super().__init__(projectName)

     def runAllTests(self, type='Debug'):
        filePath = self.getBuildBinPath(None, type)
        for file in os.listdir(filePath):
            if file.endswith("Test"):
                subprocess.check_call([os.path.join(filePath, file) ], env=self.getConfig())
        self.writeTimeLog(self.runAllTests)

     def getConfig(self, type='Debug'):
         config = self.getBasicConfig()
         #config['QT_QPA_PLATFORM'] = 'offscreen'
         #config['QT_DEBUG_PLUGINS'] = '1'

         config['LD_LIBRARY_PATH'] = \
                config.get('LD_LIBRARY_PATH', '') + \
                os.path.pathsep.join([
                    os.path.join(self.getInstallBinPath(self.projectName, type)),
                ])
         if self.projectName != 'Framework':
            config['LD_LIBRARY_PATH'] = \
                config.get('LD_LIBRARY_PATH', '') + ';' +\
                os.path.pathsep.join([ os.path.join(self.getFrameworkInstallPath(type), 'lib'), ])

         return config

     def getCMakePath(self):
         return [subprocess.check_output(['which', 'cmake']).decode('utf-8').strip()]
     
     def createPackage(self, version, test=False):
         path = ''
         binPath = self.getBuildBinPath(self.projectName, 'Release')
         
         if(test):
            path = os.path.join(binPath, 'Test')
         else:
            path = os.path.join(binPath, 'App')

         deployer = AppDeployer(path, self.getDeployPath(), self.projectName)
         iconPath = os.path.join(self.getDependencyPath(), 'icon.png')

         output = deployer.createAppImageTerminal(version, iconPath, self.getConfig('Release'), test)
         self.writeTimeLog(self.createPackage)