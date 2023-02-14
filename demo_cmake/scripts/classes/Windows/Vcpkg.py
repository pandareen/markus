import os
import shutil
import subprocess
import glob
        
class Vcpkg():
   def __init__(self, config, projectPath ):
       self.config = config
       self.projectPath = projectPath
       self.path = 'C:/vcpkg' 

   def installPackages(self, packages):
         subprocess.check_call([
            *self.getVCPKGExecutable(),
            'install',
            '--clean-buildtrees-after-build',
            *packages,
        ], env=self.config) 

   def getVCPKGExecutable(self):
       vcpkg_path = glob.glob(
           os.path.join(self.path,'vcpkg.exe'),
           recursive=True,
       )[0]
       return [vcpkg_path,]

   def installQtAndGTest(self):
       return self.installPackages(self.qtPackages() + self.gTestPackage())

   def qtPackages(self):
       return ['qtbase[sql-mysql]:x64-windows', 'qttools:x64-windows']

   def gTestPackage(self):
       return ['gtest:x64-windows']

   def getBinaries(self, type='debug'):
       if(type.lower() == 'release'):
          return os.path.join(self.path, 'installed', 'x64-windows',  'bin')

       return os.path.join(self.path, 'installed', 'x64-windows',  type.lower(),  'bin')

   def getQtPlugins(self, type='debug'):
       if(type.lower() == 'release'):
          return os.path.join(self.path, 'installed', 'x64-windows', 'Qt6', 'plugins')

       return os.path.join(self.path, 'installed', 'x64-windows',  type, 'Qt6', 'plugins')
   
   def getOpenSSL(self):
       return os.path.join(self.path, 'installed', 'x64-windows',  'tools', 'openssl')

   def installBootstrap(self):
        t1 = os.path.join(self.projectPath, 'deps', 'vcpkg',)
        t2 = os.path.join(t1, 'bootstrap-vcpkg.bat')

        print(t2)
        assert os.path.exists(t2)
       
        if not os.path.exists(self.path):
            shutil.copytree(t1, self.path,)
        else:
            print(['vcpkg at C: found'])

        t4 = os.path.join(self.path, 'vcpkg.exe')
        if not os.path.exists(t4):
            subprocess.call(
                [
                    'cmd.exe',
                    '/c',
                    'bootstrap-vcpkg.bat',
                ],
                cwd=self.path,
            )
        assert os.path.exists(t4)