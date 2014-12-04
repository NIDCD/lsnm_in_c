%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% plotvisual.m
%
% Written by:  Brent Warner
% 07/02/03
%
% for use with VISUAL model
%
% loads right hemisphere *.out files in current
% directory and plots them.
%
% IT and PFC regions on Figure 2
% V1 and V4 regions on Figure 1
% 
% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load efd1.out
load efd2.out
load ev1h.out
load ev1v.out
load ev4c.out
load ev4h.out
load ev4v.out
load exfr.out
load exfs.out
load exss.out

figure(2)
subplot(5,1,1),plot(exss),title('EXSS')
subplot(5,1,2),plot(exfs),title('EXFS')
subplot(5,1,3),plot(efd1),title('EFD1')
subplot(5,1,4),plot(efd2),title('EFD2')
subplot(5,1,5),plot(exfr),title('EXFR')

figure(1)
subplot(5,1,1),plot(ev1h),title('EV1H')
subplot(5,1,2),plot(ev1v),title('EV1V')
subplot(5,1,3),plot(ev4h),title('EV4H')
subplot(5,1,4),plot(ev4c),title('EV4C')
subplot(5,1,5),plot(ev4v),title('EV4V')

clear all
