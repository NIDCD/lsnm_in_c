%  loadmovieR.m -- Aug. 1998
%
%  FORMAT:  m=loadmovieR;
%
%	m=movie with every region in a line
%	right hemisphere only
%
%  This function loads all the 'out' files needed to make a movie of
%  the excitatory neuronal activity in the following brain regions 
%  (from left to right:  LGN, EV1v, EV4v, IT, ExFS, EFD1, EFD2, ExFR).
%
%  It also makes the frames for the movie using the subprogram mov.m.
%
%  To play the movie, enter movie(m,nt), where m is the loaded movie,
%  and nt is the number of times you want the movie repeated.
%
%  Calls:  mov.m
%
%  Written:  12-15-97 by B. Horwitz
%  Modified from loadmovie.m (written by M. Tagamets)

function m = loadmovieR

figure('Position',[200 30 600 100]);
axis('off')
load ('../../outputs/lgns.out', 'lgns');
load ('../../outputs/ev1v.out', 'ev1v');
load ('../../outputs/ev4v.out', 'ev4v');
load ('../../outputs/exss.out', 'exss');
load ('../../outputs/exfs.out', 'exfs');
load ('../../outputs/efd1.out', 'efd1');
load ('../../outputs/efd2.out', 'efd2');
load ('../../outputs/exfr.out', 'exfr');
aa = [lgns ev1v ev4v exss exfs efd1 efd2 exfr];
clear efd1 efd2 exfr exfs exss ev4v ev1v lgns;
n = length(aa(:,1));
m = mov(aa(1:n,:),81);
