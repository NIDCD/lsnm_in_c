%  combinesumsynactpf_2_fmri.m -- July 2003
%
%  FORMAT: combinesumsynactpf_2_fmri
%
%  This program loads the time series of integrated synaptic activity 
%  from a number of separate scans and computes the time series of 
%  synaptic activity in each brain region.  It also generates a matrix
%  the summed synaptic activity for each scan.
%
%  This program performs a within subject analysis.  Furthermore, it
%  corresponds to the case where the synaptic activity is the mean of 
%  that between the stimulus-relevant and stimulus-irrelevant neurons.
%
%  The attention (scan) list must be called attnlist, which is a list of the
%  directories having data for each scan.
%
%  This program correspond to case when prefrontal cortex is broken
%  up into 4 separate regions.
%  
%  Written:  July 2003 by B. Horwitz
%            (modified from combinesumsynactpf.m)

workdir=pwd;

[nrows,ncols]=size(attnlist);

allsynact=[];
allintgract=[];


for i=1:nrows
  eval(['cd ',attnlist(i,:)]);
  load resultpf_2_fmri
  allsynact=[allsynact;synactmean];
  allintgract=[allintgract; intgractmean];
  eval(['cd ',workdir]);
end

save allactivity_fmri allsynact allintgract

clear intgract synact

