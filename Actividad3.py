from grove_rgb_lcd import *
from grovepi import *
import time
import grovepi
import math
sensor = 0
button = 4
pinMode(button,"INPUT")
str1 = "Temp = "
str2 = " C"
while True:
    temp = str(grovepi.temp(sensor,'1.1'))
    temp = temp[0:4]
    button_status = digitalRead(button)
    if button_status:
        setRGB(0,255,0)
        message = str1+temp+str2
        setText_norefresh(message)
    else:
        setRGB(255,0,0)
        setText_norefresh("Presiona el boton")