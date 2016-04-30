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

def getHSVMaskExcludeTable(H,THRESHOLD=15000):
	histogram = cv2.calcHist([H], [0], None, [180], [0, 180])

	H[histogram[H][:,:,0] > THRESHOLD] = 0
	#print(hsv[:,:,0].shape)
	H = cv2.threshold(H,1,255,cv2.THRESH_BINARY)[1]
	return H

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

def getMask(H):
    #Accepts just HUE as input
    mask = getHSVMaskExcludeTable(H)
    mask = cv2.erode(mask, None, iterations=4)
    mask = cv2.dilate(mask, None, iterations=9)
    
    return mask
    
def detectBlobs(frame,mask):

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

def drawFrame(frame,circles):
    if(circles != None):
        for c in circles:
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            if M["m00"] > 0:
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                # only proceed if the radius meets a minimum size
                if radius > 20 and radius < 50:
                    # draw the circle and centroid on the frame,
                    # then update the list of tracked points
                    cv2.circle(frame, (int(x), int(y)), int(radius),
                        (0, 255, 255), 2)
                    cv2.circle(frame, center, 5, (0, 0, 255), -1)
                    

    return frame

    
def getTable(hsv,frame=None,writer=None):        
    #Takes in a gaussian blurred image in HSV domain
    #This method still assumes the table takes up most of the image
    #It outputs the cropped / rotated image in hsv space
    THRESHOLD = 3000
    contourMode = cv2.RETR_LIST
    contourMethod = cv2.CHAIN_APPROX_SIMPLE
    
    
    mask = hsv  #hsv is held because it is needed for the bitwise_and later
    width,length,layers = mask.shape
    
    histogram = cv2.calcHist([hsv], [0], None, [180], [0, 180])
   
    mask = mask[:,:,0]
    thing = histogram[hsv[:,:,0]][:,:,0]
    mask[thing < THRESHOLD] = 0
    mask = cv2.threshold(mask,40,255,cv2.THRESH_BINARY)[1]
    
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
    
    hull = cv2.convexHull(blobs[maxContourIndex],returnPoints = True)
    tableMask = cv2.bitwise_and(hsv[:,:,0],cv2.drawContours(np.zeros((width,length),np.uint8),[hull],0,(255),-1))
    
    #Threshold image, should help isolate table
    THRESHOLD = width*length*.3
    histogram = cv2.calcHist([mask], [0], None, [180], [0, 180])
    
    #tableMask[histogram[tableMask][:,:,0] < THRESHOLD] = 0
    
    minLineLength = 500
    maxLineGap = 1
    canny = cv2.Canny(mask,100,100,apertureSize = 3)
    
    showImage = imutils.resize(tableMask, width=850)
    cv2.imshow('frame',showImage)
    
    lines = cv2.HoughLines(canny,2,np.pi/180*1,200)
    if(lines != None):
        cont = 0
        print(len(lines))
        for line in lines:
            for rho,theta in line:
                a = np.cos(theta)
                b = np.sin(theta)
                x0 = a*rho
                y0 = b*rho
                x1 = int(x0 + 1000*(-b))
                y1 = int(y0 + 1000*(a))
                x2 = int(x0 - 1000*(-b))
                y2 = int(y0 - 1000*(a))
                #cv2.line(mask,(x1,y1),(x2,y2),(255,255,0),2)
        #for [[x1,y1,x2,y2]] in lines:
         #   cv2.line(mask,(x1,y1),(x2,y2),(255,255,0),2)
          #  cont=cont+1
        #print(cont)
    
    
    showImage = imutils.resize(mask, width=850)
    #cv2.imshow('frame',showImage)
    
    rect = cv2.minAreaRect(blobs[maxContourIndex])
    box = np.int0(cv2.boxPoints(rect))
    
    #rotMatrix = getTable2DRotation(box,rect,width,length)
    rotMatrix = getAffineRotation(box,rect,width,length)
    
    #This crops the image appropriately
    #AFTER THIS POINT, mask is re-used to save space
    #All references to mask could be replaced with OUTFRAME
    outFrame = cv2.drawContours(np.zeros((width,length),np.uint8),[box],0,(255),-1)
    #THIS IS JUST SOME DEBUG CODE
    croppedFrame = frame
    if(frame !=None):
        showImage = frame
        showImage[:,:,0] =cv2.bitwise_and(frame[:,:,0],outFrame)
        showImage[:,:,1] =cv2.bitwise_and(frame[:,:,1],outFrame)
        showImage[:,:,2] =cv2.bitwise_and(frame[:,:,2],outFrame)
    
        showImage = cv2.warpAffine(showImage,rotMatrix,(length,width))
        croppedFrame = showImage
        showImage = imutils.resize(showImage, width=850)
        #cv2.imshow('frame',showImage)
        if(writer != None):
            writer.write(showImage)
    
    outFrame =cv2.bitwise_and(hsv[:,:,0],outFrame)
    
    outFrame = cv2.warpAffine(outFrame,rotMatrix,(length,width))
    

    #This simply displays the image
    return [outFrame,croppedFrame]        #TEMPORARY, normally return table (holes) info

def getAffineRotation(box,rect,width,length):
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