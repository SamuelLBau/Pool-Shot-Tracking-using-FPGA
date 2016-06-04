% This was inspired by Yi Cao's Hungarian Algorithm implementation at 
% http://www.mathworks.com/matlabcentral/fileexchange/20652-hungarian-algorithm-for-linear-assignment-problems--v2-3-

% The ball to classifier matching is an example of the maximum weight 
% bipartate matching problem where the edge weight is the probability. 
% Only one ball of each classification can be on the table at once and 
% we want the probability of all the balls matched to be optimal.  

% L is a 16,1 or 17,1 array of ball labels
% P is an input matrix of 16x16 or 17x17 for the probability that each of the balls
% on the table (rows) matches the ball ids (columns)
% Sometimes not all the balls are on the table and in that case the row
% should be all zeros.

function [L] = MaximumProbabilityMatching(P)

[n, ~] = size(P);

% Create a rectangular cost matrix to minimize. Cost is 1-p
C = zeros(n);
C_id = zeros(n,1);
ball_cnt = 0;
for i=1:n
    if sum(P(i,:) ~= 0) ~=0
        ball_cnt = ball_cnt+1;
        C(ball_cnt, :) = 1 - P(i,1:n);
        C_id(ball_cnt) = i;
    end
end

% 1: For each row of the matrix, find the smallest element and subtract it 
% from every element in its row.
minR = min(C,[],2);
minC = min(bsxfun(@minus, C, minR));

% 2:  Find a zero (Z) in the resulting matrix.  If there is no starred zero 
% in its row or column, star Z. Repeat for each element in the matrix.
zP = C == bsxfun(@plus, minC, minR);

starZ = zeros(n,1);
while any(zP(:))
    [r,c]=find(zP, true);
    starZ(r)=c;
    zP(r,:)=false;
    zP(:,c)=false;
end

while 1
% 3: Cover each column containing a starred zero.  If K columns are 
% covered, the starred zeros describe a complete set of unique assignments.  
% In this case, Go to DONE, otherwise, Go to Step 4.
    if all(starZ>0)
        break
    end
    coverColumn = false(1,n);
    coverColumn(starZ(starZ>0))= true;
    coverRow = false(n,1);
    primeZ = zeros(n,1);
    [rIdx, cIdx] = find(C(~coverRow,~coverColumn)==bsxfun(@plus,minR(~coverRow), minC(~coverColumn)));
    while 1
         % 4: Find a noncovered zero and prime it.  If there is no starred zero 
         % in the row containing this primed zero, Go to Step 5.  Otherwise, 
         % cover this row and uncover the column containing the starred zero. 
         % Continue in this manner until there are no uncovered zeros left. 
         % Save the smallest uncovered value and Go to Step 6.
        cR = find(~coverRow);
        cC = find(~coverColumn);
        rIdx = cR(rIdx);
        cIdx = cC(cIdx);
        Step = 6;
        while ~isempty(cIdx)
            uZr = rIdx(1);
            uZc = cIdx(1);
            primeZ(uZr) = uZc;
            stz = starZ(uZr);
            if ~stz
                Step = 5;
                break;
            end
            coverRow(uZr) = true;
            coverColumn(stz) = false;
            z = rIdx==uZr;
            rIdx(z) = [];
            cIdx(z) = [];
            cR = find(~coverRow);
            z = C(~coverRow,stz) == minR(~coverRow) + minC(stz);
            rIdx = [rIdx(:);cR(z)];
            cIdx = [cIdx(:);stz(ones(sum(z),1))];
        end
        if Step == 6
            % 6: Add the value found in Step 4 to every element of each 
            % covered row, and subtract it from every element of each 
            % uncovered column.  Return to Step 4 without altering any stars, 
            % primes, or covered lines.
            [minval,rIdx,cIdx]=outerplus(C(~coverRow,~coverColumn),minR(~coverRow),minC(~coverColumn));            
            minC(~coverColumn) = minC(~coverColumn) + minval;
            minR(coverRow) = minR(coverRow) - minval;
        else
            break
        end
    end
    % 5: Construct a series of alternating primed and starred zeros
    rowZ1 = find(starZ==uZc);
    starZ(uZr)=uZc;
    while rowZ1>0
        starZ(rowZ1)=0;
        uZc = primeZ(rowZ1);
        uZr = rowZ1;
        rowZ1 = find(starZ==uZc);
        starZ(uZr)=uZc;
    end
end

% Done - assignment
colIdx = 1:n;
L = zeros(n,1);
L(C_id(1:ball_cnt)) = colIdx(starZ(1:ball_cnt));
end

function [minval,rIdx,cIdx]=outerplus(M,x,y)
ny=size(M,2);
minval=inf;
for c=1:ny
    M(:,c)=M(:,c)-(x+y(c));
    minval = min(minval,min(M(:,c)));
end
[rIdx,cIdx]=find(M==minval);
end