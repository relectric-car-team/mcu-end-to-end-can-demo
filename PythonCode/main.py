import serial
import keyboard
import math
import time
import matplotlib.pyplot as plot

# Connect to the port
ser = serial.Serial(port= "COM4", baudrate = 115200, bytesize = 8, timeout = 10, stopbits = serial.STOPBITS_ONE)
counter = 0
loops = []
data_in = []
while(True):
    #byte = ser.read() # reads a single byte
    string = ser.readline() # reads a line '\n\r'
    string = string.decode(encoding= "ascii").strip()
    num = int(string)
    if(num > 0):
        num = 1
    else:
        num = -1
        
    data_in.append(num)
    loops.append(counter)
    counter+=1
    
    # breaks from loop, (not an interrupt; HOLD esc to exit)
    if(keyboard.is_pressed('esc')):
        break
    
plot.plot(loops, data_in)
plot.show()
ser.close() # makes sure the next time the port is accessed it isnt blocked by process already using it