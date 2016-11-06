import serial
import struct
import time

# -1 is read start
# 0xAA55 is read end
_serial = serial.Serial('/dev/tty.usbserial-A504ECY3', baudrate = 38400)

raw = _serial.readline()
print "after readline"

#data = struct.pack("<hhhhhhhh",-1,1500,100,200,300,400,500,0xAA55)
data = struct.pack("<h",-9999)
_serial.write(data)

raw = _serial.readline()
print raw
raw = _serial.readline()
print raw
raw = _serial.readline()
print raw
raw = _serial.readline()
print raw
raw = _serial.readline()
print raw
