%  topcombinesynactpf_2_fmri.m -- July 2003
%  Revised for synchronously simulation of MEG/fMRI with new A1PT group
%  -- May 2005
%
%  FORMAT: topcombinesynactpf_2_fmri
%
%  Calls:  combinesumsynactpf_2_fmri.m
%          subjectlist.mat, attnlist.mat
%
%  This program is used when we simulate the case with both stimulus-
%  relevant and stimulus-irrelevant neurons.
%
%  It is used when we have multiple sets of data.  Each set consists of
%  identical directories of subject-attention levels. Each directory name
%  starts with 'b' followed by a two digit designation of attention
%       e.g., b20 ==>  relevant attention level = 0.20
%
%  This code goes down the hierarchy of a directory, loads the 
%  time series of integrated synaptic activity from a number of separate 
%  scans and computes the time series of synaptic activity in each brain 
%  region.  It also generates a matrix the summed synaptic activity for 
%  each scan.  It then produces the combined time series of activity over
%  all the attention levels of the subject.
%
%  It does this for each of the subject directories in which such data is located.
%
%  The subject list must be called subjectlist, which is a list of the
%  directories having data for each scan.  The attention list must be called
%  attnlist.
%
%  This program correspond to case when prefrontal cortex is broken
%  up into 4 separate regions.
%  
%
%  In essence, this program combines sumsynactpf_2 and combinesumsynactpf_2.
%
%  Written:  July 2003 by B. Horwitz
%            (modified from topcombinesynactpf.m)

cworkdir=pwd;

load subjectlist
load attnlist

[nrp,ncp]=size(attnlist);

[nrowsp,ncolsp]=size(subjectlist);

for ii=1:nrowsp
  eval(['cd ',subjectlist(ii,:)]);
  combinesumsynactpf_2_fmri
  clear allsynact allintgract
  eval(['cd ',cworkdir]);
end


