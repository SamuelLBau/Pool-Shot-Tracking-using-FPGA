import numpy as np
import cv2
import imutils
<<<<<<< HEAD
from ballDetection import *



MAX_FRAMES = 180

INPUT_VIDEO_FILE = "GoPro4deFisheye2"
INPUT_EXTENSION = ".mp4"
OUTPUT_MASK_FILE = INPUT_VIDEO_FILE+"_mask.mp4"
OUTPUT_CIRCLES_FILE = INPUT_VIDEO_FILE+"_circles.mp4"
OUTPUT_TABLE_FILE = INPUT_VIDEO_FILE+"_table.mp4"
INPUT_VIDEO_FILE = INPUT_VIDEO_FILE + INPUT_EXTENSION

WRITE_CIRCLES_VIDEO = False
WRITE_MASK_VIDEO = False
=======
>>>>>>> parent of 928bfb9... Initial Table Detection Code

from ballDetection import *


cap = cv2.VideoCapture("croppedAndRotatedVideo1.mp4")

ret, frame = cap.read()
frameHeight,frameWidth,depth = frame.shape
#(*'H264')
fourcc = cv2.VideoWriter_fourcc("X","V","I","D")


maskWriter = cv2.VideoWriter("croppedAndRotatedVideo1_mask.mp4",fourcc,30,(frameWidth,frameHeight),0)
resultWriter = cv2.VideoWriter("croppedAndRotatedVideo1_result.mp4",fourcc,30,(frameWidth,frameHeight))

#fgbg = cv2.bgsegm.createBackgroundSubtractorMOG()
#fgbg = cv2.bgsegm.createBackgroundSubtractorGMG()

while(cap.isOpened()):
    ret, frame = cap.read()
    #bgsub = subtractBackground(fgbg,frame)
    #circles = getHoughCircles(frame)
    #cimg = drawCirclesOnFrame(circles,frame)
    #im_with_keypoints = drawBlobs(frame)
    
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    mask = getMask(frame)
    blobs = detectBlobs(frame,mask)
    circles = getCircles(blobs)
    

    outFrame = drawFrame(frame,blobs)
    
    maskWriter.write(mask)
    resultWriter.write(outFrame)
    
    outFrame = imutils.resize(outFrame, width=850)
    cv2.imshow('frame', outFrame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

maskWriter.release()
resultWriter.release()
cap.release()
cv2.destroyAllWindows()