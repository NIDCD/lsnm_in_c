%  Written by:  B. Warner
%  07/09/03
%
%  Modified from loadmovieR.m and loadmovieB.m (by T. Long/M. Tagamets)
%
%  This is for use with mkbatchr_au.cc, and creates a movie displaying
%  all right side regions plus the left side MGN units

function m = loadmovieR_au

figure('Position',[200 20 800 200]);
axis('off');

% load .out files

load ea1d.out
load ea1u.out
load ea2c.out
load ea2d.out
load ea2u.out
load efd1.out
load efd2.out
load estg.out
load exfr.out
load exfs.out
load gmgn.out
load mgns.out

aa = [mgns ea1u ea1d ea2u ea2c ea2d];
clear mgns ea1u ea1d ea2u ea2c ea2d;

bb = [gmgn estg exfs efd1 efd2 exfr];
clear gmgn estg exfs efd1 efd2 exfr];

n = length(aa(:,1));

m = mov2(aa(10:n,:), bb(10:n,:),81);