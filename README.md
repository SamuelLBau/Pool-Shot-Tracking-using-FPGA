Pool-Shot-Tracking-using-FPGA
===============================
Initial code will be higher level, later in the quarter we will move to lower level c code.


Pool ball subbtraction(April 11th)
--------------------------------
The purpose of this goal is to take a well-cropped image of a pool table, and subtract all colors that are determined to be the table. What remains after the subtraction is potentially a pool ball, and will be analyzed by later algorithms.
<a href="https://www.youtube.com/watch?v=DhBfrnDcqEQ"
target="_blank"><img src="http://img.youtube.com/vi/DhBfrnDcqEQ/0.jpg" 
alt="TABLE ISOLATION DEMO" width="360" height="270" border="10" /></a>


Collect an hour of pool footage(April 15th)
-----------------------------------------
The purpose of this goal is to collect a decent amount of footage to run through our algorithms, preferably under varied light conditions.


Pool ball detection
-------------------

Dynamic Table Identification(April 30th)
----------------------------
In the interest of easing physics calculations, as well as improving pool ball detection, the bounds of the table should be identified and transformed to fill the frame.. This goal involves detecting the pool table, then cropping and rotating it in order to take up the entire frame, which will standardize calculations later in the pipeline.
<a href="https://www.youtube.com/watch?v=-fDlGlp3wvo"
target="_blank"><img src="http://img.youtube.com/vi/-fDlGlp3wvo/0.jpg" 
alt="TABLE ISOLATION DEMO" width="360" height="270" border="10" /></a>


Improved Ball detection
-----------------------

Convert all code to C/C++
-------------------------

