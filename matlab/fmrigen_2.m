%  fmrigen_2.m  -- July 2003
%
%  FORMAT:   fmrigen_2
%__________________________________________________________
%
%  This program will generate the sampled hemodynamically-delayed
%  activity (integrated activity over Ti, sampled every Tr)
%  (fmriact2) that would represent what is seen by fMRI.  It also
%  produces the hemodynamically delayed synaptic activity (act4).
%  A new synaptic activity matrix, synact4, also is outputted.  All have
%  time units in seconds.
%
%  Calls:  convol.m
%  
%  The input parameters are: 
%
%  allsynact=synact is the summed integrated (over time Ti) synaptic activity
%            for the entire "scan"
%
%  Task parameters (found in the file task.mat)
%
%  Ti=neural time interval needed to acquire a slice of fMRI data
%  lambda=parameter (in sec.) for the Poisson distributed hemodyn. delay
%  T=total time of scanning experiment
%  Tr=frame time (time needed to sample hemo activity to produce each
%                          fMRI volume)
%  delay=time interval between beginning of study and when fMRI data
%             starts to be acquired.
%  Ttrial=time (in sec.) for one complete trial
%
%  All time units are in seconds. 
%
%  The output matrices, synact4, act4 and fmriact2 have as their first 
%  column the time (in seconds), the second thru eighth  represent activity
%  in A1, A2, STG and PFC (fs,d1,d2,fr), respectively.  
%
%  Two time vectors (Tsyn4 and Tmr2) also are computed; the former
%  is in steps of Ti, the latter in steps of Tr; units are in seconds.
%
%  Finally, we delete the first stimulus trial to get our final time courses
%  and make sure the beginning and ending time points are the same for
%  fmriact2, act4, and synact4.
%
%  Final output variables are called synact4, act4, fmriact2, Tsyn4 and 
%  Tmr2.
%
%----------------------------------------------

%  Written 7-03 by B. Horwitz (modified from fmrigen.m)

[r, c]=size(allsynact);
 
begin=zeros(1,c+1);
 
synact1=[begin;(1:r)' allsynact];
 
Tsyn=(0:Ti:T)';
 
synact1=[Tsyn synact1(:,(2:c+1))];


act=convol(synact1,lambda,Ti,T);
act(:,1)=Tsyn;


%  Convert seconds to Ti units

delaynew=round(delay/Ti);
TRnew=round(Tr/Ti);


% Generate fMRI activity

[r, c]=size(act);
act1rows=fix((r-delaynew)/TRnew);
activity1=zeros(act1rows,c);

for i=1:act1rows
	A=delaynew+1+i*TRnew;
	activity1(i,:)=act(A,:);
end
v=(delay+Tr):Tr:T;
activity1(:,1)=v';
Tmr=v';
fmriact1=activity1;

%  Remove first trial

synticks=Ttrial/Ti+1; 
mrticks=round(Ttrial/Tr);

Tsyn2=Tsyn(synticks+1:length(Tsyn));
synact2=synact1(synticks+1:length(Tsyn),:);
act2=act(synticks+1:length(Tsyn),:);
delaynew=round(delay/Ti);
TRnew=round(Tr/Ti);
Tmr2=Tmr(mrticks:length(Tmr)); 
fmriact2=fmriact1(mrticks:length(Tmr),:);

%  Make beginning and end time points the same for 
%  the hemodyn. synaptic activity and the fMRI activity

ivalue=1; jvalue=length(Tsyn2);

%  First, the beginning time points

tmax1=length(Tmr2); tmax2=length(Tsyn2);

if Tmr2(1)==Tsyn2(1)
  act3=act2;
  synact3=synact2;
  Tsyn3=Tsyn2;
elseif Tmr2(1)>Tsyn2(1);
  ivalue=find(Tsyn2==Tmr2(1));
  Tsyn3=Tsyn2(ivalue:tmax2);
  act3=act2(ivalue:tmax2,:);
  synact3=synact2(ivalue:tmax2,:);
  jvalue=length(Tsyn3);
elseif Tmr2(1)<Tsyn2(1);
  Tmr2=Tmr2(2:tmax1);
  fmriact2=fmriact2(2:tmax1,:);
  tmax1=length(Tmr2);
  ivalue=find(Tsyn2==Tmr2(1));
  Tsyn3=Tsyn2(ivalue:tmax2);
  act3=act2(ivalue:tmax2,:);
  synact3=synact2(ivalue:tmax2,:);
  jvalue=length(Tsyn3);
end

%  Now, the end time points

tmax3=length(Tsyn3); 

if Tmr2(tmax1)==Tsyn3(tmax3)
  act4=act3;
  synact4=synact3;
  Tsyn4=Tsyn3;
elseif Tmr2(tmax1)<Tsyn3(tmax3)
  jvalue=find(Tsyn3==Tmr2(tmax1));
  Tsyn4=Tsyn3(1:jvalue);
  act4=act3(1:jvalue,:);
  synact4=synact3(1:jvalue,:);
elseif Tmr2(tmax1)>Tsyn3(tmax3)
  Tmr2=Tmr2(1:tmax1-1);
  jvalue=find(Tsyn3==Tmr2(length(Tmr2)));
  Tsyn4=Tsyn3(1:jvalue);
  act4=act3(1:j,:);
  synact4=synact3(1:jvalue,:);
  fmriact2=fmriact2(1:length(Tmr2),:);
end