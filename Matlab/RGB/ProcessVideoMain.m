% Script for demo 4/24/16
clc;
close all;
clear;

% limits for clipping the video
x_min = 20;
x_max = 500;
y_min = 514;
y_max = 843;
d_x = x_max-x_min+1;
d_y = y_max-y_min+1;

% Load the video
filename = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\VideoClip1.mp4';
frame_cnt = 0;
vidRead = VideoReader(filename);
vidRead.CurrentTime = 3.8;

% Output video
outFilename = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\RecognitionDemo2.avi';
vidWrite = VideoWriter(outFilename);
vidWrite.FrameRate = vidRead.FrameRate/2;
open(vidWrite);

collision = false;
while frame_cnt <= 400
    frame_cnt = frame_cnt + 1;
    vidFrame = readFrame(vidRead);
    clippedFrame = vidFrame(x_min:x_max,y_min:y_max,:);
    
    % display the clipped frame
    imshow(clippedFrame);
    
    % Get the ball coordinates
    BW = BinaryPoolImage(clippedFrame);
    if collision == false
        [X, Y, collision] = BallCoordBeforeCollision(BW);
    else
        [X, Y] = BallCoordAfterCollision(BW);
    end
    
    hold on
    scatter(X, Y);
    
    % Label the coordinates
    L = LabelBallCoordinates(clippedFrame, X, Y);
    for i=1:length(L)
        text(X(i)+2,Y(i)+2,int2str(L(i)),'HorizontalAlignment','right', 'Color', 'white');
    end
    hold off
    
    % Save the image to the output video
    frame = getframe;
    writeVideo(vidWrite, frame);
   
    pause(1/vidRead.FrameRate);
    
    % Save the last frame for a sec
    if (frame_cnt == 400)
        for i=1:60
            writeVideo(vidWrite, frame);
        end
    end
end

close(vidWrite);
