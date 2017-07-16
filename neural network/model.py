#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 25 22:18:08 2017

@author: Zmy-Apple
"""
from keras.models import Sequential
from keras.layers import Dense, Dropout
def getModel():
    model = Sequential()
    model.add(Dense(512, activation='relu', input_shape=(33,)))
    #model.add(Dropout(0.1))
    model.add(Dense(512, activation='relu'))
    #model.add(Dropout(0.1))
    
    model.add(Dense(256, activation='relu'))
    
    
    #model.add(Dropout(0.1))
    
    model.add(Dense(128, activation='relu'))
    model.add(Dropout(0.1))
    
    model.add(Dense(64, activation='relu'))
    model.add(Dropout(0.1))
    
    model.add(Dense(9, activation='softmax'))
    
    return model