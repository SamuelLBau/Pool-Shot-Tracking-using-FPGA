% function to adjust estimated probability based on distance from past
% measurement
% M classifier matrix
% id the current image in the classifier matrix
% P classification probability
function [P_adjusted] = AdjustByProximity(P, M, id)

ball_cnt = 17;
P_t = zeros(ball_cnt);

[size_P, ~] = size(P);
P_t(1:size_P, 1:size_P) = P;

mu = 4.10418; % From fitting training data
first_ball_id = (id-1)*ball_cnt+1;

if (id <= 1)
    P_adjusted = P;
else
    row = first_ball_id:id*ball_cnt;
    row_p = row-ball_cnt;
    distance = (bsxfun(@minus, transpose(M(row_p, 5)), M(row, 5))).^2 + (bsxfun(@minus, transpose(M(row_p, 4)), M(row, 4))).^2;
    k = find(distance);
    distance(k) = distance(k).^0.5;
    p_distance = exp(-distance./mu);
    p_distance(:,ball_cnt) = zeros(ball_cnt, 1);
    P_a = P_t+0.1*p_distance;
    P_adjusted = P_a(1:size_P, 1:size_P);
    
    % Do not adjust rows that are all zeros by distance
    for i=1:size_P
        if sum(P(i,1:16) ~= 0) ==0
            P_adjusted(i,:) = zeros(1,size_P);
        end
    end
end
end