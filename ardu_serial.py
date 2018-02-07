#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import serial
import struct

rospy.init_node('Servo_control',anonymous=True)
ser = serial.Serial("/dev/ttyACM0", 9600)
ser.flushInput()
pub = rospy.Publisher('arduino', String, queue_size=10)
r = rospy.Rate(10)
print('connection created')
a = raw_input("Enter angle:")
ser.write(struct.pack('>H',long(a)))

while not rospy.is_shutdown():
    print('enter the loop')
    var = ser.readline()
    print ser.readline()
    pub.publish(var)
    r.sleep()



