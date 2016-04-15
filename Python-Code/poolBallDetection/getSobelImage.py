import cv2
import numpy as np
from matplotlib import pyplot as plt

def generateSobel(path,outpath,threshold=25):

    greyImage = cv2.imread(path,0)
    if(greyImage == None):
        print("Could not open image: %s"%(path))
    #cv2.imwrite(outpath,greyImage)
    #return
    sobel = cv2.Sobel(greyImage,cv2.CV_16S,1,1,ksize=1)
    #sobel = cv2.Laplacian(greyImage,cv2.CV_16S)
    absSobel = np.absolute(sobel)
    sobel = np.uint8(absSobel)
    sobel[sobel<threshold]=0
    sobel[sobel>=threshold]=255


    cv2.imwrite(outpath,sobel)
    
if __name__ == "__main__":   
    print("Using getSobelImage as main")
    sourcePath = "D:/Files/UCSD Undergrad/Spring 2016/CSE145/PythonImplementation/SourceImages/racked2.jpg"
    outPath = "D:/Files/UCSD Undergrad/Spring 2016/CSE145/PythonImplementation/sobelFilter/resultImages/racked1_grad.jpg"

    generateSobel(sourcePath,outPath)