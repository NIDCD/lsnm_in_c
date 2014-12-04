%  topsumsynactpf.m -- Feb. 2000
%
%  FORMAT: topsumsynactpf
%
%  This program load the results (spec_pet.m -- the time series of 
%  of integrated synaptic activity) from a number of subjects and 
%  computes the time series of synaptic activity in each brain region.
%
%  The subject list must be called subjectlist, which is a list of the
%  directories having data for each subject.
%
%  This program correspond to case when prefrontal cortex is broken
%  up into 4 separate regions.
%
%  Calls:  sumsynactpf.m
%
%  Written:  Feb. 2000 by B. Horwitz

workdir=pwd;

[nrows,ncols]=size(subjectlist);

for i=1:nrows
  eval(['cd ',subjectlist(i,:)]);
  sumsynactpf
  eval(['cd ',workdir]);
end

clear intgract synact