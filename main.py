import numpy as np
import cv2
import imutils
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



cap = cv2.VideoCapture(INPUT_VIDEO_FILE)

ret, frame = cap.read()
frameHeight,frameWidth,depth = frame.shape
#(*'H264')
fourcc = cv2.VideoWriter_fourcc("X","V","I","D")
if WRITE_MASK_VIDEO:
    maskWriter = cv2.VideoWriter(OUTPUT_MASK_FILE,fourcc,30,(frameWidth,frameHeight),0)

if WRITE_CIRCLES_VIDEO:
    circlesWriter = cv2.VideoWriter(OUTPUT_CIRCLES_FILE,fourcc,30,(frameWidth,frameHeight))
    
tableWriter = cv2.VideoWriter(OUTPUT_TABLE_FILE,fourcc,30,(frameWidth,frameHeight),0)
count = 0

while(cap.isOpened()):
    ret, frame = cap.read()             #Gets frame from the video
    
    
    hsv = cv2.GaussianBlur(frame,(3,3),0)
    hsv = cv2.cvtColor(hsv, cv2.COLOR_BGR2HSV)
    
    #H is the Hue array 
    [H,table] = getTable(hsv[:,:,0]) 
    #circles = generateCircleList(frame) #This does same operation as next 3 lines
    #mask = getMask(frame)               #Generates mask
    #blobs = detectBlobs(mask)     #Finds contours from video
    #circles = getCircles(blobs)         #Generates list of circles from countour list
    
    #circlesFrame = drawCirclesFrame(frame,blobs)
    #tableFrame = drawTableFrame(frame,table)
    
    if WRITE_MASK_VIDEO:
        maskWriter.write(mask)
    if WRITE_CIRCLES_VIDEO:
        circlesWriter.write(circlesFrame)
    
    print(count)
    tableWriter.write(H)
    
    #circlesFrame = imutils.resize(circlesFrame, width=850)
    #cv2.imshow('frame',imutils.resize(frame, width=850))
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    count = count+1
    if(count > 180):
        break
        
if WRITE_CIRCLES_VIDEO:
    circlesWriter.release()
if WRITE_MASK_VIDEO:
    maskWriter.release()
tableWriter.release()
cap.release()
cv2.destroyAllWindows()