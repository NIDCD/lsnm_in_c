%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% plotvis_rl.m
%
% written by: B. Warner
% 07/18/03
%
% for use with VISUAL MODEL
%
% loads both right and left hemisphere .out files
% and plots them on top of each other
%
% V1 and V4 regions on Figure 1
% IT and PFC regions on Figure 2
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load efd1.out,load egd1.out
load efd2.out,load egd2.out
load ev1h.out,load eg1h.out
load ev1v.out,load eg1v.out
load ev4c.out,load eg4c.out
load ev4h.out,load eg4h.out
load ev4v.out,load eg4v.out
load exfr.out,load egfr.out
load exfs.out,load egfs.out
load exss.out,load exgt.out

figure(1)
subplot(5,1,1),plot(eg1h,'b'),hold on,plot(ev1h,'r'),title('V1h');
subplot(5,1,2),plot(eg1v,'b'),hold on,plot(ev1v,'r'),title('V1v');
subplot(5,1,3),plot(eg4h,'b'),hold on,plot(ev4h,'r'),title('V4h');
subplot(5,1,4),plot(eg4c,'b'),hold on,plot(ev4c,'r'),title('V4c');
subplot(5,1,5),plot(eg4v,'b'),hold on,plot(ev4v,'r'),title('V4v');

figure(2)
subplot(5,1,1),plot(exgt,'b'),hold on,plot(exss,'r'),title('IT');
subplot(5,1,2),plot(egfs,'b'),hold on,plot(exfs,'r'),title('FS');
subplot(5,1,3),plot(egd1,'b'),hold on,plot(efd1,'r'),title('D1');
subplot(5,1,4),plot(egd2,'b'),hold on,plot(efd2,'r'),title('D2');
subplot(5,1,5),plot(egfr,'b'),hold on,plot(exfr,'r'),title('FR');

clear all