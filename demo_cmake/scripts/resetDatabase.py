import subprocess


subprocess.check_call(["docker-compose", "down", "-v" ])
subprocess.check_call(["docker-compose", "up", "-d", "database" ])