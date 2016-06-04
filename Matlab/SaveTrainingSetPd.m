%Script to get the probablity density for hues and value from the trainings
%set and save these to a csv file.
clc;
close all;
clear;

%Directory to save the files to
directory = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\';

%Read the image identifiers
R = 8;
R_sq = R^2;
ball_cnt = 17;
bin_cnt = 255;
M = csvread('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\ImageClassification.csv');
[M_l, M_w] = size(M);
image_cnt = M_l/ball_cnt;

% Compute the average HSV histograms for each ball type
idx_train = M(:, 3) == 1;
M_train = M(idx_train, :);
[image_train, ~] = size(M_train);
pixel_cnt = zeros(ball_cnt);
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

% Need to "wrap" axis for red, maroon, purple classification
ball_id = [3:4 7 11 15];
pd_data = zeros(256, length(ball_id)+1);
pd_data(1,2:length(ball_id)+1) = ball_id;
x_values = -0.5:1/254:0.5;
pd_data(2:256,1) = transpose(x_values);
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue_high = HSV_pixels(id, 1:pixel_cnt(id), 1) >= 0.5;
    Hue_wrapped = HSV_pixels(id, 1:pixel_cnt(id), 1);
    Hue_wrapped(Hue_high) = Hue_wrapped(Hue_high) - 1;
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue_wrapped),'Kernel','Kernel','epanechnikov');
    
    % calc the pd
    y = pdf(pd, x_values);
    pd_data(2:256,i+1)=transpose(y);
end

%Save to file
dlmwrite(strcat(directory,'ReddishHuePd.csv'), pd_data);

% Normal balls
ball_id = [1:2 5:6 9:10 12:14 16];
pd_data = zeros(256, length(ball_id)+1);
pd_data(1,2:length(ball_id)+1) = ball_id;
x_values = 0:1/254:1;
pd_data(2:256,1) = transpose(x_values);
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = HSV_pixels(id, 1:pixel_cnt(id), 1);
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue),'Kernel','Kernel','epanechnikov');
      
    % calc the pd
    y = pdf(pd, x_values);
    pd_data(2:256,i+1)=transpose(y);
end

%Save to file
dlmwrite(strcat(directory,'NormalHuePd.csv'), pd_data);

% For white, black ball use the value
ball_id = [8];
pd_data = zeros(256, length(ball_id)+1);
pd_data(1,2:length(ball_id)+1) = ball_id;
x_values = 0:1/254:1;
pd_data(2:256,1) = transpose(x_values);
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = HSV_pixels(id, 1:pixel_cnt(id), 3);
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue),'Kernel','Kernel','epanechnikov');
    
    % calc the pd
    y = pdf(pd, x_values);
    pd_data(2:256,i+1)=transpose(y);
end

%Save to file
dlmwrite(strcat(directory,'ValuePd.csv'), pd_data);
