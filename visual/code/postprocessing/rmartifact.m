function [y]=rmartifact(M);

y=M;

[row,col]=size(y);

for j=1:col
  for i=2:row-1
    if(y(i,j) >= 1.2*y(i-1,j) && y(i,j) >= 1.2*y(i+1,j))
      y(i,j) = (y(i-1,j)+y(i+1,j))/2;
    end
  end
end


return;