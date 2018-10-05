# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import csv 
import cv2
import numpy as np
import matplotlib.pyplot as plt
lines=[]
with open("./data/driving_log.csv") as csvfile:
    reader=csv.reader(csvfile)
    for line in reader:
        lines.append(line)
    
images=[]
measurements=[]
for line in lines:
    for i in range(3):
        source_path=line[i]
        filename=source_path.split('/')[-1]
        current_path=filename
        image=cv2.imread(current_path)
        images.append(image)
        measurement=float(line[3])
        measurements.append(measurement)
        
augmented_images,augmented_measurements=[],[]
for image,measurement in zip(images,measurements):
    augmented_images.append(image)
    augmented_measurements.append(measurement)
    augmented_images.append(cv2.flip(image,1))
    augmented_measurements.append(measurement*(-1))
    
X_train=np.array(augmented_images)
y_train=np.array(augmented_measurements)

from keras.models import Sequential
from keras.layers import Flatten,Dense,Lambda,Cropping2D,Dropout,ELU
from keras.layers.convolutional import Convolution2D
from keras.layers.pooling import MaxPooling2D


model=Sequential()
model.add(Lambda(lambda x:x/255.0-0.5,input_shape=(160,320,3)))
model.add(Cropping2D(cropping=((70,25),(0,0))))

model.add(Convolution2D(36,5,5))
model.add(ELU())
model.add( MaxPooling2D())

model.add(Convolution2D(24,5,5))
model.add(ELU())
model.add( MaxPooling2D())

model.add(Convolution2D(12,3,3))
model.add(ELU())
model.add( MaxPooling2D())
model.add(Convolution2D(6,3,3))
model.add(ELU())
model.add( MaxPooling2D())

model.add(Flatten())
model.add(Dropout(0.5))
model.add(Dense(128))
model.add(Dropout(0.4))
model.add(ELU())

model.add(Dense(64))
model.add(Dropout(0.3))
model.add(ELU())

model.add(Dense(16))
model.add(Dropout(0.2))
model.add(ELU())


model.add(Dense(4))
model.add(Dropout(0.1))
model.add(ELU())

model.add(Dense(1))
model.compile(loss="mse",optimizer="adam")



history_object=model.fit(X_train,y_train,validation_split=0.2,shuffle=True,nb_epoch=8,verbose=2)

model.save("model.h5")

print(history_object.history.keys())

### plot the training and validation loss for each epoch
plt.plot(history_object.history['loss'])
plt.plot(history_object.history['val_loss'])
plt.title('model mean squared error loss')
plt.ylabel('mean squared error loss')
plt.xlabel('epoch')
plt.legend(['training set', 'validation set'], loc='upper right')
plt.show()