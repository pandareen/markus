import urllib.request
import docker


class Docker():
   def __init__(self):
       self.client = docker.from_env()
       
   def pullImageIfNotInstalled(self, image):
       if not self.hasImage(image):
          self.pullImage(image) 
      
   def hasContainer(self, name ):
       try:
           return self.client.containers.get(name)
       except docker.errors.NotFound:
           return False

   def hasImage(self, image ):
       try:
           return self.client.images.get(image)
       except docker.errors.ImageNotFound:
           return False
       
   def pullImage(self, image ):
      self.client.images.pull(image)  
      
   def build(self, image ):
      self.client.images.pull(image)

   def createVolume(self, name):
      self.client.volumes.create(name=name)

   def buildImage(self, path, buildargs : dict ):
      self.client.images.build(path=path, nocache=True, buildargs=buildargs)

   def createContainerIfNotInstalled(self, name, **args):
       if not self.hasContainer(name):
            self.runContainer(name, **args)


#subprocess.check_call(["docker", "volume", "create", "mysqlvol" ])
#"--mount", "source=mysqlvol,target=/var/lib/mysql", "mysql"]