% Script to create a final demo video. Uses all frames.
% This also takes into account the "ghosts" or no-ball data points
clc
clear all
close all

%Read the image identifiers
ball_cnt = 17;
R = 8;
M = csvread('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\ImageClassification.csv');
[M_l, M_w] = size(M);
image_cnt = M_l/ball_cnt;

%No-balls are currently 0. Replace those with 17 for indexing.
k = find(M(:,3) == 0);
M(k, 3) = 17;

% Output video
outFilename = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\FinalClassificationDemo.avi';
vidWrite = VideoWriter(outFilename);
open(vidWrite);

% Generate a video
fig = figure();
composite_image = uint8(zeros(2*R*4,2*R*4,3));
for id=1:image_cnt
    first_ball_id = (id-1)*ball_cnt+1;
        
    % Read in the frame
    image_id = M(first_ball_id, 1);
    filename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Img_',int2str(image_id),'.png');
    RGB = imread(filename);
    [img_width, img_length, ~] = size(RGB);
    
    % Show 16 balls
    replaced_ball = 0;
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame
        idb = row - first_ball_id + 1;
        if (M(row, 5) == 0 && M(row, 4) == 0)
            replaced_ball = idb;
            continue;
        end
        
        % read the RGB from the image
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
       
        cropped_RGB = RGB(xmin:xmax,ymin:ymax,:);
        [cropped_width, cropped_length, ~] = size(cropped_RGB);
        if (M(row, 3) == 17)
            if (replaced_ball == 0)
                replaced_ball = ceil(16*rand(1));
            end
            comp_row = ceil(replaced_ball/4);
            comp_col = mod(replaced_ball,4);
            if (comp_col == 0)
                comp_col = 4;
            end
        else
            comp_row = ceil(idb/4);
            comp_col = mod(idb,4);
            if (comp_col == 0)
                comp_col = 4;
            end
        end
        comp_xmin = 2*R*(comp_row-1)+1;
        comp_xmax = comp_xmin+cropped_width-1;
        comp_ymin = 2*R*(comp_col-1)+1;
        comp_ymax = comp_ymin+cropped_length-1;
        composite_image(comp_xmin:comp_xmax, comp_ymin:comp_ymax,:) = cropped_RGB;
    end
    %Scale the image and show
    scaled_composite = composite_image;
    subplot(1,2,1); imshow(scaled_composite);
    label_img = uint8(zeros(size(scaled_composite)));
    subplot(1,2,2); imshow(label_img);
    
    % Save the image to the output video
    frame = getframe(fig);
    writeVideo(vidWrite, frame);
    
    % Convert the frame to HSV
    HSV = rgb2hsv(RGB);
    
    % For each ball
    P = zeros(ball_cnt,ball_cnt);
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        % Get the classification
        P(M(row, 3), 1:16) = BallClassificationProbability(HSV, M(row, 5), M(row, 4), false);
        I_actual =  M(row, 3);
    end
    
    % For the not-ball or ghost use the 1-max probability of a match to the
    % other ball classes
    % This assumption lowers accuracy by 1%
    %P(:, ball_cnt) = ones(ball_cnt,1)-max(P(:,1:16),[],2);
    
    % Match all the balls in the frame
    P_adjusted = AdjustByProximity(P, M, id);
    L = MaximumProbabilityMatching(P_adjusted);
    
    % Display the labels
    for idb=1:ball_cnt
        if (idb == replaced_ball)
            continue;
        end
        if (idb == ball_cnt)
            comp_row = ceil(replaced_ball/4);
            comp_col = mod(replaced_ball,4);
            if (comp_col == 0)
                comp_col = 4;
            end
        else
            comp_row = ceil(idb/4);
            comp_col = mod(idb,4);
            if (comp_col == 0)
                comp_col = 4;
            end
        end
        label_x = 2*R*(comp_row-1)+R;
        label_y = 2*R*(comp_col-1)+R;
        
        row = first_ball_id + idb -1;
        
        if (L(idb) == ball_cnt)
            label_txt = 'X';
        else
            label_txt = int2str(L(idb));
        end
        if (L(idb) == M(row, 3))
            text(label_y, label_x, label_txt ,'HorizontalAlignment','center', 'Color', 'white', 'FontSize', 14);
        else
            text(label_y, label_x, label_txt ,'HorizontalAlignment','center', 'Color', 'red', 'FontSize', 14);
        end
        pause(1/16);
        % Save the image to the output video
        frame = getframe(fig);
        writeVideo(vidWrite, frame);
    end
    
    pause(1);
end

close(vidWrite);