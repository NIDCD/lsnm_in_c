%  topthreshdetect.m
%
%  Written:  Jan 2004 by Brent Warner
%  Updated:  March 2004 by Brent Warner
%
%  The program traverses all of the attention levels and trials for each
%  subject, checking the number of response units that exceed some threshold
%  value.  
%
%  This program should be run from a directory containing all of the subject
%  directories.  The files 'subjectlist.mat', 'attnlist.mat', and
%  'triallist.mat' should be present in this directory.
%
%  The code for detecting the number of neurons above threshold is adapted from
%  Mike Chen's 2001 program, response_number.m

thresh=input('Enter threshold value: ');

fid=fopen('threshold.txt','w');

workdir=pwd;

load subjectlist
load attnlist
load triallist

load task
start=(T0+T1+T2+T3)*200;
stop=Ttrial*200;

[nsubjs,subjcols]=size(subjectlist);
[nattns,attncols]=size(attnlist);
[ntrials,trialcols]=size(triallist);

for i=1:nsubjs
  eval(['cd ',subjectlist(i,:)]);
  subjdir=pwd;
  fprintf(fid,'%s:\n',subjectlist(i,:));
  for j=1:nattns
     eval(['cd ',attnlist(j,:)]);
     attndir=pwd;
     fprintf(fid,'\t%s:\n',attnlist(j,:));
     for k=1:ntrials
        eval(['cd ',triallist(k,:)]);
        eval('!gunzip egfr.out.gz');
	eval('!gunzip exfr.out.gz');
	load exfr.out
	for n=start:stop;
	   mat1(n,:)=exfr(n,:);
	end
	A1=zeros(size(mat1));
	A1(find(mat1>thresh))=1;
	B1=sum(A1);
        load egfr.out
	for n=start:stop;
	   mat2(n,:)=egfr(n,:);
	end
        A2=zeros(size(mat2));
        A2(find(mat2>thresh))=1;
        B2=sum(A2);
        neuron_count1=length(find(B1~=0));
	neuron_count2=length(find(B2~=0));
        fprintf(fid,'\t\t%s \t%d \t%d\n',triallist(k,:),neuron_count1 , neuron_count2);
        eval('!gzip egfr.out');
	eval('!gzip exfr.out');
        eval(['cd ',attndir]);
     end
     eval(['cd ',subjdir]);
  end
  eval(['cd ',workdir]);
end

fclose(fid);

