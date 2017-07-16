from __future__ import print_function

import keras
import os
import time
import shutil


from keras.optimizers import SGD
from keras.optimizers import RMSprop
from keras import callbacks
import pandas as pd
import numpy as np

from model import getModel
batch_size = 128
num_classes = 9
epochs = 20


pointxyz = pd.read_csv('trainx.csv',header=None, skiprows=0,sep=",")

x_train = np.array(pointxyz)
x_test = np.array(pointxyz[110000:])
x_train = x_train.astype('float32')
x_test = x_test.astype('float32')

print(x_train.shape[0], 'train samples')
print(x_test.shape[0], 'test samples')


y = pd.read_csv('trainy.csv',header=None, sep=",")[0]
y_train = np.array(y)
y_test = np.array(y[110000:])

# convert class vectors to binary class matrices
y_train = keras.utils.to_categorical(y_train, num_classes)
y_test = keras.utils.to_categorical(y_test, num_classes)


train_desc = '{}-lr{:.0e}-bs{:03d}'.format(
        time.strftime("%Y-%m-%d %H:%M"),
        1,
        batch_size)

checkpoints_folder = 'trained/' + train_desc
try:
    os.makedirs(checkpoints_folder)
except OSError:
    shutil.rmtree(checkpoints_folder, ignore_errors=True)
    os.makedirs(checkpoints_folder)

model_checkpoint = callbacks.ModelCheckpoint(
    checkpoints_folder + '/ep{epoch:02d}-vl{val_loss:.4f}.hdf5',
    monitor='loss')

tensorboard_cback = callbacks.TensorBoard(
    log_dir='{}/tboard'.format(checkpoints_folder),
    histogram_freq=0,
    write_graph=False,
    write_images=False)

csv_log_cback = callbacks.CSVLogger(
    '{}/history.log'.format(checkpoints_folder))

'''
reduce_lr_cback = callbacks.ReduceLROnPlateau(
    monitor='val_loss',
    factor=0.2,
    patience=5,
    verbose=1,
    min_lr=0.05 * learning_rate)

'''

model = getModel()

model.summary()

#sgd = SGD(lr=0.1, decay=1e-6, momentum=0.9, nesterov=True)


model.compile(loss='categorical_crossentropy',
              optimizer=RMSprop(),
              metrics=['accuracy'])
'''
history = model.fit(x_train, y_train,
                    batch_size=batch_size,
                    epochs=epochs,
                    verbose=1,
                    validation_data=(x_test, y_test))
score = model.evaluate(x_test, y_test, verbose=0)
print('Test loss:', score[0])
print('Test accuracy:', score[1])
'''
model.fit(
        x_train,
        y_train,
        batch_size= batch_size,
        epochs=epochs,
        validation_data=(x_test, y_test),
        callbacks=[
            model_checkpoint,
            tensorboard_cback,
            csv_log_cback,
        ])
    
score = model.evaluate(x_test, y_test, verbose=0)
print('Test loss:', score[0])
print('Test accuracy:', score[1])
