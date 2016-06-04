%Script to get the probablity density for distance from past location
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

% Compute the distance from past location for each ball type
ball_image_cnt = 0;
for id=1:image_cnt
    first_ball_id = (id-1)*ball_cnt+1;
    if (M(:, 2) == 0)
        continue
    end
    
    % For each ball
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        % Do this for balls only
        if (M(row, 3) == 0)
            continue
        end
        
        if (id > 1)
            ball_image_cnt = ball_image_cnt + 1;
            distance_prev(ball_image_cnt) = ((M(row, 5)- M(row-ball_cnt, 5))^2 + (M(row, 4)-M(row-ball_cnt, 4))^2)^.5;
        end
    end
end

% Plot a histogram
figure

% fit the distribution with a kernel pd distribution
pd = fitdist(transpose(distance_prev),'Exponential');
    
% plot the pd
x_values = 0:100;
y = pdf(pd, x_values);
plot(x_values,y)