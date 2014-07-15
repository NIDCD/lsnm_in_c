%  catspec_pet.m  
%
%  FORMAT: catspec_pet  
%
%  Calls:  subjectlist.mat, attnlist.mat, triallist.mat
%
%  Written by Julia Fitzer and B. Horwitz 7/24/03  
%
%  Puts together spec_pet for all the trials for all attention levels 
%  ( b's, e.g.,  [10,14,18,22,26,30]) for all the subjects

%  To run this program, one must be at the directory above all the subject
%  files


load subjectlist;
load attnlist;
load triallist;

workdir=pwd;

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
    spec_petall=[];
    for k=1:tr
      eval(['cd ',triallist(k,:)]);
      load spec_pet.m;
      spec_petall=[spec_petall;spec_pet];
      cd ..
    end
  spec_pet=spec_petall;
  save spec_pet spec_pet
  cd ..
  end
cd ..
end	
