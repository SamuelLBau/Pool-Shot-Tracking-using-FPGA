Pool-Shot-Tracking-using-FPGA
===============================
Initial code will be higher level, later in the quarter we will move to lower level c code.


Pool ball subbtraction(April 11th)
----------------------------------
The purpose of this goal is to take a well-cropped image of a pool table, and subtract all colors that are determined to be the table. What remains after the subtraction is potentially a pool ball, and will be analyzed by later algorithms.
<a href="https://www.youtube.com/watch?v=DhBfrnDcqEQ"
target="_blank"><img src="http://img.youtube.com/vi/DhBfrnDcqEQ/0.jpg" 
alt="POOL BALL SUBBTRACTION" width="360" height="270" border="10" /></a>


Collect an hour of pool footage(April 15th)
-------------------------------------------
The purpose of this goal is to collect a decent amount of footage to run through our algorithms, preferably under varied light conditions.



Recognition 80% accurate and integrate with detection end of pipeline(April 26th)
--------------------------------------------------------------------------------
For these two milestones we designed a preliminary algorithm in RGB space. We tested using both the median pixel hue, R, G, and B values of the balls and the R,G,B histograms in classifying and had worse results using the median. We also integrated this with the non-optimized ball detection using Matlab and the results are shown in the video below. This did not identify the “racked” balls accurately so we implemented “racked” and “un-racked” states for detection. We plan to improve on this in Sprint 2.

<a href="https://www.youtube.com/watch?v=HbJJNquY9z8"
target="_blank"><img src="http://img.youtube.com/vi/HbJJNquY9z8/0.jpg" 
alt="POOL BALL RECOGNITION" width="360" height="270" border="10" /></a>



Dynamic Table Identification(April 30th)
----------------------------------------
In the interest of easing physics calculations, as well as improving pool ball detection, the bounds of the table should be identified and transformed to fill the frame.. This goal involves detecting the pool table, then cropping and rotating it in order to take up the entire frame, which will standardize calculations later in the pipeline.
<a href="https://www.youtube.com/watch?v=-fDlGlp3wvo"
target="_blank"><img src="http://img.youtube.com/vi/-fDlGlp3wvo/0.jpg" 
alt="TABLE ISOLATION DEMO" width="360" height="270" border="10" /></a>


Convert all code to C/C++(May 14th)
-----------------------------------
Before being implemented in HLS, we will need to convert all of our code from high level Python, to lower level C/C++. This may have the additional benefit of improving performance.



Pool ball detection
-------------------

Improved Ball detection
-----------------------


Libraries Compiled using FPGA synthesizable code
------------------------------------------------
