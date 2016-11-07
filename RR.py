import serial
import struct
import time

# -1 is read start
# 0xAA55 is read end
_serial = serial.Serial('/dev/tty.usbserial-A504ECY3', baudrate = 38400)

raw = _serial.readline()
print "after readline"

data = struct.pack("<hhhhhhhh",-1,2300,500,300,500,500,500,-99)
#data = struct.pack("<h",-9999)
_serial.write(data)

time.sleep(2)
'''
for i in range(1):
	raw = _serial.readline()
	print raw
'''