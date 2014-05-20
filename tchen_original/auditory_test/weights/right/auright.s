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
 
    Parameters: {(THRESH  0.3 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 8.5 ) (NOISE  0.2)}
    Node Activation { ALL 0.2 }
  }
 
set(ICtl,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 19 ) (NOISE  0.2)}
    Node Activation { ALL 0.2 }
  }
 
set(MGNs,81)
  {
    Write 1
    Topology: Rect(1,81)
%   ActRule: ShifAct
%   OutputRule: SumOut
     ActRule: Clamp
     OutputRule: SumOut

%    Parameters: {(DELTA  5 ) (DX  1 )}
%    Parameters: {(DELTA  5 ) (DX  2 )} 
    Node Activation { ALL 0.01 }
  }
 
set(EA1d,81)
  {
    Write 1
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut

  Parameters: {(THRESH  0.3 ) (DELTA .7) (DECAY .7) (K 8 ) (NOISE  0.05)}  
  
  Node Activation { ALL 0.05 }
  }
 
set(IA1d,81)
  {
    Write 0
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
	
  Parameters: {(THRESH  0.2 ) (DELTA  2 ) (DECAY 1) (K 17 ) (NOISE  0.05)}
	
    Node Activation { ALL 0.05 }
  }

set(EA1u,81)
  {
    Write 1
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut

    Parameters: {(THRESH  0.3 ) (DELTA .7) (DECAY .7 ) (K 8 ) (NOISE  0.05)} 
    Node Activation { ALL 0.05 }
  }
 
set(IA1u,81)
  {
    Write 0
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut

    Parameters: {(THRESH  0.2 ) (DELTA  2  ) (DECAY 1 ) (K 17 ) (NOISE  0.05)}
    Node Activation { ALL 0.05 }
  }

% set(EA1PT,81)
% {
%    Write 1
%    Topology: Rect(1,81)
%    ActRule: DiffSig
%    OutputRule: SumOut
%
%  Parameters: {(THRESH  0.3 ) (DELTA .7) (DECAY .7) (K 8 ) (NOISE  0.05)}  
%  
%  Node Activation { ALL 0.05 }
%  }
 
% set(IA1PT,81)
%  {
%    Write 0
%    Topology: Rect(1,81)
%    ActRule: DiffSig
%    OutputRule: SumOut
%	
%  Parameters: {(THRESH  0.2 ) (DELTA  2 ) (DECAY 1) (K 17 ) (NOISE  0.05)}
%	
%    Node Activation { ALL 0.05 }
%  }
	
set(EA2d,81)
  {
    Write 1
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
	
    Parameters: {(THRESH  0.35 ) (DELTA  1.7) (DECAY  1.7 ) (K 9 ) (NOISE  0.10)}
    Node Activation { ALL 0.1 }

  }
 
set(IA2d,81)
  {
    Write 0
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
	
    Parameters: {(THRESH  0.35 ) (DELTA  .2 ) (DECAY  1.6 ) (K 18 ) (NOISE  0.1)}
    Node Activation { ALL 0.1 }
  }
	 
set(EA2u,81)
  {
    Write 1
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.35 ) (DELTA 1.7  ) (DECAY  1.7 ) (K 9 ) (NOISE  0.10)}
    Node Activation { ALL 0.1 }

  }
 
set(IA2u,81)
  {
    Write 0
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.35 ) (DELTA  .2 ) (DECAY  1.6 ) (K 18 ) (NOISE  0.1)}
    Node Activation { ALL 0.1 }
  }
 

set(EA2c,81)
  {
    Write 1
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
 
 Parameters: {(THRESH  0.34 ) (DELTA  1.3 ) (DECAY  1.3 ) (K 8 ) (NOISE  0.10)}
%    Parameters: {(THRESH  0.35 ) (DELTA  0.6 ) (DECAY  0.6 ) (K 8.5 ) (NOISE  0.10)}
    Node Activation { ALL 0.1 }

  }
 
set(IA2c,81)
  {
    Write 0
    Topology: Rect(1,81)
    ActRule: DiffSig
    OutputRule: SumOut
Parameters: {(THRESH  0.3 ) (DELTA  .2 ) (DECAY  .8 ) (K 17 ) (NOISE  0.1)} 
%    Parameters: {(THRESH  0.2 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 17 ) (NOISE  0.1)}
    Node Activation { ALL 0.1 }
  }
	  
set(ESTG,81)
  {
    Write 1
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.35) (DELTA  .8 ) (DECAY  1.2 ) (K 7.5 ) (NOISE  0.05)}
    Node Activation { ALL 0.1 }
  }
 
set(ISTG,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3  ) (DELTA  1 ) (DECAY  1 ) (K 19 ) (NOISE  .1)}
%    Parameters: {(THRESH  0.2 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 19 ) (NOISE  0.1)}
    Node Activation { ALL 0.1 }
  }
 
set(ExFs,81)
  {
    Write 1
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
	
    Parameters: {(THRESH  0.3) (DELTA  .5 ) (DECAY  .5 ) (K 9 ) (NOISE  0.05)}
 
%    Parameters: {(THRESH  0.3 ) (DELTA  1.0 ) (DECAY  1.0 ) (K 8.5 ) (NOISE  0.13)}
    Node Activation { ALL 0.2 }
  }
 
set(InFs,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
	
    Parameters: {(THRESH  0.1  ) (DELTA  .5 ) (DECAY  .5 ) (K 20 ) (NOISE  0.05)}
 
%    Parameters: {(THRESH  0.1 ) (DELTA  0.5 ) (DECAY  0.5 ) (K 19 ) (NOISE  0.13)}
    Node Activation { ALL 0.2 }
  }
 
set(EFD1,81)
  {
    Write 1
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3) (DELTA  0.5 ) (DECAY  0.5 ) (K 9 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(IFD1,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1  ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(EFD2,81)
  {
    Write 1
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3) (DELTA  0.5 ) (DECAY  0.5 ) (K 9 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(IFD2,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1  ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ExFR,81)
  {
    Write 1
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3) (DELTA  .89 ) (DECAY  1 ) (K 9 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(InFR,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1  ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20 ) (NOISE  0.05)}
    Node Activation { ALL 0.2}
  }
 
set(AttV,1)
  {
    Write -1 
    ActRule: Clamp
    OutputRule: SumOut
 

    Node Activation { ALL 1.0 }
  }

set(ETED,81)
  {
    Write 1
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.3) (DELTA  0.5 ) (DECAY  0.5 ) (K 9 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 
set(ITED,81)
  {
    Write 0
    Topology: Rect(9,9)
    ActRule: DiffSig
    OutputRule: SumOut
 
    Parameters: {(THRESH  0.1  ) (DELTA  0.5 ) (DECAY  0.5 ) (K 20 ) (NOISE  0.05)}
    Node Activation { ALL 0.2 }
  }
 



