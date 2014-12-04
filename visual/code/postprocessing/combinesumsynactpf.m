%  combinesumsynactpf.m -- Feb. 2000
%
%  FORMAT: combinesumsynactpf
%
%  This program loads the time series of integrated synaptic activity 
%  from a number of separate scans and computes the time series of 
%  synaptic activity in each brain region.  It also generates a matrix
%  the summed synaptic activity for each scan.
%
%  The subject(scan) list must be called subjectlist, which is a list of the
%  directories having data for each scan.
%
%  This program correspond to case when prefrontal cortex is broken
%  up into 4 separate regions.
%  
%  Written:  Feb. 2000 by B. Horwitz

workdir=pwd;

[nrows,ncols]=size(subjectlist);

allsynact=[];
allintgract=[];

for i=1:nrows
  eval(['cd ',subjectlist(i,:)]);
  load resultpf
  allsynact=[allsynact;synact];
  allintgract=[allintgract; intgract];
  eval(['cd ',workdir]);
end

save allactivity allsynact allintgract

clear intgract synact



