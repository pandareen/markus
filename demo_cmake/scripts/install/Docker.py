import sys
import os

import urllib.request
import subprocess, sys
from ..classes.Windows.InstallerLoader import InstallerLoader

if sys.platform == 'win32':
    loader = InstallerLoader()
    loader.installDocker()
else:
    raise NotImplementedError
