%  topsumsynactpf_2_meg.m
%
%  FORMAT: topsumsynactpf_2_meg
%
%  This program load the results (spec_pet.mat -- the time series of 
%  of integrated synaptic activity) from a number of subjects and attention
%  levels & computes the time series of synaptic activity in each brain
%  region.
%
%  The subject list must be called subjectlist, which is a list of the
%  directories having data for each subject.  There is also a list of 
%  attention levels (attnlist).
%
%  This program correspond to case when prefrontal cortex is broken
%  up into 4 separate regions.
%
%  Calls:  sumsynactpf_2_meg.m
%	   subjectlist.mat, attnlist.mat
%
%  Written:  July 2003 by B. Horwitz (modified version of topsumsynactpf.m)

workdir=pwd;

load subjectlist
load attnlist

[nrowsp,ncolsp]=size(subjectlist);
[nrp,ncp]=size(attnlist);

for i=1:nrowsp
  eval(['cd ',subjectlist(i,:)]);
  cworkdir=pwd;
  for j=1:nrp
	eval(['cd ',attnlist(j,:)]);
  	sumsynactpf_2_meg
 	eval(['cd ',cworkdir]);
  end
  eval(['cd ',workdir]);	
end

clear intgractmean synactmean 


