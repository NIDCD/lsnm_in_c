%  petfmripf.m -- Aug. 1998 and Jan. 2004 and Oct 2004
%
%  FORMAT:  p=petfmripf_meg(m)
%
%	p=vector (rows=timepoints, columns=regions)
%	m=matrix of values from spec_pet.m
%
%  Keeps each prefrontal area as a separate region.
%
%  This function takes a matrix of the simulated MEG data
%  that corresponds to a series of writeouts, in which
%  each row corresponds to the time-integrated value (since the previous
%  writeout) of the sum of the differences of the excitatory and 
%  inhibitory synaptic activity onto each neuronal population (in the
%  following order):  
%
%  ECtl, ICtl, LGN, EV1h, IV1h, EV1v, IV1v, EV4c, IV4c, 
%  EV4h, IV4h, EV4v, IV4v, ExSs, InSs, ExFrs, InFrs, EFD1,
%  IFD1, EFD2, IFD2, ExFR, InFR
%
%  eg1h, ig1h, eg1v, ig1v, eg4c, ig4c, 
%  eg4h, ig4h, eg4v, ig4v, exgt, ingt, egfs, igfs , egd1, 
%  igd1, egd2, igd2, egfr, igfr
%
%  (or the equivalent set of auditory regions)
%
%  Note:  in the language below we refer to hemispheres, but what we
%  mean is specific neurons (right) and nonspecific (left)
%
%  If just 1 hemisphere is present:
%  The function returns a 8-element vector with the MEG activities
%  of the following areas:
%     control, V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr
%
% 
%  If 2 hemispheres are present:
%  The function returns a 15-element vector with the MEG
%  activities of the following areas:
%     control, V1, V4, IT/TEO and PFs, PFd1, PFd2, PFr (right side)
%                 V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr (left side)
%
%  Here, we assume that the inhibiotyr populations do not contribute current
%  dipoles to the magnetic signals; thus, we combine only the excitatory
%  populations.
%
%  Written:  12-15-97 by B. Horwitz
%  Modified by T. Long, 8/98
%  Modified from pet.m (written by M. Tagamets)

function p = petfmripf_meg(m)

s = size(m);
rws = s(1);			% Total rows in matrix
%r(:,:) = m(1:2:rws,:) - m(2:2:rws,:);
%rws = rws/2;
for i=1:rws
 p(i,1) = m(i,1);		        % Control
 p(i,2) = sum(m(i,4:2:9)) / 2;		% V1
 p(i,3) = sum(m(i,10:2:15)) / 3;		% V4
 p(i,4) = m(i,16);			% IT/TEO
 p(i,5)  = m(i,18);	         	% Prefrontal S
 p(i,6)  = m(i,20);			% Prefrontal D1
 p(i,7)  = m(i,22);			% Prefrontal D2
 p(i,8)  = m(i,24);			% Prefrontal R
end;

if  s(2) > 25			% two sides of brain
  for i=1:rws
   p(i,9) = sum(m(i,26:2:29)) / 2;	% V1-left
   p(i,10) = sum(m(i,30:2:35)) / 3;	% V4-left
   p(i,11) = m(i,36);			% IT/TEO-left
   p(i,12)  = m(i,38);			% Prefrontal S
   p(i,13)  = m(i,40);			% Prefrontal D1
   p(i,14)  = m(i,42);			% Prefrontal D2
   p(i,15)  = m(i,44);			% Prefrontal R

   %GGNs is column 46, which we are not printing out

  end	
end

clear s rws i
