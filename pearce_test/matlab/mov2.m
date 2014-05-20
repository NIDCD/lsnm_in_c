%  mov2.m -- June, 1998
%
%  changed reshape to its transpose because Matlab
%  converts vector into matrix in column-major form while our
%  data were written in row major form

%  FORMAT:  m=mov2(arr1,arr2, matsize);
%
%  	m=the frames for the movie
%
%  This functions makes all the frames needed for the movie of 
%  neuronal activity for 2 rows of regions (see loadmovieRie.m).

%  Written:  6/98 by T. Long
%  Modified from M. Tagamets' mov.m

function M = mov2(arr1, arr2, matsize)

nframes = length(arr1(:,1));
M = moviein(nframes);
N = sqrt(matsize);
ablank = zeros(N,1);
mm = length(arr1(1,:))/matsize;
mm = mm .*(N+1);
bblank = zeros(1,mm);

totsize = length(arr1(1,:));
arr = [arr1;arr2];
emin = min(min(arr));
emax = max(max(arr));
clear arr;
ediff = emax - emin;
a = (arr1 - emin) ./ ediff * 40 +24;
b = (arr2 - emin) ./ ediff * 40 +24;

clear arr1;
clear arr2;

colormap(bone(64));
for i=1:nframes
  A1= [];
  B1= [];
  for j=1:matsize:totsize
    A1 = [A1 (reshape(a(i,j:j+matsize-1), N, N))' ablank];
    B1 = [B1 (reshape(b(i,j:j+matsize-1), N, N))' ablank];
  end;
  C1=[A1;bblank;B1];
  image(C1);
  M(:,i) = getframe;
end;
clear a b A1 B1 C1 ablank bblank







