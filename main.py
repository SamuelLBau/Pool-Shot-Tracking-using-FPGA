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




NUM_TABLE_FRAMES_AVERAGED = 10

cap = cv2.VideoCapture(VIDEO_IN_NAME)


ret, frame = cap.read()
frameHeight,frameWidth,depth = frame.shape
#(*'H264')

frame = cv2.GaussianBlur(frame,(3,3),0)
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)   
box = getTable(hsv)




maskWriter = cv2.VideoWriter(MASK_VIDEO_NAME ,fourcc,30,(frameWidth,frameHeight),0)
#tableWriter = cv2.VideoWriter(TABLE_VIDEO_NAME,fourcc,30,(frameWidth,frameHeight)) 
#circlesWriter = cv2.VideoWriter(CIRCLE_VIDEO_NAME,fourcc,30,(frameWidth,frameHeight))
#resultWriter = cv2.VideoWriter(RESULT_VIDEO_NAME,fourcc,30,(frameWidth,frameHeight))
#fgbg = cv2.bgsegm.createBackgroundSubtractorMOG()
#fgbg = cv2.bgsegm.createBackgroundSubtractorGMG()

frameCount = 1
while(cap.isOpened()):
    ret, frame = cap.read()
    #bgsub = subtractBackground(fgbg,frame)
    #circles = getHoughCircles(frame)
    #cimg = drawCirclesOnFrame(circles,frame)
    #im_with_keypoints = drawBlobs(frame)
    
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frame = cv2.GaussianBlur(frame,(3,3),0)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    #This only searches for table for the first few frames
    #It averages the found corners, hopefully to limit
    if(frameCount < NUM_TABLE_FRAMES_AVERAGED): 
        newBox = getTable(hsv)
        box = averageBox(box,newBox,frameCount)
        frameCount = frameCount +1
    
    #This sets up frame for ball searching
    hsv = rotateFrame(box,hsv)    #This should return the hsv with the table isolated
    outFrame = rotateFrame(box,frame)
    mask = getMask(hsv,threshold=8000)#This does some light dilation, prevents some crash for some reason
    
    #This should be the iterative logic that tries to isolate balls
    #TODO: ADD ITERATIVE LOGIC HERE
    Nmask = erodeAndDilate(mask,erodeIT=4,dilateIT=4)
    #mask = None
    mask = Nmask.copy()
    #Nmask = None
    blobs = detectBlobs(mask)
    [circles,moments] = getCircles(blobs,minRadius=30,maxRadius=130)
    
    outFrame = drawCirclesOnFrame(outFrame,circles,moments)
    #outFrame = drawFrame(outFrame,blobs,minRadius=30,maxRadius=130)
    
    maskWriter.write(mask)
    #print(frame.shape)
    #print(tableFrame.shape)
    #tableWriter.write(tableFrame)
    #resultWriter.write(outFrame)
    #circlesWriter.write(outFrame)
    outFrame = imutils.resize(outFrame, width=850)
    cv2.imshow('frame', outFrame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

maskWriter.release()
#tableWriter.release()
#circlesWriter.release()
#resultWriter.release()
cap.release()
cv2.destroyAllWindows()