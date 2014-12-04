%  calcPSC.m
%
%  FORMAT calcPSC
% 
%  ___________________________________
%
%  This program, for each subject, goes through the directories
%  and generates percent signal change (PSC) as consider both the
%  tone, tonal contour and control tasks
%
%  Calls: subjectlist.mat
%
%------------------------------------------------------------------

%  Written August 2005 by F. Rong

load subjectlist
[nsub nsubc]=size(subjectlist);
workdir=pwd;

for iis=1:nsub
	eval(['cd ',subjectlist(iis,:)])
	load fmriTC;
	TC=sum(fmridata(:,2:8));
        load fmritone;
	Tone=sum(fmridata(:,2:8));
        load fmrictrl;
	B=sum(fmridata(:,2:8));
	nTC=(TC-B)./B;
        nTones=(Tone-B)./B;
        pPSC=(nTC-nTones)./nTones.*100;
        save PSC pPSC;
	eval(['cd ',workdir])
end
	