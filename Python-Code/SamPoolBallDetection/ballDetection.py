import numpy as np
import cv2

import imutils

def getHoughCircles(img,minRadius=2,maxRadius=12,minDistance=1):
	img = cv2.GaussianBlur(img,(3,3),0)
	img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,minDistance, param1=50,param2=30,minRadius=minRadius,maxRadius=maxRadius)
	return circles
   
def getHoughLines(img,minLength,minSeparation):
	gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	edges = cv2.Canny(gray,50,150,apertureSize = 3)
	lines = cv2.HoughLinesP(edges,1,np.pi/180,180,minLength,minSeparation)
	return lines

def drawCirclesOnFrame(circles,frame):
	if(circles != None):
		circles = np.uint16(np.around(circles))
		for i in circles[0,:]:
			# draw the outer circle
			cv2.circle(frame,(i[0],i[1]),i[2],(0,255,0),2)
			# draw the center of the circle
			cv2.circle(frame,(i[0],i[1]),2,(0,0,255),3)
	return frame

def subtractBackground(fgbg,frame):
	#gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)	
	fgmask = fgbg.apply(frame)
	return fgmask

def drawBlobs(img):
	gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	# set the parameters
	params = cv2.SimpleBlobDetector_Params()
	params.filterByArea = True
	params.minArea = 20
	params.maxArea = 30
	params.filterByCircularity = True
	params.minCircularity = 0.7
	# declare the blob detector
	detector = cv2.SimpleBlobDetector_create(params)
	keypoints = detector.detect(img)
	im_with_keypoints = cv2.drawKeypoints(img, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	return im_with_keypoints

def getHSVMaskExcludeTable(hsv,THRESHOLD=7000):
    histogram = cv2.calcHist([hsv], [0], None, [180], [0, 180])
    print("1")
    mask = cropHistogram(hsv,histogram,THRESHOLD=THRESHOLD)
    print("2")
    return mask
def cropHistogram(frame,histogram,THRESHOLD):
    #Assumes frame is 2D and has a maximum value equal to number of bins in histogram
    width,length = frame.shape
    mask = frame.copy()
    for i in range(0,width):
        for j in range(0,length):
            if(histogram[frame[i,j]] > THRESHOLD):
                mask[i,j] = 0
            else:
                mask[i,j] = 255
    return mask
def getHSVMaskIncludeBalls(hsv):
	#These are currently hard-coded, hopefully we can do something else with it later
	outputArray = np.array([255,255,255])

	lower_red = np.array([175,0,0])
	upper_red = np.array([180,255,255])
	red_mask = cv2.inRange(hsv, lower_red, upper_red)

	lower_yellow = np.array([20,0,0])
	upper_yellow = np.array([25,255,255])
	yellow_mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

	lower_blue = np.array([100,16,26])
	upper_blue = np.array([115,50,40])
	blue_mask = cv2.inRange(hsv, lower_blue, upper_blue)

	lower_white = np.array([22,0,0])
	upper_white = np.array([33,255,255])
	white_mask = cv2.inRange(hsv, lower_white, upper_white)


	lower_violet = np.array([130,0,00])
	upper_violet = np.array([170,255,255])
	violet_mask = cv2.inRange(hsv, lower_violet, upper_violet)

	lower_black = np.array([25,0,0])
	upper_black = np.array([50,255,255])
	black_mask = cv2.inRange(hsv, lower_black, upper_black)

	lower_orange = np.array([5,0,0])
	upper_orange = np.array([20,255,255])
	orange_mask = cv2.inRange(hsv, lower_orange, upper_orange)

	lower_green = np.array([45,0,0])
	upper_green = np.array([67,255,255])
	green_mask = cv2.inRange(hsv, lower_green, upper_green)

	outMask = red_mask
	outMask =cv2.bitwise_or(outMask,yellow_mask)
	outMask =cv2.bitwise_or(outMask,blue_mask)
	outMask =cv2.bitwise_or(outMask,white_mask)
	outMask =cv2.bitwise_or(outMask,violet_mask)
	outMask =cv2.bitwise_or(outMask,black_mask)
	outMask =cv2.bitwise_or(outMask,orange_mask)
	outMask =cv2.bitwise_or(outMask,green_mask)

	return outMask

def getHSVMask(hsv,threshold):
    #Accepts just HUE as input
    mask = getHSVMaskExcludeTable(hsv[:,:,0],THRESHOLD=threshold)
    mask2 = cv2.erode(mask, None, iterations=4)
    mask3 = cv2.dilate(mask2, None, iterations=4)
    
    return mask3
def erodeAndDilate(mask,erodeIT=0,dilateIT=0):
    mask = cv2.erode(mask, None, iterations=erodeIT)
    mask = cv2.dilate(mask, None, iterations=dilateIT)
    return mask
    
def detectBlobs(mask):

    blobs = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
    return blobs
	#return mask

def getCircles(blobs,minRadius=0,maxRadius = 10000):
    circles = []
    moments = []
    if len(blobs) > 0:
        # find the largest contour in the mask, then use
        # it to compute the minimum enclosing circle and
        # centroid
        #c = max(cnts, key=cv2.contourArea)
        for c in blobs:
            moment = cv2.moments(c)
            circle = cv2.minEnclosingCircle(c)
            radius = circle[1]
            if radius > minRadius and radius < maxRadius:
                circles.append(circle)
                moments.append(moment)
                    
    return [circles,moments]
def drawCirclesOnFrame(frame,circles,moments):
    length = len(moments)
    i=0
    while i < length:
        M = moments[i]
        ((x,y),radius) = circles[i]
        if M["m00"] > 0:
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
            # only proceed if the radius meets a minimum size
            cv2.circle(frame, (int(x), int(y)), int(radius),
                (0, 255, 255), 2)
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
        
        
        i=i+1
    return frame
def drawFrame(frame,circles,minRadius=0,maxRadius=10000):
    if(circles != None):
        for c in circles:
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            if M["m00"] > 0:
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                # only proceed if the radius meets a minimum size
                if radius > minRadius and radius < maxRadius:
                    # draw the circle and centroid on the frame,
                    # then update the list of tracked points
                    cv2.circle(frame, (int(x), int(y)), int(radius),
                        (0, 255, 255), 2)
                    cv2.circle(frame, center, 5, (0, 0, 255), -1)
                    

    return frame

def getTableMask(hsv):
    lower_table = np.array([90,0,0])
    upper_table = np.array([150,102,102])
    table_mask = cv2.inRange(hsv, lower_table, upper_table)
    return table_mask
    
    
def getTable(hsv,THRESHOLD=30000):        
    #Takes in a gaussian blurred image in HSV domain
    #This method still assumes the table takes up most of the image
    #It outputs the cropped / rotated image in hsv space
    contourMode = cv2.RETR_EXTERNAL
    contourMethod = cv2.CHAIN_APPROX_SIMPLE
    
    
    #mask = hsv  #hsv is held because it is needed for the bitwise_and later
    width,length,layers = hsv.shape
    mask = getTableMask(hsv.copy())
    #histogram = cv2.calcHist([hsv], [0], None, [180], [0, 180])
    Nmask = mask.copy()
    #mask = mask[:,:,0]
    #thing = histogram[hsv[:,:,0]][:,:,0]
    #mask[thing < THRESHOLD] = 0
    #mask = cv2.threshold(mask,1,255,cv2.THRESH_BINARY)[1]
    
    
    outFrame = imutils.resize(mask, width=850)
    cv2.imshow('frame', outFrame)
    
    print("here1")
    print(mask)
    getTable_blobs = cv2.findContours(Nmask ,contourMode,contourMethod)[1]
    print("Here2:")
    maxContourArea = 0
    maxContourIndex = 0
    i=0
    for blob in getTable_blobs:
        area = cv2.contourArea(blob,False)
        
        if(area > maxContourArea):
            maxContourArea = area
            maxContourIndex = i
        i=i+1
    if len(getTable_blobs) != 0:
        rect = cv2.minAreaRect(getTable_blobs[maxContourIndex])
        box = np.int0(cv2.boxPoints(rect))
    else:
        box = [[0,0],[0,width],[length,width],[length,0]]
    
    return box
    

def getAffineRotation(box,width,length):
    #TODO: This seems to mirror image for some reason, look into that
    yVarMax = 0
    xVarMax = 0
    for i in range(0,3):
        for j in range(0,3):
            yVar = box[i][1]-box[j][1]
            xVar = box[i][0]-box[j][0]
            
            if(yVar > yVarMax):
                yVarMax = yVar
            if(xVar > xVarMax):
                xVarMax = xVar
    if(yVarMax > xVarMax):
        TBOX = [box[1],box[2],box[3]]
    else:
        TBOX = [box[0],box[1],box[2]]

    originalCoords = np.float32([TBOX[0],TBOX[1],TBOX[2]])
    newCoords = np.float32([[0,0],[0,width],[length,width]])
    return cv2.getAffineTransform(originalCoords,newCoords)

def rotateFrame(box,frame):
    #should work on both frame and HSV
    #rotMatrix = getTable2DRotation(box,rect,width,length)
    width,length,layers = frame.shape
    rotMatrix = getAffineRotation(box,width,length)
    
    #This crops the image appropriately
    #AFTER THIS POINT, mask is re-used to save space
    #All references to mask could be replaced with OUTFRAME
    mask = cv2.drawContours(np.zeros((width,length),np.uint8),[box],0,(255),-1)
    outFrame = frame.copy()
    #THIS IS JUST SOME DEBUG CODE   if(frame !=None):
    outFrame[:,:,0] =cv2.bitwise_and(frame[:,:,0],mask)
    outFrame[:,:,1] =cv2.bitwise_and(frame[:,:,1],mask)
    outFrame[:,:,2] =cv2.bitwise_and(frame[:,:,2],mask)
    
    outFrame[:,:,0] = cv2.warpAffine(outFrame[:,:,0],rotMatrix,(length,width))
    outFrame[:,:,1] = cv2.warpAffine(outFrame[:,:,1],rotMatrix,(length,width))
    outFrame[:,:,2] = cv2.warpAffine(outFrame[:,:,2],rotMatrix,(length,width))
    

    #This simply displays the image
    return outFrame        #TEMPORARY, normally return table (holes) info
    
def averageBox(box,newbox,count):
    count =float(count)
    for i in range(0,3):
        box[i][0] = box[i][0]*(count)/(count+1) + newbox[i][0]/(count+1)
        box[i][1] = box[i][1]*(count)/(count+1) + newbox[i][1]/(count+1)
    return box
