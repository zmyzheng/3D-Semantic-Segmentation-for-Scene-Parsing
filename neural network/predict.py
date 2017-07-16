#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 25 22:15:25 2017

@author: Zmy-Apple
"""
import keras

from model import getModel
#from keras.optimizers import SGD
from keras.optimizers import RMSprop
import pandas as pd
import numpy as np
import os

import shutil
num_classes = 9

pointxyz = pd.read_csv('testx.csv',header=None, skiprows=0,sep=",")


x_test = np.array(pointxyz)

x_test = x_test.astype('float32')


print(x_test.shape[0], 'test samples')


y = pd.read_csv('testy.csv',header=None, sep=",")[0]

y_test = np.array(y)

# convert class vectors to binary class matrices

y_test = keras.utils.to_categorical(y_test, num_classes)

model = getModel()
#sgd = SGD(lr=0.1, decay=1e-6, momentum=0.9, nesterov=True)

model.compile(loss='categorical_crossentropy',
              optimizer=RMSprop(),
              metrics=['accuracy'])


model.load_weights('weights5.hdf5')
 
score = model.evaluate(x_test, y_test, verbose=0)
print('Test loss:', score[0])
print('Test accuracy:', score[1])


prob = model.predict(x_test)
prediction = np.argmax(prob, axis=1)

print(np.sum(prediction == np.array(y)) / 700.0)

try:
    os.makedirs('output')
except OSError:
    shutil.rmtree('output', ignore_errors=True)
    os.makedirs('output')
    
with open('output/result.txt', 'w') as f:
    for label in prediction:
        f.write(str(label))
        f.write('\n')
        
