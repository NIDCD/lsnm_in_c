%  meansubject.m        July 2003
%
%  FORMAT meansubject
%_______________________________________________________
%
%  This program computes  mean time series for both the task condition
%  and the control condition.
%
%---------------------------------------------------------------- 
%
%  Written July, 2003 by B. Horwitz
%

load subjectlist

[nsub nscols]=size(subjectlist);
workdir=pwd;

eval(['cd ',subjectlist(1,:)]);
load sepsynact
[nrx,ncx]=size(tasksynact);

totalsubjctrl=zeros(nrx,ncx);
totalsubjtask=zeros(nrx,ncx);

cd ..

for iis=1:nsub
  eval(['cd ',subjectlist(iis,:)]);
  load sepsynact
  totalsubjtask=totalsubjtask+tasksynact;
  totalsubjctrl=totalsubjctrl+ctrlsynact;
  eval(['cd ',workdir]);
end

meansubjtask=totalsubjtask./nsub;
meansubjctrl=totalsubjctrl./nsub;

save meansubject meansubjtask meansubjctrl
