function [L] = LabelBallCoordinates(RGB, X, Y)
r_sq = 8^2;
color_thresholds = [0.5, 0.7, 0.375, 0.425, 0, 0.11, 150, 530; % yellow
    0, 0.3, 0.175, 0.4, 0.4, 1, 150, 600; % blue
    0.65, 1, 0, 0.22, 0, 0.175, 150, 600; % red
    0.25, 0.4, 0.15, 0.3, 0.35, 0.6, 150, 520; % purple
    0.5, 0.68, 0.25, 0.35, 0, 0.15, 150, 600; % orange
    0.0, 0.4, 0.4, 1, 0.15, 0.4, 150, 600; % green
    0.4, 0.6, 0, 0.3, 0.15, 0.35, 150, 600; % maroon
    0.28, 0.4, 0.28, 0.4, 0.28, 0.4, 0, 150; % black
    0.3, 0.4, 0.3, 0.4, 0.2, 0.4, 530, 765]; % white
[color_cnt, ~] = size(color_thresholds);
[x_max, y_max, ~] = size(RGB);

len = length(X);
L = zeros(size(X));
prct = zeros([len, color_cnt]);
for i=1:len
    % Get pixels in range
    for x=1:x_max
        for y=1:y_max
            if (x-Y(i))^2+(y-X(i))^2 <= r_sq
                total_intensity = sum(RGB(x,y,:));
                ratio = double(RGB(x,y,:))./total_intensity;
                for j=1:color_cnt
                    if ratio(1,1,1) >= color_thresholds(j,1) &&...
                        ratio(1,1,1) <= color_thresholds(j,2) &&...
                        ratio(1,1,2) >= color_thresholds(j,3) &&...
                        ratio(1,1,2) <= color_thresholds(j,4) &&...
                        ratio(1,1,3) >= color_thresholds(j,5) &&...
                        ratio(1,1,3) <= color_thresholds(j,6) &&...
                        total_intensity >= color_thresholds(j,7) &&...
                        total_intensity <= color_thresholds(j,8)
                        prct(i,j) = prct(i,j) + 1;
                    end
                end
            end
        end
    end
end

%Get the maximum color
for i=1:len
    [max_cnt, max_color] = max(prct(i,1:8));
    
    % Correct for difficult to detect blue, red
    corr_limit = 11;
    if (prct(i,3) > corr_limit && 3*corr_limit > max_cnt)
        max_cnt = prct(i,3);
        max_color = 3;
    elseif (prct(i,2) > corr_limit && 3*corr_limit > max_cnt)
        max_cnt = prct(i,2);
        max_color = 2;
    end

    white_ratio = prct(i,9)/(prct(i,9) + max_cnt);
    if white_ratio > .95 % cue ball
        L(i) = 16; 
    elseif white_ratio > .3 % striped ball
        if max_color == 8
            % recalculate. No black-white balls
            [max_cnt, max_color] = max(prct(i,1:7));
    
            if (prct(i,3) > corr_limit && 3*corr_limit > max_cnt)
                max_color = 3;
            elseif (prct(i,2) > corr_limit && 3*corr_limit > max_cnt)
                max_color = 2;
            end
        end
        L(i) = 8+max_color;
    else
        L(i) = max_color;
    end  
end
end