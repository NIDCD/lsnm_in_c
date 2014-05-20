set(Atts,1)
  {
    Write -1
    ActRule: Clamp
    OutputRule: SumOut
  }
 
set(ECtl,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE  0.2)}
    Node Activation { ALL 0.2 }
  }
 
set(ICtl,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE  0.2)}
    Node Activation { ALL 0.2 }
  }
 
set(LGNs,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: Clamp
    OutputRule: SumOut
 

    Node Activation { ALL 0.01 }
  }
 
set(EV1h,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(IV1h,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EV1v,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(IV1v,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EV4c,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }

  }
 
set(IV4c,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EV4h,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }

  }
 
set(IV4h,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EV4v,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }

  }
 
set(IV4v,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ExSs,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.5 }
  }
 
set(InSs,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ExFs,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(InFs,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EFD1,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(IFD1,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EFD2,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(IFD2,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ExFR,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(InFR,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(AttV,1)
  {
    Write -1
    ActRule: Clamp
    OutputRule: SumOut
 

    Node Activation { ALL 1.0 }
  }
% used for cases when both hemispheres are working
%
% left side, receiving input from GGNS instead of LGNS, note that GGNS is
% the last unit in this list, so it will appear as the last column 
% in spec_pet.m. Please keep this order in mind when you calulate sumsynact
%
% The reason GGNS is kept as the last unit is that it is easier to delete just
% the last unit in this file if we run a case where left brain receives the
% same input as the right brain -- i.e.  LGN input, where LGNS
% is already listed in weight/right.s
%
%

set(gats,1)
  {
    Write -1
    ActRule: Clamp
    OutputRule: SumOut
  }
 
	 
set(eg1h,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ig1h,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(eg1v,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ig1v,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(eg4c,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }

  }
 
set(ig4c,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(eg4h,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }

  }
 
set(ig4h,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(eg4v,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }

  }
 
set(ig4v,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(exgt,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.5 }
  }
 
set(ingt,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(egfs,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(igfs,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(egd1,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(igd1,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(egd2,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(igd2,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(egfr,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 9.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(igfr,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20.0 ) (NOISE 0.05)}
    Node Activation { ALL 0.2 }
  }

set(GGNs,81)
  {
    Write 5
    Topology: Rect(9,9)
    ActRule: Noisy Clamp
    OutputRule: SumOut
    Parameters: {(NOISE 0.05)}

    Node Activation { ALL 0.01 }
  }
#include /home/bhguest/brent/visual/weights/right/rightlist.txt
#include /home/bhguest/brent/visual/weights/left/leftlist.txtn
#include /home/bhguest/brent/visual/weights/cross/crosslist.txt
#include /home/bhguest/brent/visual/inputs/pethi2.rsb
