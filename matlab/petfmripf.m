%  petfmripf.m -- Aug. 1998
%
%  FORMAT:  p=petfmripf(m)
%
%	p=vector (rows=timepoints, columns=regions)
%	m=matrix of values from spec_pet.m
%
%  Keeps each prefrontal area as a separate region.
%
%  This function takes a matrix of the simulated fMRI (or PET) data
%  that corresponds to a series of writeouts, in which
%  each row corresponds to the time-integrated value (since the previous
%  writeout) of the sum of the abs. values of the excitatory and 
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
%
%  If just 1 hemisphere is present:
%  The function returns a 8-element vector with the fmri (rCBF) activities
%  of the following areas:
%     control, V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr
%
% 
%  If 2 hemispheres are present:
%  The function returns a 15-element vector with the fmri (rCBF)
%  activities of the following areas:
%     control, V1, V4, IT/TEO and PFs, PFd1, PFd2, PFr (right side)
%                 V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr (left side)
%
%  Written:  12-15-97 by B. Horwitz
%  Modified by T. Long, 8/98
%  Modified from pet.m (written by M. Tagamets)

function p = petfmripf(m)

s = size(m);
rws = s(1);			% Total rows in matrix
%r(:,:) = m(1:2:rws,:) - m(2:2:rws,:);
%rws = rws/2;
for i=1:rws
 p(i,1) = m(i,1) + m(i,2);		% Control
 p(i,2) = sum(m(i,4:7)) / 2;		% V1
 p(i,3) = sum(m(i,8:13)) / 3;		% V4
 p(i,4) = sum(m(i,14:15));		% IT/TEO
 p(i,5)  = sum(m(i,16:17));	          % Prefrontal S
 p(i,6)  = sum(m(i,18:19));		% Prefrontal D1
 p(i,7)  = sum(m(i,20:21));		% Prefrontal D2
 p(i,8)  = sum(m(i,22:23));		% Prefrontal R
end;

if  s(2) > 25			% two sides of brain
  for i=1:rws
   p(i,9) = sum(m(i,24:27)) / 2;	% V1-left
   p(i,10) = sum(m(i,28:33)) / 3;	% V4-left
   p(i,11) = sum(m(i,34:35));		% IT/TEO-left
   p(i,12)  = sum(m(i,36:37));	% Prefrontal S
   p(i,13)  = sum(m(i,38:39));	% Prefrontal D1
   p(i,14)  = sum(m(i,40:41));	% Prefrontal D2
   p(i,15)  = sum(m(i,42:43));	% Prefrontal R

   %GGNs is column 44, which we are not printing out

  end	
end

clear s rws i




