import serial
import struct

# 10 is read start
# 30 is read end
_serial=serial.Serial('COM11',baudrate=38400)
dat=struct.pack("HH",10,30)
_serial.write(dat)
raw = _serial.read(size = 1)
print raw
