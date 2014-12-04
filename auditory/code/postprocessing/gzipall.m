
%gzipall.m
%written by Julia Fitzer, based on catspec_pet by B. Horwitz 
% 7/25/03
%
%FORMAT gzipall 
%
%Zips all concatenated *.out files within a directory containing subjects and
%attn levels.  Useful when one has unzipped a lot of concatenated *.out files
%while making movies or plots.
%
%Assumes one has subjectlist.mat and attnlist.mat
%
%Sometimes computer complains that argument list is too long if one
%simply tries to do gzip subj*/b*/*.out. So one has to go into each
%subject individually.  This program does that.

load subjectlist;
load attnlist;

[sr,sc]=size(subjectlist);
[ar,ac]=size(attnlist);

disp(['The number of subjects is ' num2str(sr)]);
disp(['The number of attention levels is ' num2str(ar)]);

for i=1:sr
  eval(['cd ',subjectlist(i,:)]);
  for j=1:ar
    eval(['cd ',attnlist(j,:)]);
    !gzip *.out;
    cd ..
  end   
  cd ..
end	
cd ..   %back to top of directory
