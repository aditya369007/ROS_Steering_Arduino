from time import sleep
import serial
import struct
ser = serial.Serial('/dev/ttyACM0', 9600)
ser.flushInput()



while True:
    a = raw_input("Enter angle:")
    ser.write(struct.pack('>H', long(a)))
    var = ser.readline()
    print var
    var1 = ser.readline()
    print var1

     #sleep(.5)
