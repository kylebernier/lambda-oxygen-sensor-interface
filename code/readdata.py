import serial
import struct
import statistics as stat
import matplotlib.pyplot as plt
import matplotlib.animation as anim
from collections import deque

import datetime
now=datetime.datetime.now()
out = open(now.isoformat(), 'w+')

# Connect to the USB serial device
ser = serial.Serial('/dev/ttyUSB0')
ser.baudrate = 115200
ser.flushInput()

# Graph data forever
while True:
    # Check for preamble
    while True:
        rdbytes = ser.read(1)
        if rdbytes == b'\xff':
            rdbytes = ser.read(1)
            if rdbytes == b'\xff':
                break
    # Read data
    rdbytes = ser.read(6)
    # Convert bytes to integers
    values = struct.unpack('<HHH', rdbytes)
    # Print the lambda value the temperature and the PWM Vrms
    print("Lambda:", end =" ")
    print("%.3f" % (values[0]/1000), end =" ")
    print("Temp:", end =" ")
    print(values[1], end=" ")
    print("Vrms:", end =" ")
    print("%.3f" % (values[2]/1000))
    print(values, file=out)

