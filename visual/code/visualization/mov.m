%  mov.m --  June 1998
%
%  changed reshape to its transpose because Matlab
%  converts vector into matrix in column-major form while our
%  data were written in row major form
%
%  FORMAT:  m=mov(arr, matsize)
%
%  	m=the frames for the movie
%
%  This function makes all the frames needed for the movie of 
%  neuronal activity (see loadmovieR.m).

%  Written:  6/98 by T. Long
%  Based on  M. Tagamets' original code

function M = mov(arr, matsize)

nframes = length(arr(:,1));
M = moviein(nframes);
N = sqrt(matsize);
for i=1:N
  ablank(i,1) = 0;
end;
totsize = length(arr(1,:));
emin = min(min(arr));
emax = max(max(arr));
ediff = emax - emin;
a = (arr - emin) ./ ediff * 127 +1;
clear arr;

colormap(jet(128));
for i=1:nframes
  A = ablank;
  for j=1:matsize:totsize
    A = [A (reshape(a(i,j:j+matsize-1), N, N))' ablank];
  end;
  image(A);
  M(:,i) = getframe;
end;
clear a A;

