import numpy as np 
import os 
import matplotlib.pyplot as plt

#physical constants
B = 4600 #K
T_0 = 298.15 #K

def changeOfTempInB(voltageMeasurement):
	return (np.log(1023/voltageMeasurement -1)/B + 1/T_0)**(-2)*np.log(1023/voltageMeasurement -1)/B**2

def changeOfTempInV(voltageMeasurement):
	return (1023/(1023 * voltageMeasurement - voltageMeasurement**2)* 1/B * (np.log(1023/voltageMeasurement -1)/B + 1/T_0)**(-2))

def deltaTemperature(voltageMeasurement):
	deltaB = 138 #K from the manual chosen as the uncertainty
	deltaV = 0.05 * voltageMeasurement #list type
	return np.sqrt(deltaB**2 * changeOfTempInB(voltageMeasurement)**2 + deltaV**2 * changeOfTempInV(voltageMeasurement)**2)

for index in range(1,9):
	time = [] #has index 0 in data
	fan_speed = [] #index 2 in data
	temperature = [] # index 3 in data
	voltage_int = [] #index 1 in data

	time = np.genfromtxt('Experiment%i.txt' %index, delimiter=',')[:,0]
	voltage_int = np.genfromtxt('Experiment%i.txt' %index, delimiter=',')[:,1]
	fan_speed = np.genfromtxt('Experiment%i.txt' %index, delimiter=',')[:,2]
	temperature = np.genfromtxt('Experiment%i.txt' %index, delimiter=',')[:,3]

	plt.plot(time, temperature, 'b+')
	plt.errorbar(time, temperature, yerr=deltaTemperature(voltage_int), fmt=' ', capsize=0.7, elinewidth=0.1, linestyle=' ')
	plt.xlabel('time [ms]')
	plt.ylabel('temperature [°C]')
	plt.legend(( 'data points', 'error bars'))
	plt.savefig('temperature%i.pdf' %index)
	plt.show()

#plots etc.
