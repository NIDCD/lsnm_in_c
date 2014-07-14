%---------------------------------------------------------------
% Mike Chen, July 2001
% This program counts the number of neurons in a given area that fire 
% above a threshold level during the response phase.
%
% The region analyzed in the response population depends on 
% the length of the stimuli and gap used (see below for
% choices).
%
% Updated by Antonio Ulloa on Tue Aug 20 13:57:28 EDT 2002
%---------------------------------------------------------------

% input file to be looked at.
load('exfr.out'  );
%load('exfr_a.out');
%load('exfr_b.out');

% threshold level.
threshold=0.6;

A=zeros(size(exfr));
A(find(exfr>threshold))=1;
B=sum(A);
R1=length(find(B>0))

A=zeros(size(exfr_a));
A(find(exfr_a>threshold))=1;
B=sum(A);
R2=length(find(B>0))

A=zeros(size(exfr_b));
A(find(exfr_b>threshold))=1;
B=sum(A);
R3=length(find(B>0))
