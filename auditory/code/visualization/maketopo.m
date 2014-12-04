% maketopo.m
%
% written 07/11/03
% by B. Warner
%
% this program takes the .out files in the current directory
% and manipulates them so that, when plotted, they show
% the topographical version (like antonio's model)
% 
% right now this only does the right hemisphere and left MGN

clear all

%load ea1d.out
%load ea1u.out
%load ea2c.out
%load ea2d.out
%load ea2u.out
%load efd1.out
%load efd2.out
%load estg.out
%load exfr.out
%load exfs.out
load gmgn.out
load mgns.out

[nrows,ncols]=size(mgns);

for i=1:ncols
%  ea1d(:,i)=i+ea1d(:,i);
%  ea1u(:,i)=i+ea1u(:,i);
%  ea2c(:,i)=i+ea2c(:,i);
%  ea2d(:,i)=i+ea2d(:,i);
%  ea2u(:,i)=i+ea2u(:,i);
%  efd1(:,i)=i+efd1(:,i);
%  efd2(:,i)=i+efd2(:,i);
%  estg(:,i)=i+estg(:,i);
%  exfr(:,i)=i+exfr(:,i);
%  exfs(:,i)=i+exfs(:,i);
  gmgn(:,i)=i+gmgn(:,i);
  mgns(:,i)=i+mgns(:,i);
end