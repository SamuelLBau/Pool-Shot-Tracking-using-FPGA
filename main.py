import numpy as np
import cv2
import imutils
from ballDetection import *



MAX_FRAMES = 180

WRITE_CIRCLES_VIDEO = False
WRITE_MASK_VIDEO = False



VIDEO_IN_NAME = "GoPro4DeFisheye3"
VIDEO_EXTENSION = ".mp4"
MASK_VIDEO_NAME = VIDEO_IN_NAME+"_mask.mp4"
TABLE_VIDEO_NAME = VIDEO_IN_NAME+"_table.mp4"
CIRCLE_VIDEO_NAME = VIDEO_IN_NAME+"_circles.mp4"
RESULT_VIDEO_NAME = VIDEO_IN_NAME+"_result.mp4"
VIDEO_IN_NAME = VIDEO_IN_NAME+ VIDEO_EXTENSION
fourcc = cv2.VideoWriter_fourcc("X","V","I","D")

cap = cv2.VideoCapture(VIDEO_IN_NAME)


ret, frame = cap.read()
frameHeight,frameWidth,depth = frame.shape
#(*'H264')





#maskWriter = cv2.VideoWriter(MASK_VIDEO_NAME ,fourcc,30,(frameWidth,frameHeight),0)
tableWriter = cv2.VideoWriter(TABLE_VIDEO_NAME,fourcc,30,(frameWidth,frameHeight)) 
#circlesWriter = cv2.VideoWriter(CIRCLE_VIDEO_NAME,fourcc,30,(frameWidth,frameHeight))
#resultWriter = cv2.VideoWriter(RESULT_VIDEO_NAME,fourcc,30,(frameWidth,frameHeight))
#fgbg = cv2.bgsegm.createBackgroundSubtractorMOG()
#fgbg = cv2.bgsegm.createBackgroundSubtractorGMG()

while(cap.isOpened()):
    ret, frame = cap.read()
    #bgsub = subtractBackground(fgbg,frame)
    #circles = getHoughCircles(frame)
    #cimg = drawCirclesOnFrame(circles,frame)
    #im_with_keypoints = drawBlobs(frame)
    
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frame = cv2.GaussianBlur(frame,(3,3),0)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    
    [H,tableFrame] = getTable(hsv,frame)
    #mask = getMask(H)
    #blobs = detectBlobs(frame,mask)
    #circles = getCircles(blobs)
    

    #outFrame = drawFrame(frame,blobs)
    
    #maskWriter.write(mask)
    #print(frame.shape)
    #print(tableFrame.shape)
    tableWriter.write(tableFrame)
    #resultWriter.write(outFrame)
    #circlesWriter.write(outFrame)
    
    outFrame = imutils.resize(tableFrame, width=850)
    #cv2.imshow('frame', outFrame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

#maskWriter.release()
tableWriter.release()
#circlesWriter.release()
#resultWriter.release()
cap.release()
cv2.destroyAllWindows()