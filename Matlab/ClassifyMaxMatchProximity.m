% Script to test parameters for classifying the test set by picking the
% classifier with the highest probability of a match for each ball. The
% probability is adjusted by proximity to past location before attempting a
% match.
clc
clear all
close all

%Read the image identifiers
ball_cnt = 17;
M = csvread('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\ImageClassification.csv');
[M_l, M_w] = size(M);
image_cnt = M_l/ball_cnt;

% Classify the images in the test set
correct = zeros(ball_cnt,1);
incorrect = zeros(ball_cnt,1);
for id=1:image_cnt
    first_ball_id = (id-1)*ball_cnt+1;
    if M(first_ball_id, 2) ~= 0
        continue
    end
        
    % Read in the frame
    image_id = M(first_ball_id, 1);
    filename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Img_',int2str(image_id),'.png');
    RGB = imread(filename);
    
    % Convert the frame to HSV
    HSV = rgb2hsv(RGB);
    
    % For each ball
    P = zeros(16,16);
    for row=first_ball_id:id*ball_cnt
        % Do this only for balls in the frame
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        % Skip not-balls
        if (M(row, 3) == 0)
            continue
        end
        
        % Get the classification
        P(M(row, 3), :) = BallClassificationProbability(HSV, M(row, 5), M(row, 4), false);
        I_actual =  M(row, 3);
    end
    
    % Match all the balls in the frame
    P_adjusted = AdjustByProximity(P, M, id);
    L = MaximumProbabilityMatching(P_adjusted);
    
    % Calculate correct/incorrect matches
    for idb=1:16
        row = first_ball_id + idb -1;
        
        % Do this only for balls in the frame
        if (M(row, 5) == 0 && M(row, 4) == 0)
            continue
        end
        
        if (L(idb) == M(row, 3))
            correct(idb) = correct(idb)+1;
        else
            incorrect(idb) = incorrect(idb)+1;
        end
    end
end

%plot the results
accuracy = sum(correct)/(sum(correct)+sum(incorrect))
figure
bar(correct(1:16)./(correct(1:16)+incorrect(1:16)), 0.5);
xlabels = {'1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','Cue'};
set(gca, 'Xtick', 1:17, 'XtickLabel', xlabels)
ylabel('Classification Accuracy');