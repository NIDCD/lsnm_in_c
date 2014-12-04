%  catspec_pet_fmri.m  
%
%  FORMAT: catspec_pet_fmri  
%
%  Calls:  subjectlist.mat, attnlist.mat, triallist.mat
%
%  Revised from catspec_pet.m by Julia Fitzer and B. Horwitz 7/24/03  
%  Revised by Feng Rong 5/31/05 for generating simulated intergrated
%  synaptic activity for synthetic fMRI signal
%
%  Puts together spec_pet for all the trials for all attention levels 
%  ( b's, e.g.,  [10,14,18,22,26,30]) for all the subjects. Intergrate the 
%  absolute value of the excitatory and inhibitory synaptic PSPs. The
%  integration was taken ~every 50 msec(10 simulation time steps).  
%
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
      spec_pet_fmrie=spec_pet(1:2:r,:);
      spec_pet_fmrii=spec_pet(2:2:r,:);   
%      
% The fmri signal are positive for excitatory and inhibitory signals
%
      spec_pet_fmri_trial=abs(spec_pet_fmrie)+abs(spec_pet_fmrii); 
      spec_petall=[spec_petall;spec_pet_fmri_trial];
     cd .. 
    end  
    timelen_fmri=round(size(spec_petall,1)/10);
    spec_pet_fmri=[];
    for tt=1:timelen_fmri
      if (tt*10)<=size(spec_petall,1)
         tps_ts=((tt-1)*10+1):(tt*10);
      else
         tps_ts=((tt-1)*10+1):size(spec_petall,1);
      end
      spec_pet_ts=sum(spec_petall(tps_ts,:),1);
      spec_pet_fmri=[spec_pet_fmri;spec_pet_ts];
    end
  spec_pet=spec_pet_fmri;
  save spec_pet_fmri spec_pet spec_petall;
  cd ..
  end
cd ..
end	

