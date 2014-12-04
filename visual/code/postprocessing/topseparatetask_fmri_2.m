% topseparatetask_fmri.m -- July 2003
%
% FORMAT: topseparatetask_fmri
%
% This program loads the synaptic activity from a number of subjects &
% attention levels and separates the task blocks and the control blocks by
% calling separatetask in each directory.
%
% The list of subjects must be called 'subjectlist' and the list of attention
% levels must be called 'attnlist'.
%
% calls:  separatetask.m
%         subjectlist.mat, task.mat
%
% written 07/30/03 by Brent Warner

workdir=pwd;

load subjectlist

[srow,scol]=size(subjectlist);

for i=1:srow
  load task
  eval(['cd ',subjectlist(i,:)]);
  separatetask_fmri_2;
  eval(['cd ',workdir]);
end
