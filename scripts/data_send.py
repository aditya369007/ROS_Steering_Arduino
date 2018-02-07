import serial
import time

arduino = serial.Serial(2, 9600, timeout = 1)
time.sleep(2)

while 1:
    
    command = str.encode('1')
    arduino.write(command)   
    time.sleep(1.5)


