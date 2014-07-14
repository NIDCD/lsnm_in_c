%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% plot_audleft.m
%
% written by:  B. Warner
% 07/16/03
%
% for use with AUDITORY model
%
% loads left hemisphere *.out files
% in current directory and plots them
%
% figure (1): Ai and Aii regions
% figure (2): STG and PFC regions
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load eg1d.out
load eg1u.out
load eg2d.out
load eg2u.out
load eg2c.out
load egd1.out
load egd2.out
load egtg.out
load egfr.out
load egfs.out

ymax = 1;
xmax = length(eg1d);

figure(3)
subplot(5,1,1),plot(eg1u),title('Ai_u')
axis([0 xmax 0 ymax])
subplot(5,1,2),plot(eg1d),title('Ai_d')
axis([0 xmax 0 ymax])
subplot(5,1,3),plot(eg2u),title('Aii_u')
axis([0 xmax 0 ymax])
subplot(5,1,4),plot(eg2c),title('Aii_c')
axis([0 xmax 0 ymax])
subplot(5,1,5),plot(eg2d),title('Aii_d')
axis([0 xmax 0 ymax])

figure(4)
subplot(5,1,1),plot(egtg),title('STG')
axis([0 xmax 0 ymax])
subplot(5,1,2),plot(egfs),title('FS')
axis([0 xmax 0 ymax])
subplot(5,1,3),plot(egd1),title('D1')
axis([0 xmax 0 ymax])
subplot(5,1,4),plot(egd2),title('D2')
axis([0 xmax 0 ymax])
subplot(5,1,5),plot(egfr),title('FR')
axis([0 xmax 0 ymax])




