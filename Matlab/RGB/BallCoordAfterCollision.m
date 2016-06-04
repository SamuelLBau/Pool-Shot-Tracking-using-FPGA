function [X, Y] = BallCoordAfterCollision(BW)
A_min = 50;
A_max = 250;
r_min = 12;
FilteredImage = bwareaopen(BW, A_min);
cc = bwconncomp(FilteredImage, 4);

% Get the centroids of all the regions
regiondata = regionprops(cc, 'basic');
region_centroids = [regiondata.Centroid];
centroid_coord = [region_centroids(1:2:length(region_centroids)-1); region_centroids(2:2:length(region_centroids))];

%Split large boundaries with watershed
region_areas = [regiondata.Area]; 
cnt = 0;
for i=1:length(region_areas)
   if region_areas(i)< A_max
       cnt = cnt +1;
       X(cnt) = centroid_coord(1,i);
       Y(cnt) = centroid_coord(2,i);
       continue
   end

   region = false(size(FilteredImage));
   region(cc.PixelIdxList{i}) = true;
   %subplot(1,2,1);imshow(region);

   % distance transform for watershed
   D = bwdist(~region);
   D = -D;
   D(~region) = -Inf;

   L= watershed(D);
   %rgb = label2rgb(L,'jet',[.5 .5 .5]);
   %subplot(1,2,2);imshow(rgb,'InitialMagnification','fit');title('Watershed');
   
   k = max(L(:));
   cnt_tmp = 0;
   for j=2:k
       region2 = false(size(FilteredImage));
       region2(L==j) = true;
       %imshow(region2);
       [B,L2] = bwboundaries(region2,'noholes');
       regiondata2 = regionprops(L2,'Area','Centroid');
       threshold = 0.75;
       
       % obtain (X,Y) boundary coordinates corresponding to label 'k'
       boundary = B{1};

       % compute a simple estimate of the object's perimeter
       delta_sq = diff(boundary).^2;
       perimeter = sum(sqrt(sum(delta_sq,2)));

       % compute the roundness metric
       area = regiondata2(1).Area;
       if area < A_min
           continue
       end
       metric = 4*pi*area/perimeter^2;

       % display the results
       %str = sprintf('%2.2f',metric);
       centroid = regiondata2(1).Centroid;
       %text(centroid(1),centroid(2),str,'Color', 'white');
       
       if metric >= threshold || area < 150
           cnt_tmp = cnt_tmp + 1;
           X_tmp(cnt_tmp) = centroid(1);
           Y_tmp(cnt_tmp) = centroid(2);
           A_tmp(cnt_tmp) = area;
       end
   end
   added = false(length(cnt_tmp));
   for j=1:cnt_tmp
       if added == true
           continue;
       end
       d_i = zeros(cnt_tmp);
       for k=1:cnt_tmp
           if j ~= k
              d_i(k) =  sqrt((X_tmp(k)-X_tmp(j)^2)+(Y_tmp(k)-Y_tmp(j)^2));
           end
       end
       A_cmp = A_tmp;
       A_cmp(d_i>r_min)=0;
       [~, idx] = max(A_cmp);
       added (idx) = true;
       cnt = cnt + 1;
       X(cnt) = X_tmp(idx);
       Y(cnt) = Y_tmp(idx);
   end
end
end