import numpy as np
import cv2
import imutils
from colorSelection import colorSelection

import Tkinter as Tk

root = Tk.Tk()
root.withdraw()
CS=colorSelection(root)
CS.grid()
root.mainloop()