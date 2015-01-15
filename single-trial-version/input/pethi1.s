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

#include ../weights/rightlist.txt
#include pethi1.rsb
