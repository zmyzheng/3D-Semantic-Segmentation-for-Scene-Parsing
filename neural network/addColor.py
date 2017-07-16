import pandas as pd
import os
import glob
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn import tree
from sklearn.externals.six import StringIO
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.externals import joblib

pointcloudName = 'test_value.txt'
resultName = 'result.txt'
pointxyz = pd.read_csv(pointcloudName,header=None,sep=" ")
labelpred = pd.read_csv(resultName,header=None,sep=" ")[0]
print(labelpred)
pointNum = 63360
colorlist = pd.DataFrame(columns=list('RGB'))
colorlabel = np.zeros(shape=(0,3))
for i in range(0,pointNum):
	#print(i)
	if labelpred[i] == 0: # grey, other class
		colorlist.loc[i] = np.array([153, 153, 153])
	if labelpred[i] == 1: # purple, man made terrain
		colorlist.loc[i] = np.array([128, 0, 128])
	if labelpred[i] == 2: # blue, natural terrain
		colorlist.loc[i] = np.array([0, 255, 255])
	if labelpred[i] == 3: # green, high vegetation
		colorlist.loc[i] = np.array([0, 255, 0])
	if labelpred[i] == 4: # dark green, low vegetation
		colorlist.loc[i] = np.array([0, 128, 0])
	if labelpred[i] == 5: # red, building
		colorlist.loc[i] = np.array([255, 0, 0])
	if labelpred[i] == 6: # orange, hard scape
		colorlist.loc[i] = np.array([255, 128, 0])
	if labelpred[i] == 7: # yellow, scanning artefacts
		colorlist.loc[i] = np.array([255, 255, 0])
	if labelpred[i] == 8: # black, car
		colorlist.loc[i] = np.array([0, 0, 0])
#print(colorlist)




# path = '/media/lingyuzhang/SCHOOL/1Columbia/1Courses/Spring17/DVMM/Testing' 
# files = os.listdir(path)      
# for filename in files:
# 	portion = os.path.splitext(filename)
# 	if portion[1] == ".pcd": 
# 		newname = portion[0] + ".csv"  
# 		os.rename(filename,newname)


path = '/Users/lingyuzhang/Spring17/3DeepLearning/featureextraction/' 
portion = os.path.splitext(pointcloudName)


#print(pointxyz)
outputobj = pd.concat([pointxyz,colorlist], axis=1)
#print(outputobj)

#outputobj.to_csv(portion[0] + "_100_200.txt",sep=' ',index=False,index_label=False, header=False)
#outputobj.to_csv(portion[0] + "_200_300.txt",sep=' ',index=False,index_label=False, header=False)
outputobj.to_csv(portion[0] + "_color_code.txt",sep=' ',index=False,index_label=False, header=False)
#outputobj.to_csv(portion[0] + "_400_600.txt",sep=' ',index=False,index_label=False, header=False)
#outputobj.to_csv(portion[0] + "_500_600.txt",sep=' ',index=False,index_label=False, header=False)
#outputobj.to_csv(portion[0] + "_600_700.txt",sep=' ',index=False,index_label=False, header=False)