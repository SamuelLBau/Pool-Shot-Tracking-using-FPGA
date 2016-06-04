% Function to compute the probability for all possible classifiers.
function [L] = BallClassificationProbability(HSV, X, Y, plotPd)
R=8;
R_sq = R^2;
L = zeros(16, 1);

%read the pd functions from CSV
directory = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\';
M = csvread(strcat(directory,'ReddishHuePd.csv'));
[~, y] = size(M);
red_x_values = M(2:256,1);
red_ball_id = M(1,2:y);
red_pd = M(2:256,2:y);

M = csvread(strcat(directory,'NormalHuePd.csv'));
[~, y] = size(M);
norm_x_values = M(2:256,1);
norm_ball_id = M(1,2:y);
norm_pd = M(2:256,2:y);

M = csvread(strcat(directory,'ValuePd.csv'));
[~, y] = size(M);
val_x_values = M(2:256,1);
val_ball_id = M(1,2:y);
val_pd = M(2:256,2:y);

% Limits of the frame to iterate over
[xmax, ymax, ~] = size(HSV);
xmax = min(xmax, X+R);
ymax = min(ymax, Y+R);
xmin = max(1, X-R);
ymin = max(1, Y-R);

% Iterate over the frame and save pixels in range of ball.
HSV_pixels = zeros(4*R_sq, 3);
pixel_cnt = 0;
for x=xmin:xmax
    for y = ymin:ymax
        if (x-X)^2+(y-Y)^2 <= R_sq
            pixel_cnt = pixel_cnt+1;
            HSV_pixels(pixel_cnt, :) = HSV(x,y,:);
        end
    end
end

% Fit the transposed hue of the distribution
Hue_high = HSV_pixels(1:pixel_cnt, 1) >= 0.5;
Hue_wrapped = HSV_pixels(1:pixel_cnt, 1);
Hue_wrapped(Hue_high) = Hue_wrapped(Hue_high) - 1;
pd = fitdist(Hue_wrapped,'Kernel','Kernel','epanechnikov');
y = pdf(pd, red_x_values);
for i = 1:length(red_ball_id)  
    % compare the pd
    y_comp = [y, red_pd(:,i)];
    
    if plotPd
        figure
        plot(red_x_values, y);
        hold on
        plot(red_x_values, red_pd(:,i));
        hold off
    end
    
    % Compute the estimated probability
    P = sum(min(y_comp,[],2).*1/255);
    L(red_ball_id(i))= P;
end

% Fit the hue distribution
Hue = HSV_pixels(1:pixel_cnt, 1);
pd = fitdist(Hue,'Kernel','Kernel','epanechnikov');
y = pdf(pd, norm_x_values);
for i = 1:length(norm_ball_id)  
    % compare the pd
    y_comp = [y, norm_pd(:,i)];
    
    if plotPd
        figure
        plot(norm_x_values, y);
        hold on
        plot(norm_x_values, norm_pd(:,i));
        hold off
    end
    
    % Compute the estimated probability
    P = sum(min(y_comp,[],2).*1/255);
    L(norm_ball_id(i))= P;
end

% Fit the value distribution
Hue = HSV_pixels(1:pixel_cnt, 3);
pd = fitdist(Hue,'Kernel','Kernel','epanechnikov');
y = pdf(pd, val_x_values);
for i = 1:length(val_ball_id)
    % compare the pd
    y_comp = [y, val_pd(:,i)];
    
    if plotPd
        figure
        plot(val_x_values, y);
        hold on
        plot(val_x_values, val_pd(:,i));
        hold off
    end
    
    % Compute the estimated probability
    P = sum(min(y_comp,[],2).*1/255);
    L(val_ball_id(i))= P;
end

end