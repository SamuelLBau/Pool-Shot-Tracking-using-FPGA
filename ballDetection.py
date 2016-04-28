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

def getHSVMaskExcludeTable(hsv,THRESHOLD=3000,XTOP=148,XBOT=1800,YTOP=144,YBOT=935):
	croppedHSV = hsv[YTOP:YBOT,XTOP:XBOT]
	histogram = cv2.calcHist([croppedHSV], [0], None, [180], [0, 180])

	croppedHSV[histogram[croppedHSV[:,:,0]] > THRESHOLD] = 0
	#print(hsv[:,:,0].shape)
	croppedHSV = cv2.threshold(croppedHSV,1,255,cv2.THRESH_BINARY)[1]
	hsv = cv2.copyMakeBorder(croppedHSV,YTOP,(1080-YBOT),XTOP,(1920-XBOT),cv2.BORDER_CONSTANT,0)
	return hsv[:,:,0]

def getHSVMaskIncludeBalls(hsv):
    #This method is outdated, it works by adding each color for each ball to the mask
    #Appears more efficient to instead subtract the pool table
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

def getMask(frame):

    frame = cv2.GaussianBlur(frame,(3,3),0)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = getHSVMaskExcludeTable(hsv)              #This method currently appears better
    
    
    #May add more stages here to improve ball finding
    erodeAndDilate(hsv,4,9)
    
    return mask

def erodeAndDilate(mask,erodeIT=0,dilateIT=0):
    mask = cv2.erode(mask, None, iterations=erodeIT)
    mask = cv2.dilate(mask, None, iterations=dilateIT)
    return mask
def detectBlobs(mask):

    blobs = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
    return blobs
	#return mask

def getCircles(blobs):
    circles = []
    if len(blobs) > 0:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
		#c = max(cnts, key=cv2.contourArea)
		for c in blobs:
			circles.append(cv2.minEnclosingCircle(c))
                    
    return circles

def drawCirclesFrame(frame,blobs,minradius=20,maxradius=50):
    #Given an input frame and a list of blobs, generate a list of circles blob
    if(blobs != None):
        for c in blobs:
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            if M["m00"] > 0:#Solves a div/0 issues we were having
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                # only proceed if the radius meets a minimum size
                if radius > minradius and radius < maxradius:
                    # draw the circle and centroid on the frame,
                    # then update the list of tracked points
                    cv2.circle(frame, (int(x), int(y)), int(radius),
                        (0, 255, 255), 2)
                    cv2.circle(frame, center, 5, (0, 0, 255), -1)
                    
    return frame
    
def generateCircleList(frame):
    mask = getMask(frame)               #Generates mask
    blobs = detectBlobs(mask)     #Finds contours from video
    circles = getCircles(blobs)         #Generates list of circles from countour list
    return circles
def drawTableFrame(frame,table):
    print("Draw table frame")
    
def getTable(frame):        #Takes in a gaussian blurred image
    #TODO: CURRENTLY METHOD DOES NOT CROP PROPERLY, NEED TO TEST WITH DE-FISHEYED VIDEO
    #This method still assumes table makes up majority of image
    THRESHOLD = 3000
    contourMode = cv2.RETR_LIST
    contourMethod = cv2.CHAIN_APPROX_SIMPLE
    
    frame = cv2.GaussianBlur(frame,(3,3),0)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = hsv
    
    histogram = cv2.calcHist([hsv], [0], None, [180], [0, 180])
   
    mask[histogram[mask[:,:,0]] < THRESHOLD] = 0
    mask = cv2.threshold(mask,40,255,cv2.THRESH_BINARY)[1]
    mask = mask[:,:,0]
    
    blobs = cv2.findContours(mask.copy(),contourMode,contourMethod)[1]
    
    maxContourArea = 0
    maxContourIndex = 0
    i=0
    for blob in blobs:
        area = cv2.contourArea(blob,False)
        
        if(area > maxContourArea):
            maxContourArea = area
            maxContourIndex = i
        i=i+1
            
                

    hull = cv2.convexHull(blobs[maxContourIndex])       #This is the shape of the

    rect = cv2.boundingRect(hull)
    topLeft = [rect[0],rect[1]]
    topRight = [rect[0]+rect[2],rect[1]]
    botLeft = [rect[0],rect[1]+rect[3]]
    botRight = [rect[0]+rect[2],rect[1]+rect[3]]
    rectangle = np.array([topLeft,topRight,botRight,botLeft])
    

    showImage = np.zeros(mask.shape,np.uint8)
    showImage = cv2.drawContours(showImage.copy(),[hull],0,(255),-1)
    
    showImage =cv2.bitwise_and(frame[:,:,0],showImage)
    
    #showImage = imutils.resize(showImage, width=850)
    #cv2.imshow('frame', showImage)
    return showImage        #TEMPORARY, normally return table (holes) info
    