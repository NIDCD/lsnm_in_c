%calcMEG() -- function applys the forward model to calculate synthetic MEG
%signal.
%%%%%%%%%%%%%%%%%%%%%%%% Input Arguments %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%SDC -- the simulated dipole currents of single  source
%srcloc -- the spherical coordinates of the dipole source
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%%%%%%%%%%%%%%%%%%%%%%%%% Output Arguments %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%sigMEG_src -- the simulated MEG signal of the sensors from this single
%source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%Call: TransCoords.m
%by Feng Rong 2005/10/24

function sigMEG_src=calcMEG(SDC,srcloc);

load sensorlocs;

[srcR,R,theta,phi]=TransCoords(srcloc,sensorlocs);

gamma=1-2*srcR.*cos(theta)./R+(srcR./R).^2;
sigMEG_src=(srcR.sin(theta).*sin(phi)./(4*pi.*R.^2.*gamma.^1.5)).*SDC;

