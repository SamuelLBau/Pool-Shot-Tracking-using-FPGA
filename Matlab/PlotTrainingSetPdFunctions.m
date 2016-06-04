%Script to plot probablity density functions from the training set for
%report
clc;
close all;
clear;

%Directory to save the files to
directory = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Histogram\';

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
        
    % Read in the frame.cdata
    image_id = M(first_ball_id, 1);
    filename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Img_',int2str(image_id),'.png');
    RGB = imread(filename);
    [img_width, img_length,~] = size(RGB);
    
    % Convert the frame.cdata to HSV
    HSV = rgb2hsv(RGB);
    
    % For each ball
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame.cdata
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        % Crop the frame.cdata into ball images based on the coordinates 
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
fg = figure;
ball_id = [3:4 7];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue_high = HSV_pixels(id, 1:pixel_cnt(id), 1) >= 0.5;
    Hue_wrapped = HSV_pixels(id, 1:pixel_cnt(id), 1);
    Hue_wrapped(Hue_high) = Hue_wrapped(Hue_high) - 1;
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue_wrapped),'Kernel','Kernel','epanechnikov');
    
    % plot the pd
    x_values = -0.5:1/255:0.5;
    y = pdf(pd, x_values);
    plot(x_values,y)
    hold on
end
hold off
xlabel('Transformed Hue');
ylabel('Training set likelihood');
legend('3','4','7')

% Save the image
print(fg,strcat(directory, 'RedishHuePd'),'-dpng');

% Example of striped red ball
fg = figure;
ball_id = [3 11 16];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue_high = HSV_pixels(id, 1:pixel_cnt(id), 1) >= 0.5;
    Hue_wrapped = HSV_pixels(id, 1:pixel_cnt(id), 1);
    Hue_wrapped(Hue_high) = Hue_wrapped(Hue_high) - 1;
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue_wrapped),'Kernel','Kernel','epanechnikov');
    
    % plot the pd
    x_values = -0.5:1/255:0.5;
    y = pdf(pd, x_values);
    plot(x_values,y)
    hold on
end
hold off
xlabel('Transformed Hue');
ylabel('Training set likelihood');
legend('3','11','Cue')

% Save the image
print(fg,strcat(directory, 'StripedRedPd'),'-dpng');

% Solid Normal balls
fg = figure;
ball_id = [1:2 5:6 16];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = HSV_pixels(id, 1:pixel_cnt(id), 1);
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue),'Kernel','Kernel','epanechnikov');
    
    % plot the pd
    x_values = 0:1/255:1;
    y = pdf(pd, x_values);
    plot(x_values,y)
    hold on
end
hold off
xlabel('Hue');
ylabel('Training set likelihood');
legend('1','2','5','6','Cue')

% Save the image
print(fg,strcat(directory, 'SolidHuePd'),'-dpng');

% Example of striped blue ball
fg = figure;
ball_id = [2 10 16];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = HSV_pixels(id, 1:pixel_cnt(id), 1);
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue),'Kernel','Kernel','epanechnikov');
    
    % plot the pd
    x_values = 0:1/255:1;
    y = pdf(pd, x_values);
    plot(x_values,y)
    hold on
end
hold off
xlabel('Hue');
ylabel('Training set likelihood');
legend('2','10','Cue')

% Save the image
print(fg,strcat(directory, 'StripedBluePd'),'-dpng');

% For white, black balls plot the saturation
fg = figure;
ball_id = [8 16];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = HSV_pixels(id, 1:pixel_cnt(id), 2);
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue),'Kernel','Kernel','epanechnikov');
    
    % plot the pd
    x_values = 0:1/255:1;
    y = pdf(pd, x_values);
    plot(x_values,y)
    hold on
end
hold off
xlabel('Saturation');
ylabel('Training set likelihood');
legend('8','Cue')

% Save the image
print(fg,strcat(directory, 'SaturationPd'),'-dpng');

% For white, black balls plot the value
fg = figure;
ball_id = [8 16];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = HSV_pixels(id, 1:pixel_cnt(id), 3);
    
    % fit the distribution with a kernel pd distribution
    pd = fitdist(transpose(Hue),'Kernel','Kernel','epanechnikov');
    
    % plot the pd
    x_values = 0:1/255:1;
    y = pdf(pd, x_values);
    plot(x_values,y)
    hold on
end
hold off
xlabel('Value');
ylabel('Training set likelihood');
legend('8','Cue')

% Save the image
print(fg,strcat(directory, 'ValuePd'),'-dpng');
