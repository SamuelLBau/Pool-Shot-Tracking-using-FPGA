function [X, Y, collision] = BallCoordBeforeCollision(BW)

% Close regions using ball morphology
ball_rad = 7;
FilteredImage = bwareaopen(BW, ball_rad);
se = strel('disk',ball_rad);
closeBW = imclose(FilteredImage,se);

% Trace region boundaries in the binary image.
cc = bwconncomp(closeBW, 4);
    
% We determine a collision has taken place when the area becomes one
regiondata = regionprops(cc, 'basic');
region_areas = [regiondata.Area];

if (length(region_areas) > 1)
    collision = false;
    
    region_centroids = [regiondata.Centroid];
    centroid_coord = [region_centroids(1:2:length(region_centroids)-1); region_centroids(2:2:length(region_centroids))];

    % Save the region with the min area, this is the cue ball
    [~, k] = min(region_areas);
    X(1) = centroid_coord(1,k);
    Y(1) = centroid_coord(2,k);
    
    % Break the region with the max area into 15 balls.
    [~, k] = max(region_areas);
    
    % Find the coordinates of the three corners
    [id_X, id_Y] = ind2sub(size(BW),cc.PixelIdxList{k});
    x_1 = min(id_Y);
    x_2 = max(id_Y);
    y_3 = max(id_X);
    y_1 = max(id_X(id_Y==x_1));
    y_2 = max(id_X(id_Y==x_2));
    x_3 = (max(id_Y(id_X==y_3))+min(id_Y(id_X==y_3)))/2;
    
    x_1 = x_1 + ball_rad;
    x_2 = x_2 - ball_rad;
    y_3 = y_3 - 1.2*ball_rad;
    
    dx_3_1 = (x_1 - x_3)/4;
    dy_3_1 = (y_1 - y_3)/4;
    dx_1_2 = (x_2 - x_1)/4;
    dy_1_2 = (y_2 - y_1)/4;
    cnt = 1;
    
    for i=1:5
        cnt = cnt + 1;
        cnt_i = cnt;
        X(cnt) = x_3 + (i-1)*dx_3_1;
        Y(cnt) = y_3 + (i-1)*dy_3_1;
        for j=1:(i-1)
            cnt = cnt + 1;
            X(cnt) = X(cnt_i) + j*dx_1_2;
            Y(cnt) = Y(cnt_i) + j*dy_1_2;
        end
    end
    %figure; imshow(closeBW); hold on; scatter(X,Y);
else
    X=[];
    Y=[];
    collision = true;
end
end