# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import serial
import time
import numpy as np
import sys
import matplotlib.pyplot as plt
fanspeed = 0
ser = serial.Serial('COM4', 9600, timeout=0.1)
time.sleep(0.5) #wait for arduino
Data = np.array([[0, 0, 0, 0]]) # Time, threshold, Temperature, threshold<temperature
input = '0'
while input!='4242':
    input = ser.readline()
    print(input)
    input = input.decode('ascii')
    input = input.replace('\r\n', '')
    print('waiting for start')

for i in range(400):
    tempo = np.array([0., 0., 0., 0.])
    j=0
    while j<3:
            input = ser.readline()
            input = input.decode('ascii')
            input = input.replace('\r\n', '')
            if input != '' and input != '4242':
                tempo[j] = float(input)
                j+=1
    if tempo[2]>tempo[1]:
        tempo[3] = 1
    else:
        tempo[3] = 0
    print(tempo)

    
    
    Data = np.vstack((Data, tempo))

Data = Data[12:-12, :]
plt.figure()
plt.plot(Data[1:-1, 0], Data[1:-1, 2], '.')
plt.xlabel('time [ms]')
plt.ylabel('Temperature [C]')
plt.savefig('Temperature.pdf')
plt.show()

plt.figure()
plt.plot(Data[:, 0], Data[:, 1], '.')
plt.xlabel('time [ms]')
plt.ylabel('Threshold [C]')
plt.savefig('Threshold.pdf')
plt.show()

plt.figure()
plt.plot(Data[:, 0], Data[:, 3], '.')
plt.xlabel('time [ms]')
plt.ylabel('0: Thresh. > Temp., 1: Thresh. < Temp. ')
plt.savefig('TempThresh.pdf')
plt.show()



ser.close()
 