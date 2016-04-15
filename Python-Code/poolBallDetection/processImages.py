from glob import glob

import os

from getSobelImage import *
from houghCircleExample import *





programDir = os.path.dirname(os.path.realpath(__file__))
imageSourceDir = os.path.join(programDir,'..', 'sourceImages')+ "\\"
imageResultDir =programDir + "/resultImages/"


sourceImageList = glob(imageSourceDir + "*.jpg")
secondList = glob(imageSourceDir + "*.png")
for s in secondList:
    sourceImageList.append(s)
imageNames = []
outImageNames = []
outImageList = []
for s in sourceImageList:
    name = s.replace(imageSourceDir,"")
    imageNames.append(s.replace(imageSourceDir,""))
    
    outImageName = name.replace(".jpg","_processed.jpg").replace(".png","_processed.png")
    outImageNames.append(outImageName)
    outImageList.append(imageResultDir + outImageName)
    
#minRadius=20,maxRadius=40,minDistance=20
dataSet = []
entry1 = [15,50,10] 
dataSet.append(entry1)
entry2 = [25,50,15] 
dataSet.append(entry2)
entry3 = [20,50,12]
dataSet.append(entry3)
entryCount = 0
for entry in dataSet:
    entryCount = entryCount + 1
    length = len(sourceImageList)
    i=0
    while i < length:
        adjustedOutName = outImageList[i].replace(".jpg",str(entryCount) + ".jpg").replace(".png",str(entryCount) + ".png")
        findHoughCircles(sourceImageList[i],adjustedOutName,entry[0],entry[1],entry[2])
        i=i+1
    

    
    
    
