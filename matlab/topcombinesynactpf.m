%  topcombinesynactpf.m -- Feb. 2000
%
%  FORMAT: topcombinesynactpf
%
%  Calls:  sumsynactpf.m
%
%  This program is used when we simulate both hemispheres, with cross
%  hemisphere connection.
%
%  It is used when we have multiple sets of data.  Each set consists of
%  identical directories of subject attention levels. Each directory name
%  starts with 'b' followed by a two digit designation of attention
%       e.g., b20 ==>  right side attention level = 0.20
%
%  This code goes down the hierarchy of a directorylike fRnL, loads the 
%  time series of integrated synaptic activity from a number of separate 
%  scans and computes the time series of synaptic activity in each brain 
%  region.  It also generates a matrix the summed synaptic activity for 
%  each scan.  It then produces the combined time series of activity over
%  all the attention levels of the subject.
%
%  It does this for each of the directories in which such data is located.
%
%  The subject(scan) list must be called subjectlist, which is a list of the
%  directories having data for each scan.  The directory list must be called
%  dirlist.
%
%  This program correspond to case when prefrontal cortex is broken
%  up into 4 separate regions.
%  
%  Written:  Feb. 2000 by B. Horwitz

workdir=pwd;

[nr,nr]=size(dirlist);

[nrows,ncols]=size(subjectlist);


for ii=1:nr

  eval(['cd ',dirlist(ii,:)]);

  allsynact=[];
  allintgract=[];
  workdir1=pwd;

  for i=1:nrows
    eval(['cd ',subjectlist(i,:)]);
    sumsynactpf;
    allsynact=[allsynact;synact];
    allintgract=[allintgract; intgract];
    eval(['cd ',workdir1]);
  end

  save allactivity allsynact allintgract

  clear intgract synact allsynact allintgract

  eval(['cd ',workdir]);

end


