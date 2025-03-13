# -*- coding: utf-8 -*-
"""
Created on Sun Nov 26 14:24:44 2023

@author: User
"""


import pandas as pd
'''from matplotlib import pyplot as plt'''
import numpy as np
import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

dataDF=pd.read_csv('C:\\Users\\User\\.spyder-py3\\project.dat',sep=' ',names=['humidity','temp','date','time'])

T=dataDF['temp']
dataDF['p']=611.2*np.exp(17.504*T/(241.2+T))
dataDF['ro']=dataDF['p']*18/8.31/(T+273)
dataDF['abs']=dataDF['humidity']*dataDF['ro']/100
s_abs=dataDF['abs'].sum()
dataDF['T^2']=(dataDF['temp']*dataDF['temp'])
sumT2=dataDF['T^2'].sum()
x2=dataDF['humidity']*dataDF['humidity']
x3=dataDF['humidity']*dataDF['humidity']*dataDF['humidity']
x4=dataDF['humidity']*dataDF['humidity']*dataDF['humidity']*dataDF['humidity']
sumx2t=(x2*T).sum()
sumx4=x4.sum()
sumx3=x3.sum()
sumx2=x2.sum()
sumxt=(dataDF['humidity']*T).sum()
sumty=(T*dataDF['abs']).sum()
sumx2y=(x2*dataDF['abs']).sum()
sumxy=(dataDF['humidity']*dataDF['abs']).sum()
ex1=np.exp(dataDF['humidity'])
ex2=np.exp(2*dataDF['humidity'])
sumex1=ex1.sum()
sumex2=ex2.sum()
sumext=(ex1*T).sum()
sumexy=(ex1*dataDF['abs']).sum()
a=np.array([[sumT2,sumxt,dataDF['temp'].sum()],
            [sumxt,sumx2,dataDF['humidity'].sum()],
            [dataDF['temp'].sum(),dataDF['humidity'].sum(),109]])
b=np.array([sumty,sumxy,dataDF['abs'].sum()])
y=np.linalg.solve(a,b)
dataDF['y_lin']=y[0]*T+y[1]*dataDF['humidity']+y[2]
dataDF['delta']=dataDF['abs']-dataDF['y_lin']
a1=np.array([[sumT2,sumx2t,sumxt,dataDF['temp'].sum()], 
           [sumx2t,sumx4,sumx3,sumx2],
           [sumxt,sumx3,sumx2,dataDF['humidity'].sum()],
           [dataDF['temp'].sum(),sumx2t,sumxt,109]])
b1=np.array([sumty,sumx2y,sumxy,dataDF['abs'].sum()])
y1=np.linalg.solve(a1,b1)
dataDF['y_kv']=y1[0]*T+y1[1]*x2+y1[2]*dataDF['humidity']+y1[3]
dataDF['delta1']=dataDF['abs']-dataDF['y_kv']
a2=np.array([[sumT2,sumext,dataDF['temp'].sum()],
             [sumext,sumex2,sumex1],
             [dataDF['temp'].sum(),sumex1,109]])
b2=np.array([sumty,sumexy,dataDF['abs'].sum()])
y2=np.linalg.solve(a2,b2)
dataDF['y_exp']=y2[0]*T+y2[1]*ex1+y2[2]
dataDF['delta2']=dataDF['abs']-dataDF['y_exp']
plt.plot(dataDF['y_lin'],dataDF['humidity'],dataDF['temp'])
plt.show()
