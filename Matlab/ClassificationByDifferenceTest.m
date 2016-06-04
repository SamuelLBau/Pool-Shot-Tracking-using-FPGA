% Old version that attempts to calculate params based on subtracting the
% master and the ball H,L, or V distribution.

%Script to compute the parameters for classifying the 16 balls based on
%training set frames
clc;
close all;
clear;

%Read the image identifiers
R = 8;
R_sq = R^2;
ball_cnt = 17;
bin_cnt = 200;
M = csvread('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\ImageClassification.csv');
[M_l, M_w] = size(M);
image_cnt = M_l/ball_cnt;

% Compute the average HSV histograms for each ball type
pixel_cnt = zeros(ball_cnt);
for id=1:image_cnt
    first_ball_id = (id-1)*ball_cnt+1;
    
    % Do this only for training images
    if (M(first_ball_id, 2) ~= 1)
        continue;
    end
        
    % Read in the frame
    image_id = M(first_ball_id, 1);
    filename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Img_',int2str(image_id),'.png');
    RGB = imread(filename);
    [img_width, img_length,~] = size(RGB);
    
    % Convert the frame to HSV
    HSV = rgb2hsv(RGB);
    
    % For each ball
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        % Crop the frame into ball images based on the coordinates 
        % specified in the classification
        xmin = M(row, 5)-R;
        if xmin<1
            xmin = 1;
        end
        xmax = M(row, 5)+R;
        if xmax > img_width
            xmin = img_width;
        end
        
        ymin = M(row, 4)-R;
        if ymin<1
            ymin = 1;
        end
        ymax = M(row, 4)+R;
        if ymax > img_length
            ymax = img_length;
        end

        for x=1:xmax
            for y = 1:ymax
                if (x-M(row, 5))^2+(y-M(row, 4))^2 <= R_sq
                    pixel_cnt(M(row, 3)+1) = pixel_cnt(M(row, 3)+1)+1;
                    HSV_pixels(M(row, 3)+1, pixel_cnt(M(row, 3)+1), :) = HSV(x,y,:);
                end
            end
        end
    end
end

% For each ball, compute a histogram to differentiate balls
masterHistVals = zeros(ball_cnt, bin_cnt);
for id=2:ball_cnt
    % Differentiate colored balls by hue.
    chanel = 1;
    
    % Differnetiate black ball by value
    if id == 9
        chanel=3;
        
    % Differentate white ball by saturation
    elseif  id == 17
        chanel = 2;
    end
    h = histogram(HSV_pixels(id, 1:pixel_cnt(id), chanel), bin_cnt);
    masterHistVals(id,:)=h.Values./pixel_cnt(id);
end

% Save the histogram to file. Ignore the first entry as it is "not a ball."
matrixFilename = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\MasterHistogramMatrix.csv';
dlmwrite(matrixFilename, masterHistVals(2:ball_cnt, :));

% For each ball compute the difference in HLV distribution from Master.
idx_train = M(:, 3) == 1;
M_train = M(idx_train, :);
[image_train, ~] = size(M_train);
differenceFromMaster = zeros(ball_cnt, ball_cnt, image_train);
for id=1:image_train
    first_ball_id = (id-1)*ball_cnt+1;
        
    % Read in the frame
    image_id = M(first_ball_id, 1);
    filename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Img_',int2str(image_id),'.png');
    RGB = imread(filename);
    [img_width, img_length,~] = size(RGB);
    
    % Convert the frame to HSV
    HSV = rgb2hsv(RGB);
    
    % For each ball
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        % Crop the frame into ball images based on the coordinates 
        % specified in the classification
        xmin = M(row, 5)-R;
        if xmin<1
            xmin = 1;
        end
        xmax = M(row, 5)+R;
        if xmax > img_width
            xmin = img_width;
        end
        
        ymin = M(row, 4)-R;
        if ymin<1
            ymin = 1;
        end
        ymax = M(row, 4)+R;
        if ymax > img_length
            ymax = img_length;
        end
        
        ball_pixels = zeros(R_sq*R_sq, 3);
        ball_pixel_cnt = 0;
        for x=1:xmax
            for y = 1:ymax
                if (x-M(row, 5))^2+(y-M(row, 4))^2 <= R_sq
                    ball_pixel_cnt = ball_pixel_cnt+1;
                    ball_pixels(ball_pixel_cnt,:) = HSV(x,y,:);
                end
            end
        end
        
        % Chanel to compare
        for chanel = 1:3
            if chanel == 1
                balls_compare = [1:8 10:16];
            elseif chanel ==3
                balls_compare = 9;
            else
                balls_compare = 17;
            end
            
            h = histogram(ball_pixels(1:ball_pixel_cnt, chanel), bin_cnt);
            values = h.Values./ball_pixel_cnt;
            close all

            for j=1:length(balls_compare)
                dif = 0;
                for i=1:bin_cnt
                    dif = dif + abs(masterHistVals(balls_compare(j), i)-values(i));
                end
                differenceFromMaster(balls_compare(j),M(row, 3)+1,id) = dif;
            end
        end
    end
end

% Create a histogram of the different differences in accuracy
for i=2:9
    figure
    for j=2:9
        histogram(differenceFromMaster(i,j,:),(0.05:0.1:1.95));
        hold on
    end
    legend('1','2','3','4','5','6','7','8');
    hold off
end