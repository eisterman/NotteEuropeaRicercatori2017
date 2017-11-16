# -*- coding: utf-8 -*-
"""
Created on Thu Sep 28 17:40:26 2017

@author: fpasqua
"""
import serial
import time
import numpy as np
from vpython import *

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM7' # Porta USB Sinistra in Alto

ser.open()

ser.readline()

def getData():
    output = ser.readline().decode()
    data = output.split(',')
    del data[-1] # Cancella a capo finale
    data = np.array([int(a) for a in data])
    return data

def getAcc():
    return getData()[:3]

scene.fullscreen = True

#ref
X = arrow(pos=vector(0,0,0), axis=vector(20000,0,0), color=color.red, shaftwidth=100)
Y = arrow(pos=vector(0,0,0), axis=vector(0,20000,0), color=color.blue, shaftwidth=100) 
Z = arrow(pos=vector(0,0,0), axis=vector(0,0,20000), color=color.green, shaftwidth=100)

pointer = arrow(pos=vector(0,0,0),axis=vector(-1652,131,15453), color=color.orange, shaftwidth=300)
scene.autoscale = False
while True:
    rate(100)
    data = getAcc()
    pointer.axis = vector(-data[0],-data[2],-data[1])
    #pointer.axis = pointer.axis + vector(0,0,1)
    