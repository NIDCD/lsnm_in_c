%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% plotaud_rl.m
%
% written by: B. Warner
% 07/21/03
%
% for use with AUDITORY MODEL
%
% loads both right and left hemisphere .out files
% and plots them on top of each other
%
% A1 and A2 regions on Figure 1
% STG and PFC regions on Figure 2
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load ea1d.out,load eg1d.out
load ea1u.out,load eg1u.out
load ea2c.out,load eg2c.out
load ea2d.out,load eg2d.out
load ea2u.out,load eg2u.out
load estg.out,load egtg.out
load exfs.out,load egfs.out
load efd1.out,load egd1.out
load efd2.out,load egd2.out
load exfr.out,load egfr.out

xmax=length(ea1d);
ymax=1;

figure(1)
subplot(5,1,1),plot(eg1d,'b'),hold on,plot(ea1d,'r'),title('A1d');
axis([0 xmax 0 ymax])
subplot(5,1,2),plot(eg1u,'b'),hold on,plot(ea1u,'r'),title('A1u');
axis([0 xmax 0 ymax])
subplot(5,1,3),plot(eg2d,'b'),hold on,plot(ea2d,'r'),title('A2d');
axis([0 xmax 0 ymax])
subplot(5,1,4),plot(eg2c,'b'),hold on,plot(ea2c,'r'),title('A2c');
axis([0 xmax 0 ymax])
subplot(5,1,5),plot(eg2u,'b'),hold on,plot(ea2u,'r'),title('A2u');
axis([0 xmax 0 ymax])

figure(2)
subplot(5,1,1),plot(egtg,'b'),hold on,plot(estg,'r'),title('STG');
axis([0 xmax 0 ymax])
subplot(5,1,2),plot(egfs,'b'),hold on,plot(exfs,'r'),title('FS');
axis([0 xmax 0 ymax])
subplot(5,1,3),plot(egd1,'b'),hold on,plot(efd1,'r'),title('D1');
axis([0 xmax 0 ymax])
subplot(5,1,4),plot(egd2,'b'),hold on,plot(efd2,'r'),title('D2');
axis([0 xmax 0 ymax])
subplot(5,1,5),plot(egfr,'b'),hold on,plot(exfr,'r'),title('FR');
axis([0 xmax 0 ymax])

%Figure for added regions
% figure(3)
% subplot(1,1,1),plot(epdt,'b'),title('EPDT');
% axis([0 xmax 0 ymax])

clear all
