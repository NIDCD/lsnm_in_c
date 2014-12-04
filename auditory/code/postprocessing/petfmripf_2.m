%  petfmripf_2.m -- Aug. 1998
%  revised from petfmripf.m for adding new groups {EA1PT, IA1PT}
%
%  FORMAT:  p=petfmripf_2(m)
%
%	p=vector (rows=timepoints, columns=regions)
%	m=matrix of values from spec_pet.m
%
%  Keeps each prefrontal area as a separate region.
%
%  This function takes a matrix of the simulated synaptic activity data
%  that corresponds to a series of writeouts, in which
%  each row corresponds to the time-integrated value (since the previous
%  writeout) of the sum of the abs. values of the excitatory and 
%  inhibitory synaptic activity onto each neuronal population (in the
%  following order):  
%
%  ECtl, ICtl, MGN, EA1d, IA1d, EA1u, IA1u, EA1PT, IA1PT,
%  EA2d, IA2d, EA2u, IA2u, EA2c, IA2c, ESTG, ISTG,
%  ExFs, InFs, EFD1, IFD1, EFD2, IFD2, ExFR, InFR
%
%  eg1d, ig1d, eg1u, ig1u, eg2d, ig2d, eg2u, ig2u,
%  eg2c, ig2c, egtg, igtg, egfs, igfs , egd1, 
%  igd1, egd2, igd2, egfr, igfr
%
%
%  If just 1 hemisphere is present:
%  The function returns a 8-element vector with the integrated synaptic 
%  activities of the following areas:
%     control, A1, A2, STG, PFs, PFd1, PFd2, PFr
%
% 
%  If 2 hemispheres are present:
%  The function returns a 15-element vector with the integrated synaptic
%  activities of the following areas:
%     control, A1, A2, STG and PFs, PFd1, PFd2, PFr (right side)
%              A1, A2, STG, PFs, PFd1, PFd2, PFr (left side)
%
%  Written:  12-15-97 by B. Horwitz
%  Modified by T. Long, 8/98
%  Modified from pet.m (written by M. Tagamets)
%  Revised by F. Rong 5/05

function p = petfmripf_2(m)

s = size(m);
rws = s(1);			% Total rows in matrix
%r(:,:) = m(1:2:rws,:) - m(2:2:rws,:);
%rws = rws/2;
for i=1:rws
 p(i,1) = m(i,1) + m(i,2);		% Control
 p(i,2) = sum(m(i,4:9)) / 2;		% A1
 p(i,3) = sum(m(i,10:15)) / 3;		% A2
 p(i,4) = sum(m(i,16:17));		% STG
 p(i,5)  = sum(m(i,18:19));	        % Prefrontal S
 p(i,6)  = sum(m(i,20:21));		% Prefrontal D1
 p(i,7)  = sum(m(i,22:23));		% Prefrontal D2
 p(i,8)  = sum(m(i,24:25));		% Prefrontal R
end;

if  s(2) > 25			% two sides of brain
  for i=1:rws
   p(i,9) = sum(m(i,26:29)) / 2;	% A1-left
   p(i,10) = sum(m(i,30:35)) / 3;	% A2-left
   p(i,11) = sum(m(i,36:37));		% STG-left
   p(i,12)  = sum(m(i,38:39));	% Prefrontal S
   p(i,13)  = sum(m(i,40:41));	% Prefrontal D1
   p(i,14)  = sum(m(i,42:43));	% Prefrontal D2
   p(i,15)  = sum(m(i,44:45));	% Prefrontal R

   %GGNs is column 46, which we are not printing out

  end	
end

clear s rws i




