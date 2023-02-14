import sys
import os

import subprocess, sys
from ..classes.Windows.InstallerLoader import InstallerLoader
from ..classes.Docker import Docker

if sys.platform == 'win32':
    loader = InstallerLoader()
    docker = Docker()
    containerName = 'mysql-database'

    #docker.pullImageIfNotInstalled('mysql/mysql-server:latest')
    
    if not docker.hasContainer(containerName):
        subprocess.check_call(["docker", "run", "--name", containerName, "-p", "3306:3306",
                               "-e", "MYSQL_ROOT_PASSWORD=DoesntMatter", "-d", "mysql"]) 
     
  #  loader.installMysqlWorkbrench()
else:
    raise NotImplementedError
