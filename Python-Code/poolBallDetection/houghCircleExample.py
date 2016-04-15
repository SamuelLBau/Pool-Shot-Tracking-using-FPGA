import numpy as np
import cv2
import os




def findHoughCircles(inFile,outFile="",minRadius=20,maxRadius=40,minDistance=20):
    img = cv2.imread(inFile, 0 );

    img = cv2.GaussianBlur(img,(3,3),0)
    cimg = cv2.cvtColor(img,cv2.COLOR_GRAY2BGR)

    circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,minDistance,
                                param1=50,param2=30,minRadius=minRadius,maxRadius=maxRadius)
    if(circles != None):
        
        circles = np.uint16(np.around(circles))
        for i in circles[0,:]:
            # draw the outer circle
            cv2.circle(cimg,(i[0],i[1]),i[2],(0,255,0),2)
            # draw the center of the circle
            cv2.circle(cimg,(i[0],i[1]),2,(0,0,255),3)

    if(outFile == ""):
        cv2.imshow('detected circles',cimg)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    else:
        cv2.imwrite(outFile,cimg)
        
    
    return circles
    
    
    
if __name__ == "__main__":
    programDir = os.path.dirname(os.path.realpath(__file__))
    imageSourceDir = os.path.join(programDir,'..', 'sourceImages')+ "\\"
    imageResultDir =programDir + "/resultImages/"
    
    findHoughCircles(imageSourceDir+"/racked5.jpg")
    #findHoughCircles(imageResultDir+"/racked4_processed.jpg")