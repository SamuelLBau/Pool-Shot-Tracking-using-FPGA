%Uses RGB Space to classify Black, White balls.

%Script to compute the parameters for classifying the 16 balls based on
%training set frames
clc;
close all;
clear;

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
                    RGB_pixels(M(row, 3)+1, pixel_cnt(M(row, 3)+1)) = double(RGB(x,y,1))*double(RGB(x,y,2))*double(RGB(x,y,3));
                end
            end
        end
    end
end

% For black ball plot the value
figure
ball_id = [8 16];
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = RGB_pixels(id, 1:pixel_cnt(id));

    h = histogram(Hue, bin_cnt);
    hold on
end
xlabel('R*G*B');
ylabel('Training set pixel count');
legend('8','Cue');
hold off

% Plot for all the balls
figure
ball_id = 1:16;
for i = 1:length(ball_id)
    id = ball_id(i) + 1;
    
    Hue = RGB_pixels(id, 1:pixel_cnt(id));

    h = histogram(Hue, bin_cnt);
    hold on
end
xlabel('R*G*B');
ylabel('Training set pixel count');
legend('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','Cue');
hold off