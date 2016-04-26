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

def getHSVMaskExcludeTable(hsv):
	THRESHOLD = 3000
	XTOP = 148
	XBOT = 1800
	YTOP = 144
	YBOT = 935
	croppedHSV = hsv[YTOP:YBOT,XTOP:XBOT]
	histogram = cv2.calcHist([croppedHSV], [0], None, [180], [0, 180])

	croppedHSV[histogram[croppedHSV[:,:,0]] > THRESHOLD] = 0
	#print(hsv[:,:,0].shape)
	croppedHSV = cv2.threshold(croppedHSV,1,255,cv2.THRESH_BINARY)[1]
	hsv = cv2.copyMakeBorder(croppedHSV,YTOP,(1080-YBOT),XTOP,(1920-XBOT),cv2.BORDER_CONSTANT,0)
	return hsv[:,:,0]

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

def detectBlobs(frame):
    whiteLower = (27, 0, 0)
    whiteUpper = (33, 255, 255)
    greenLower = (54, 0, 0)
    greenUpper = (70, 255, 255)
    frame = cv2.GaussianBlur(frame,(3,3),0)
	
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

	#greenMask = cv2.inRange(hsv, greenLower, greenUpper)
	#whiteMask = cv2.inRange(hsv, whiteLower, whiteUpper)
	#mask = greenMast
	#mask = cv2.bitwise_or(greenMask, whiteMask)
    mask = getHSVMaskExcludeTable(hsv)
	#mask = getHSVMaskIncludeBalls(hsv)
    #frame = imutils.resize(frame, width=850)
    #mask = imutils.resize(mask, width=850)
	#mask = getHSVMaskIncludeBalls(hsv)
    mask = cv2.erode(mask, None, iterations=4)
    mask = cv2.dilate(mask, None, iterations=9)
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
    center = None
	## only proceed if at least one contour was found
    return cnts
	#return mask

def getCircles(cnts):
    circles = []
    if len(cnts) > 0:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
		#c = max(cnts, key=cv2.contourArea)
		for c in cnts:
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
cap = cv2.VideoCapture("croppedAndRotatedVideo1.mp4")
#fgbg = cv2.bgsegm.createBackgroundSubtractorMOG()
#fgbg = cv2.bgsegm.createBackgroundSubtractorGMG()

while(cap.isOpened()):
    ret, frame = cap.read()
    #bgsub = subtractBackground(fgbg,frame)
    #circles = getHoughCircles(frame)
    #cimg = drawCirclesOnFrame(circles,frame)
    #im_with_keypoints = drawBlobs(frame)
    
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cnts = detectBlobs(frame)
    circles = getCircles(cnts)
    
    outFrame = drawFrame(frame,cnts)
    
    outFrame = imutils.resize(outFrame, width=850)
    cv2.imshow('frame', outFrame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()