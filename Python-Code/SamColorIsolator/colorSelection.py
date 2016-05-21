import Tkinter as Tk
import numpy as np
import cv2
import imutils

class colorSelection(Tk.Toplevel):
    runButton = 0
    HLowBox = 0
    HHighBox = 0
    SLowBox = 0
    SHighBox = 0
    VLowBox = 0
    VHighBox = 0
    
    HHLowTV=0
    HHighTV = 0
    SLowTV = 0
    SHighTV = 0
    VLowTV = 0
    VHighTV = 0
    
    cap=0
    begun = 0
    def __init__(self,parent=None):
        Tk.Toplevel.__init__(self,parent,bg='#F0F0F0',bd=1,relief='sunken',width=100,height=100)
        
        VIDEO_IN_NAME = "LightWhiteBalance"
        VIDEO_EXTENSION = ".mp4"
        VIDEO_IN_NAME = VIDEO_IN_NAME+ VIDEO_EXTENSION
        fourcc = cv2.VideoWriter_fourcc("X","V","I","D")


        self.cap = cv2.VideoCapture(VIDEO_IN_NAME)
        
        self.runButton = Tk.Button(self,width=15,text="Run, q to stop",command=self.mainLoop)
        self.runButton.grid(row=0,column=1)
        
        
        self.HLowTV = Tk.StringVar()
        self.HLowTV.trace("w", lambda name, index, mode, HLowTV = self.HLowTV.get() : self.changeHLowTV())
        self.HLowBox = Tk.Entry(self,width=10,textvariable=self.HLowTV)
        self.HLowBox.grid(row=1,column=0)
        
        self.HHighTV = Tk.StringVar()
        self.HHighTV.trace("w", lambda name, index, mode, HHighTV = self.HHighTV.get() : self.changeHHighTV())
        self.HHighBox = Tk.Entry(self,width=10,textvariable=self.HHighTV)
        self.HHighBox.grid(row=1,column=2)
        
        self.SLowTV = Tk.StringVar()
        self.SLowTV.trace("w", lambda name, index, mode, SLowTV = self.SLowTV.get() : self.changeSLowTV())
        self.SLowBox = Tk.Entry(self,width=10,textvariable=self.SLowTV)
        self.SLowBox.grid(row=2,column=0)
        
        self.SHighTV = Tk.StringVar()
        self.SHighTV.trace("w", lambda name, index, mode, SHighTV = self.SHighTV.get() : self.changeSHighTV())
        self.SHighBox = Tk.Entry(self,width=10,textvariable=self.SHighTV)
        self.SHighBox.grid(row=2,column=2)
        
        self.VLowTV = Tk.StringVar()
        self.VLowTV.trace("w", lambda name, index, mode, VLowTV = self.VLowTV.get() : self.changeVLowTV())
        self.VLowBox = Tk.Entry(self,width=10,textvariable=self.VLowTV)
        self.VLowBox.grid(row=3,column=0)
        
        self.VHighTV = Tk.StringVar()
        self.VHighTV.trace("w", lambda name, index, mode, VHighTV = self.VHighTV.get() : self.changeVHighTV())
        self.VHighBox = Tk.Entry(self,width=10,textvariable=self.VHighTV)
        self.VHighBox.grid(row=3,column=2)
       
    def mainLoop(self):
       
        try:
            HHigh = int(self.getHHigh())
        except ValueError:
            HHigh = 180
        try:
            HLow = int(self.getHLow())
        except ValueError:
            HLow = 0
        
        
        try:
            SHigh = int(self.getSHigh())
        except ValueError:
            SHigh = 256
        try:
            SLow = int(self.getSLow())
        except ValueError:
            SLow = 0
        
        
        try:
            VHigh = int(self.getVHigh())
        except ValueError:
            VHigh = 256
        try:
            VLow = int(self.getHLow())
        except ValueError:
            VLow = 0
        
        while(self.cap.isOpened()):
            ret, frame = self.cap.read()
            frame = cv2.GaussianBlur(frame.copy(),(3,3),0)
            hsv = cv2.cvtColor(frame.copy(), cv2.COLOR_BGR2HSV)
            #TODO: Code that thresholds stuff
            outFrame = self.thresholdFrame(frame,hsv,HHigh=HHigh,HLow=HLow,SHigh=SHigh,SLow=SLow,VHigh=VHigh,VLow=VLow)
            
            showFrame = imutils.resize(outFrame.copy(), width=850)
            cv2.imshow("Cropped Frame",showFrame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
        self.begun = 0
        cv2.destroyAllWindows()
        
    def thresholdFrame(self,frame,hsv,HHigh=180,HLow=0,SHigh=255,SLow=0,VHigh=255,VLow=0):
        lower_colors = np.array([HLow,SLow,VLow])
        upper_colors = np.array([HHigh,SHigh,VHigh])
        mask = cv2.inRange(hsv,lower_colors,upper_colors)
        
        print(mask.shape)
        print(hsv.shape)
        print(frame.shape)
        mask = cv2.merge((mask,mask,mask))
        outFrame = cv2.bitwise_and(mask,frame)
        
        return outFrame
        
    def getHLow(self):
        return self.HLowTV.get()
    def getHHigh(self):
        return self.HHighTV.get()
    def getSLow(self):
        return self.SLowTV.get()
    def getSHigh(self):
        return self.SHighTV.get()
    def getVLow(self):
        return self.VLowTV.get()
    def getVHigh(self):
        return self.VHighTV.get()
        
        
        
    def changeHLowTV(self):
        return
    def changeHHighTV(self):
        return
    def changeSLowTV(self):
        return
    def changeSHighTV(self):
        return
    def changeVLowTV(self):
        return
    def changeVHighTV(self):
        return
        