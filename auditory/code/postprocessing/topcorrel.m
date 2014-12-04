%  topcorrel.m -- July 2003
%
%  FORMAT  topcorrel
%
%  Calls:  subjectlist.mat, sepsynact.mat, fmritask.mat, fmrictrl.mat
%__________________________________________________________
%
%  This program computes the correlations between the timeseries
%  for the task condition and the control condition.  It does
%  this for each subject.
%
%-----------------------------------------------------------  

%  Written July, 2003 by B. Horwitz and Brent Warner

load subjectlist;
[srows,scols]=size(subjectlist);
workdir=pwd;

for kk=1:srows
  eval(['cd ',subjectlist(kk,:)]);
  load sepsynact;
  rtask=corrcoef(tasksynact);
  rctrl=corrcoef(ctrlsynact);
  load fmritask;
  fmridata=fmridata(:,2:8);
  rtaskfmri=corrcoef(fmridata);
  load fmrictrl;
  fmridata=fmridata(:,2:8);
  rctrlfmri=corrcoef(fmridata);
  save correl rtask rctrl rtaskfmri rctrlfmri;
  eval(['cd ',workdir]);
end