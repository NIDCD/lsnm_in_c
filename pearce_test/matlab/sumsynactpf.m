%  sumsynactpf.m -- Aug. 1998
%
%  FORMAT:  sumsynactpf
%
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
%  ECtl, ICtl, LGN,  EV1h, IV1h, EV1v, IV1v, EV4c, IV4c, 
%  EV4h, IV4h, EV4v, IV4v, ExSs, InSs, ExFrs, InFrs, EFD1,
%  IFD1, EFD2, IFD2, ExFR, InFR
%
%  eg1h, ig1h, eg1v, ig1v, eg4c, ig4c, 
%  eg4h, ig4h, eg4v, ig4v, exgt, ingt, egfs, igfs , egd1, 
%  igd1, egd2, igd2, egfr, igfr
%
%  Note that the left side input GGNS comes after igfr, but we
%  do not compute this input (we do not compute LGNS either)
%
%  If just 1 hemisphere is present:
%  The function returns a 8-element vector with the fmri (rCBF) activities
%  of the following areas:
%     control, V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr
%
%  If 2 hemispheres are present:
%  The program returns a 15-element vector with the fmri or PET (rCBF)
%  activities of the following areas:
%     control, V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr  (right side)
%                 V1, V4, IT/TEO, PFs, PFd1, PFd2, PFr  (left side)
%
%  It saves the resulting matrix to a Matlab file.; it also saves a vector 
%  containing the summed integrated activity.
%
%  Calls: petfmripf.m
%
%  Written:  1-18-98 by B. Horwitz
%  Modified 8-98 by T. Long

load spec_pet.m

synact=petfmripf(spec_pet);

  intgract=sum(synact);
  save resultpf synact intgract;