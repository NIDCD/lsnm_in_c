
%gunzipall.m
%written by Julia Fitzer
% 7/30/03
%
%FORMAT gunzipall 
%
%Unzips all *.out.zip files within a directory containing subjects and
%attn levels.
%
%Assumes one has subjectlist.mat,  attnlist.mat, and trial list.
%
%Sometimes computer complains that argument list is too long if one
%simply tries to do gunzip subj*/b*/trial*/*.out.gz So one has to go into each
%subject individually.  This program does that.

load subjectlist;
load attnlist;
load triallist;

[sr,sc]=size(subjectlist);
[ar,ac]=size(attnlist);
[tr,tc]=size(triallist);

disp(['The number of subjects is ' num2str(sr)]);
disp(['The number of attention levels is ' num2str(ar)]);
disp(['The number of trials is ' num2str(tr)]);

for i=1:sr
  eval(['cd ',subjectlist(i,:)]);
  for j=1:ar
    eval(['cd ',attnlist(j,:)]);
    for k=1:tr
       eval(['cd ',triallist(k,:)]);
       !gunzip *.out.gz;
       cd ..
    end   
    cd ..
  end
  cd ..	
end
cd ..   %back to top of directory
