import serial
import time
import numpy as np
ser = serial.Serial('COM3', 9600, timeout=0.1)
time.sleep(2) #wait for arduino
print(ser.name)

while True:
    input = ser.readline()
    list = [int(s) for s in input.split() if s.isdigit()]
    if np.size(list)>0:
        numinput = list[0]
    print(numinput)

ser.close()