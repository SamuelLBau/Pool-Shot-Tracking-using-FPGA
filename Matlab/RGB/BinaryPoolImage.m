function BW = BinaryPoolImage(RGB)

persistent color_limits;

if isempty(color_limits)
    % load the background
    filename_background = 'C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\PoolTableBackground.png';
    Background = imread(filename_background);

    % compute the min and the max for each color
    color_limits = zeros([3, 2]);
    for i=1:3
        color_limits(i,1) = prctile(Background(:,i),0.3);
        color_limits(i,2) = prctile(Background(:,i),99.7);
    end
end

[d_x, d_y, ~] = size(RGB);
BW=zeros([d_x,d_y]);
for x=1:d_x
    for y=1:d_y
         if RGB(x,y,1) < color_limits(1,1) ||...
            RGB(x,y,1) > color_limits(1,2)||...
            RGB(x,y,2) < color_limits(2,1) ||...
            RGB(x,y,2) > color_limits(2,2)||...
            RGB(x,y,3) < color_limits(3,1) ||...
            RGB(x,y,3) > color_limits(3,2)
            BW(x,y)=1;
        end
    end
end
end