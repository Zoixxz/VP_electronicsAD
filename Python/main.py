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
Data = np.array([[0, 0, 0, 0]]) # Time, Voltage, RPM, Temperature
input = '0'
while input!='42':
    input = ser.readline()
    print(input)
    input = input.decode('ascii')
    input = input.replace('\r\n', '')
    print('waiting for start')

for i in range(100):
    tempo = np.array([0., 0., 0., 0.])
    j=0
    while j<4:
            input = ser.readline()
            input = input.decode('ascii')
            input = input.replace('\r\n', '')
            if input != '' and input != '42':
                tempo[j] = float(input)
                j+=1
    
    print(tempo)

    
    
    Data = np.vstack((Data, tempo))

Data = Data[1:-5, :]
plt.figure()
plt.plot(Data[1:-1, 0], Data[1:-1, 3], '.')
plt.xlabel('time [ms]')
plt.ylabel('Temperature [C]')
plt.savefig('Temperature.pdf')
plt.show()

plt.figure()
plt.plot(Data[:, 0], Data[:, 1], '.')
plt.xlabel('time [ms]')
plt.ylabel('Voltage [mV]')
plt.savefig('Voltage.pdf')
plt.show()

plt.figure()
plt.plot(Data[:, 0], Data[:, 2], '.')
plt.xlabel('time [ms]')
plt.ylabel('RPM [1/s]')
plt.savefig('RPM.pdf')
plt.show()


ser.close()
 