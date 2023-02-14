import subprocess, os,string, shutil
   
class AppDeployer():
   def __init__(self, inputPath, appDirOutputPath, projectName) -> None:
       self.inputPath  =  inputPath
       self.projectName =  projectName
       self.outputPath =  appDirOutputPath

   def readTemplate(self, filename):
        path = os.path.join(os.getcwd(), 'scripts', 'templates', filename)
        with open(path) as t:
          return string.Template(t.read())
        return ''

   def createFile(self, path, data):
        os.makedirs(os.path.dirname(path), exist_ok=True)
        f = open(path, "w")
        f.write(data)
        f.close()   

   def getDesktopFilePath(self):
       return os.path.join(self.outputPath, 'App.desktop')

   def createDesktopFile(self, path, icon, terminal='true',  comment=''):
          templateFile = self.readTemplate('template.Desktop')

          fileData = templateFile.substitute(
                name=self.projectName, 
                comment=comment, 
                exec=path, 
                icon=icon, 
                GenericName=self.projectName,
                categories='Utility',
                terminal=terminal
          )
          self.createFile(self.getDesktopFilePath(), fileData)

   def createDatabaseFile(self, username='root', password='DoesntMatter'):
        templateFile = self.readTemplate('config.json')

        fileData = templateFile.substitute(
              username= username,
              password= password
        )
        self.createFile(os.path.join(self.outputPath, 'usr', 'bin', 'database', 'config.json'), fileData)

   def copyPlugin(self, qtPath, plugin ):
        gccPath =  os.path.join(qtPath, 'plugins', plugin)
        pluginPath = os.path.join(self.outputPath, 'usr', 'plugins', plugin)
        shutil.rmtree(pluginPath) #buggy https://github.com/linuxdeploy/linuxdeploy-plugin-qt/issues/133
        shutil.copytree(gccPath, pluginPath)

   def createAppDir(self, iconFile, environment):
        #'--verbosity', '0', 
        subprocess.check_call(['linuxdeploy','--appdir', self.outputPath,
                               '--plugin', 'qt', '-e', self.inputPath,
                               '--icon-file', iconFile, '-d', self.getDesktopFilePath()], env=environment)
        self.copyPlugin(environment['QT_GCC'], 'sqldrivers')
        self.copyPlugin(environment['QT_GCC'], 'tls')
        self.copyPlugin(environment['QT_GCC'], 'platforms')


   def createAppImage(self, appImageName, environment):
        subprocess.check_call(['appimagetool',self.outputPath], env=environment)

        shutil.copy(appImageName, self.outputPath)       
        os.remove(appImageName)

   def createAppImageTerminal(self, version, iconFile, environment, test=True):
        
        appName =  ['App', 'Test'][test]

        if os.path.exists(self.outputPath):
           shutil.rmtree(self.outputPath) 

        self.createDesktopFile(appName, 'icon', 'true')
        self.createDatabaseFile()
        #maybe try to move plugins then dont have to delete them?!

        #print(environment)
        #environment['EXTRA_PLATFORM_PLUGINS'] = 'offscreen'
        #environment['DEBUG'] = '1'
        #environment['UPDATE_INFORMATION'] = 'zsync|https://server.domain/path/Application-latest-x86_64.AppImage.zsync'

        environment['VERSION'] = version
      
        appImageName = self.projectName + '-' + version + '-x86_64.AppImage'
        
        self.createAppDir(iconFile, environment)
        self.createAppImage(appImageName, environment)

        return os.path.join(self.outputPath, appImageName)  

