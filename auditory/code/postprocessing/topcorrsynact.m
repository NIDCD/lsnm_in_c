%  topcorrsynact.m
%
%  Format:  topcorrsynact
%
%  Calls:  corrsynact.m
%
%  This program applies corrsynact to each directory given by dirlist. 
%  It essentially is used when we have a set of directories in which each set
%  of subjects/runs were modified, perhaps by weakening the synaptic weights.
%
%  This program constructs the interregional correlations between the 
%  simulated synaptic activity(allsynact); it also does the same thing 
%  for the integrated activity (allintgract).  It produces both a standard
%  correlation matrix and a vector of correlation values in the order:
%
%  (r12 r13 r14 ... r23 r24 r25 ... etc)
%
%  Written:  2-00 by B. Horwitz
%

[dr dc]=size(dirlist);
base=pwd;

for i=1:dr
  eval(['cd ',dirlist(i,:)])
  corrsynact;
  eval(['cd ',base])
end
  

