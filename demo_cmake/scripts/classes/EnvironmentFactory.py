import sys
from .Environment import Environment
from .Windows.Windows import Windows
from .Linux.Linux import Linux

class EnvironmentFactory():
     def __init__(self, projectName):
         self.projectName = projectName

     def create(self) -> Environment:
         if sys.platform == 'win32':
             return Windows(self.projectName)     
         if sys.platform == 'linux':
             return Linux(self.projectName)
         else:
            raise NotImplementedError