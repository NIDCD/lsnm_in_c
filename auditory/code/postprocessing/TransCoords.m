%TransCoords () -- function implemented to transform the coordination of the
%sensors and the sources to fit in the forward model -- put the source on z
%axis and transform the coordinates of the sensors to fit this shift.
%
%by Feng Rong 2005/10/24

function [srcR,R,theta,phi]=TransCoords(srcloc,sensorlocs);

srcR=srcloc(1);
srctheta=srcloc(2);
srcphi=srcloc(3);

Shift_Coords=[0 -1*srctheta -1*srcphi];
Shift_sensorlocs=sensorlocs+Shift_Coords;

R=Shift_sensorlocs(:,1);
theta=Shift_sensorlocs(:,2);
phi=Shift_sensorlocs(:,3);
