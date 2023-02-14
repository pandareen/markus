import os
import urllib
import urllib.request
import subprocess


class InstallerLoader():
   def __init__(self):
       self.installerPath = './tmp/installer/'
       if not os.path.exists(self.installerPath):
         os.makedirs(self.installerPath)
       
   def downloadAndInstall(self, downloadURL, fileName, startArguments ):
      filePath = os.path.join(self.installerPath, fileName)
      if not os.path.exists(filePath):
        urllib.request.urlretrieve(downloadURL, filePath)
        subprocess.check_call([filePath, *startArguments])       

   def downloadAndInstallMSI(self, downloadURL, fileName, startArguments ):
      filePath = os.path.join(self.installerPath, fileName)
      if not os.path.exists(filePath):
        urllib.request.urlretrieve(downloadURL, filePath)
      subprocess.check_call(["msiexec.exe", "/a", os.path.abspath(filePath), *startArguments])

   def installLLVM(self):
       self.downloadAndInstall('https://github.com/llvm/llvm-project/releases/download/llvmorg-15.0.7/LLVM-15.0.7-win64.exe', 
                               'LLVM-15.0.7-win64.exe', ['/S'])
       
   def installMysqlWorkbrench(self):
        setupName = "mysql-workbench-community-8.0.30-winx64.msi"
        logPath = os.path.join(self.installerPath, "log.txt")
        self.downloadAndInstallMSI("https://cdn.mysql.com//Downloads/MySQLGUITools/" + setupName,
                                  setupName, ["/qn", "/l*v", logPath]) 
   def eraseInstaller(self):
       for file in os.listdir(self.installerPath):
           if file.endswith(".exe"):
               os.remove(file)