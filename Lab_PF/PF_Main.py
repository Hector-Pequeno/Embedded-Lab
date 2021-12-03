import subprocess
import time

while True:
	process = subprocess.Popen('/home/pi/bcm2835-1.58/examples/i2c/PF_Temperatura')
	process.wait()
	time.sleep(1)
	process2 = subprocess.Popen('/home/pi/bcm2835-1.58/examples/i2c/PF_Display_y_Humedad')
	process2.wait()
	time.sleep(1)
