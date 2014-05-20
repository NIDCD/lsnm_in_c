%  loadmovieB.m -- Aug. 1998
%
%  FORMAT:  m=loadmovieB;
%
%	both hemispheres-separate input for left (ggns)
%	excitatory regions
%
%  This function loads all the 'out' files needed to make a movie of
%  the neuronal activity in the following brain regions (from left to 
%  right:  LGN, EV1v, EV4v, IT, ExFS, EFD1, EFD2, ExFR
%  left:   ggns eg1v eg4v exgt egfs egd1 egd2 egfr;
%
%  Calls:  mov2.m
%
%  It also makes the frames for the movie using the subprogram mov2.m.
%
%  To play the movie, enter movie(m,nt), where m is the loaded movie,
%  and nt is the number of times you want the movie repeated.

%  Written:  8/98 by T. Long
%  Modified from loadmovie.m (written by M. Tagamets)


function m = loadmovieB

figure('Position',[200 20 800 200]);
axis('off');

%load right side
load lgns.out;
load ev1v.out;
load ev4v.out;
load exss.out;
load exfs.out;
load efd1.out;
load efd2.out;
load exfr.out;

right = [lgns ev1v ev4v exss exfs efd1 efd2 exfr];
clear lgns efd1 efd2 exfr exfs exss ev4v ev1v;

%load left side
load ggns.out;
load eg1v.out;
load eg4v.out;
load exgt.out;
load egfs.out;
load egd1.out;
load egd2.out;
load egfr.out;

left = [ggns eg1v eg4v exgt egfs egd1 egd2 egfr];
clear ggns eg1v eg4v exgt egfs egd1 egd2 egfr;

n = length(right(:,1));

m = mov2(left(10:n,:), right(10:n,:),81);

