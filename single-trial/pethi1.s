% ============================================================================
%
%                            PUBLIC DOMAIN NOTICE
%
%       National Institute on Deafness and Other Communication Disorders
%
% This software/database is a "United States Government Work" under the 
% terms of the United States Copyright Act. It was written as part of 
% the author's official duties as a United States Government employee and 
% thus cannot be copyrighted. This software/database is freely available 
% to the public for use. The NIDCD and the U.S. Government have not placed 
% any restriction on its use or reproduction. 
%
% Although all reasonable efforts have been taken to ensure the accuracy 
% and reliability of the software and data, the NIDCD and the U.S. Government 
% do not and cannot warrant the performance or results that may be obtained 
% by using this software or data. The NIDCD and the U.S. Government disclaim 
% all warranties, express or implied, including warranties of performance, 
% merchantability or fitness for any particular purpose.
%
% Please cite the author in any work or product based on this material.
% 
% ==========================================================================



% ***************************************************************************
%
%   Large-Scale Neural Modeling software (LSNM)
%
%   Section on Brain Imaging and Modeling
%   Voice, Speech and Language Branch
%   National Institute on Deafness and Other Communication Disorders
%   National Institutes of Health
%
%   This file (pethi1.s) was created around 1998.
%
%   pethi1.s acts as input file to an LSNM visual model simulation. it
%   contains a description of all brain regions to be simulated, its 	
%   parameters, as well as the location of a file with description of 
%   the connecting weights linking all those regions. pethi1.s also contains
%   the location of the experimental script to be used by the simulator
%	
%   Author: Malle Tagamets, circa 1998
%
%   Last updated by Antonio Ulloa on February 1 2015  
% **************************************************************************/


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
    Ww 5
    Topology: Rect(9,9)
    ActRule: DiffSig
    LearningRule: Efferent
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% The following brain areas are TVB brain brain nodes, which act as 'non-specific'
% neurons in an LSNM simulation
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Excitatory 'non-specific' V1
set(ENV1, 1)
  {
    Write 5
    Actrule: TVB
    OutputRule:	 SumOut
	
    Node Activation {All 0.3}
}

% Inhibitory 'non-specific' V1
set(INV1, 1)
  {
    Write 5
    Actrule: TVB
    OutputRule:	 SumOut

    Node Activation {All 0.3}	
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% The following line tells the simulator where to find list of connecting weights
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
#include weights/rightlist.txt

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% The following line tells the simulator where to find the experimental script
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include input/pethi1.rsb
