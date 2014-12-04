% separatetask_fmri.m -- July 2003
%
% FORMAT:  separatetask_fmri
%
% This program loads task.mat and allactivity.mat in order to separate the
% the form-task blocks and the control blocks.  The separated data is saved in
% a .mat file called sepsynact.mat containing matrices 'tasksynact' and 
% 'ctrlsynact'.
%
% This program also creates two new files containing timing data (T, Tblock,
% nb, etc...) like task.mat.  They are called septask.mat and sepctrl.mat.
%
% Additionally, this program calculates the means for each block, found in
% 'taskmeans' and 'ctrlmeans', as well as total means for all tasks or all
% controls.
%
% Written 07/30/03 by Brent Warner

load allactivity_fmri;

TCsynact=[allsynact(351:525,:);allsynact(526:700,:)];
tonesynact=[allsynact(1:175,:);allsynact(176:350,:)];
ctrlsynact=[allsynact(701:875,:);allsynact(876:1050,:)];

TCmean =(TCsynact(1:175,:)+TCsynact(176:350,:))./2;
tonemean = (tonesynact(1:175,:)+tonesynact(176:350,:))./2;
ctrlmean = (ctrlsynact(1:175,:)+ctrlsynact(176:350,:))./2;

allTCmean = mean(TCmean);
alltonemean = mean(tonemean);
allctrlmean = mean(ctrlmean);

save sepsynact_fmri TCsynact tonesynact ctrlsynact;
save sepmeans_fmri TCmean tonemean ctrlmean allTCmean alltonemean allctrlmean;

T=T/3;
save septask T T1 T2 T3 T4 Tb1 Tb2 Tb3 Tblock Ttrial nb nt;
save sepctrl T T1 T2 T3 T4 Tb1 Tb2 Tb3 Tblock Ttrial nb nt;



