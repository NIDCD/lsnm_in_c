%  sumsynactpf_2_fmri.m -- July 2003
%  revised May 2005 for synchronized MEG/fMRI simulation
%
%  FORMAT:  sumsynactpf_2_fmri
%
%  OUTPUT:  resultpf_2_fmri.mat
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
%  Stimulus Relevant Regions  
%
%  ECtl, ICtl, MGNS,  EA1d, IA1d, EA1u, IA1u, EA1PT, IA1PT,
%  EA2d, IA2d, EA2u, IA2u, EA2c, IA2c, ESTG, ISTG,
%  ExFs, InFs, EFD1, IFD1, EFD2, IFD2, ExFR, InFR
%
%  Stimulus Irrelevant Regions (Non-specific processining)
%
%  eg1d, ig1d, eg1u, ig1u, eg2d, ig2d, eg2u, ig2u,
%  eg2c, ig2c, egtg, igtg, egfs, igfs , egd1, 
%  igd1, egd2, igd2, egfr, igfr
%
%  Note that the left side input GGNS comes after igfr, but we
%  do not compute this input (For MGNS, the synaptic activity should be
%  zeroes)
%
%  The function returns a 7-element vector with the integrated synaptic 
%  activities of the following areas:
%     A1, A2, STG, PFs, PFd1, PFd2, PFr
%
%  These represent the mean values of both the stimulus relevant and stimulus
%  irrelevant neurons.
%
%  It saves the resulting matrix to a Matlab file.; it also saves a vector 
%  containing the summed integrated activity.
%
%  Modified version of sumsynactpf.m; for use with double-sized regions
%
%  Calls: petfmripf_2.m
%
%  Written:  7-03 by B. Horwitz
%  Revised:  5-05 by F. Rong

load spec_pet

synact=petfmripf(spec_pet);

[nr,nc]=size(synact);
synact=synact(:,2:nc);			% eliminates control region
[nrows,ncols]=size(synact);
synactmean=(synact(:,1:ncols/2) + synact(:,((ncols/2)+1):ncols))./2;

intgractmean=sum(synactmean);
save resultpf_2 synactmean intgractmean;