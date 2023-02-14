import os
import shutil
from .Vcpkg import Vcpkg

class FileMover():
   def __init__(self, vcpkg, framework,  destination, installedPathFunc, type='debug'):
       self.destination = destination
       self.framework = framework
       self.installedPathFunc = installedPathFunc
       self.vcpkg : Vcpkg = vcpkg
       self.type = type.lower()

   def deployQtFilesToBinFolder(self, type='debug'):
       self.moveDllFiles(type)  
       self.moveOpenSSL()
       self.moveQtFolder('platforms', type)
       self.moveQtFolder('sqldrivers', type)
       self.moveQtFolder('tls', type)
       self.moveQtFolder('imageformats', type)

   def moveSwaggerUi(self, swaggerPath):
       uiPath = os.path.join(swaggerPath, 'swagger-ui-app', 'release')
       outputPath =  os.path.join(self.destination, 'swagger')

       if(os.path.exists(outputPath)):
           shutil.rmtree(outputPath)
       
       shutil.copytree(uiPath, outputPath)

   def moveQtFolder(self, folderName, type='debug'):
        if not os.path.isdir(os.path.join(self.destination, folderName)):
           shutil.copytree(
               os.path.join(self.vcpkg.getQtPlugins(self.type), folderName),
               os.path.join(self.destination, folderName))

   def moveDllFiles(self, type='debug'):
       self.moveFolderDllsToDestination(self.vcpkg.getBinaries(type))
  
   def moveFrameworkFiles(self, type='debug'):
       self.moveFolderDllsToDestination(self.framework)

       if(type == 'debug'):
           self.moveFolderDllsToDestination(self.framework, ".pdb")
      
   def moveQuazipDllFiles(self):
       filePath = self.installedPathFunc("quazip")
       self.moveFolderDllsToDestination(filePath)

   def moveOpenSSL(self):
       folder = self.vcpkg.getOpenSSL()
       for file in os.listdir(folder):
           if file.endswith(".dll") and not os.path.isfile(os.path.join(self.destination, file)):
             shutil.copy(os.path.join(folder, file), self.destination)       

   def moveFolderDllsToDestination(self, folderPath, extension=".dll"):
       for file in os.listdir(folderPath):
           src_file = os.path.join(folderPath, file)
           dst_file = os.path.join(self.destination, file)
           if file.endswith(extension):
               if os.path.exists(dst_file):
                    if os.path.samefile(src_file, dst_file):
                        continue
                    os.remove(dst_file)
               shutil.copy2(src_file, self.destination)