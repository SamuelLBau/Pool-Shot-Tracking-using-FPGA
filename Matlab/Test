% Script to write the test frames to file.

test_frame_cnt = 3;

for frame=1:test_frame_cnt
     % Read in the frame
    filename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\Img_',int2str(frame),'.png');
    RGB = imread(filename);
    [max_x, max_y, ~] = size(RGB);
    
    %Write out the frame
    outFilename = strcat('C:\Users\osouverneva\Desktop\Temp\CSE237D\Video1\Images\TestFrame',int2str(frame),'.txt');
    fileID = fopen(outFilename,'w');
    formatSpec = '{%u,%u,%u},';
    fprintf(fileID, '{\n');
    for x=1:max_x
        fprintf(fileID, '{');
        for y=1:max_y
            fprintf(fileID, formatSpec, RGB(x,y,1), RGB(x,y,2), RGB(x,y,3));
        end
        fprintf(fileID, '},\n');
    end
    fprintf(fileID, '};\n');
    fclose(fileID);
end
