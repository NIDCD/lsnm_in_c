%  catspec_pet_meg.m  
%
%  FORMAT: catspec_pet_meg
%
%  Calls:  subjectlist.mat, attnlist.mat, triallist.mat
%
%  Written by B. Horwitz 10/2/04 (modified from catspec_pet.m)  
%
%  Puts together spec_pet for all the trials for all attention levels 
%  ( b's, e.g.,  [10,14,18,22,26,30]) for all the subjects.  It does this
%  for the MEG data (the difference between the integrated excitatory and
%  inhibitory activity, which is obtained for each timestep (~5msec).

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
      [r c]=size(spec_pet);
      spec_pet_mege=spec_pet(1:2:r,:);
      spec_pet_megi=spec_pet(2:2:r,:);   
%      
% Note that spec_pet_megi is negative
%
      spec_pet_meg=spec_pet_mege+spec_pet_megi; 
      spec_petall=[spec_petall;spec_pet_meg];
      cd ..
    end
  spec_pet=spec_petall;
  save('spec_pet_meg.mat','spec_pet');
  cd ..
  end
cd ..
end	
