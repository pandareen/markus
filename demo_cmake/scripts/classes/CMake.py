import os
import shutil, pprint
import subprocess


class CMake():
   def __init__(self, cmakePath, config, iwyu):
       self.path = cmakePath
       self.config = config
       self.iwyu = iwyu

   def createAndInstall(self, sourcePath, buildPath, installPath, type='Debug', module='All'):
         self.generate(sourcePath, buildPath, installPath, type, module)
         self.build(buildPath, type, module)
         self.install(buildPath, type, module)

   def generate(self, sourcePath, buildPath, installPath, type,  module='All' ):
        subprocess.check_call([
            *self.path,
            '-S', sourcePath,
            '-B', buildPath,
            '-DCMAKE_INSTALL_PREFIX=%s' % installPath,
            '-DCMAKE_BUILD_TYPE=%s' % type,
            '-DMODULE=%s' % module,
        ], env=self.config) 
      
   def build(self, buildPath, type, module='All'):
        subprocess.check_call([
            *self.path,
            '--build', buildPath,
	 	    '--config', type,
            '--parallel', '24',
        ], env=self.config)

   def install(self, buildPath, type, module='All'):  
       subprocess.check_call([
            *self.path,
            '--build', buildPath,
            '--target', 'install',
		    '--config', type,
        ], env=self.config)

   def clean(self, paths):
       for o in [paths]:
           if os.path.exists(o):
              pprint.pprint(['clean', o])
              shutil.rmtree(o)