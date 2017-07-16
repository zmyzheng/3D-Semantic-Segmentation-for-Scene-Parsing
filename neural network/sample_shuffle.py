#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr 26 05:06:35 2017

@author: Zmy-Apple
"""
import keras
import numpy as np
import pandas as pd

#rawx = pd.read_csv('rawx.txt',header=None, sep=" ")[:,0:3]
#rawy = pd.read_csv('rawy.txt',header=None, sep=" ")[:,0]

rawx = np.loadtxt("rawx.txt", delimiter=' ', usecols=range(0,3))
rawy = np.loadtxt("rawy.txt", delimiter=' ', usecols=range(0,1))

def balanced_subsample(x,y,subsample_size=1.0):

    class_xs = []
    min_elems = None

    for yi in np.unique(y):
        elems = x[(y == yi)]
        class_xs.append((yi, elems))
        if min_elems == None or elems.shape[0] < min_elems:
            min_elems = elems.shape[0]

    use_elems = min_elems
    if subsample_size < 1:
        use_elems = int(min_elems*subsample_size)

    xs = []
    ys = []

    for ci,this_xs in class_xs:
        if len(this_xs) > use_elems:
            np.random.shuffle(this_xs)

        x_ = this_xs[:use_elems]
        y_ = np.empty(use_elems)
        y_.fill(ci)

        xs.append(x_)
        ys.append(y_)

    xs = np.concatenate(xs)
    ys = np.concatenate(ys)

    return xs,ys

trasx, trasy = balanced_subsample(rawx, rawy, subsample_size=1)

with open('trasx.txt', 'w')as x, open('trasy.txt', 'w') as y:
    for line in trasx:
        string = str(line[0]) + ' ' + str(line[1]) + ' ' + str(line[2]) + '\n'
        x.write(string)
    
    for line in trasy:
        string = str(line) + '\n'
        y.write(string)