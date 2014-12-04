%simMEG () -- function adapts forward model (Cuffin & Cohen 1977) to generate
%synthetic MEG signal with simulated dipole currents from the neural network.
%The inputs are the time series represents the simulated integrative synaptic
%activity in separate cortical areas. The outputs will be the synthetic MEG
%signal on all sensors accounting to these activities.
%%%%%%%%%%%%%%%%%%%% Input Arguments %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%srcSDC -- simulated dipole currents (# sources, # of time samples).       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%% Output Arguments %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%sigMEG -- simulated MEG signals (# sensors, # time samples).              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
% Programs called: Tlr2Sph.m, calcMEG.m
% by Feng Rong 2005/10/24

function sigMEG=simMEG(srcSDC);

 
load fidmarkers; % load the coordinates of the fiducial markers
load sourcelocs; % load the Talairach coordinates of the source locations
load sensorlocs; % load the spherical coordinates of the sensor loacations

[NumSensors,dimSensors]=size(sensorlocs);
[NumSources,NumSamples]=size(srcSDC);

sphsrcloc=Tlr2Sph(sourcelocs, fidmarkers);
sigMEG=zeros(NumSensors,NumSamples);
for n=1:7
   sigMEG_src=calcMEG(srcSDC(n,:),sphsrcloc(n,:));
   sigMEG=sigMEG+sigMEG_src;
end

save synsigMEG sigMEG;





























































































































































