% written 07/16/03 by B. Warner
% This reset file resets only the MGN, delay units, and STG
% in both hemispheres.
% It is comparable to the reset.s in the visual model and is
% different than resetall_au.s that resets every unit in the
% right hemisphere.

% input units
set(MGNs,81)
{
  Node activation { ALL 0.05 }
}
set(GMGN,81)
{
  Node activation { ALL 0.05 }
}

% delay units
set(EFD1,81)
{
  Node activation { ALL 0.2 }
}
set(EFD2,81)
{
  Node activation { ALL 0.2 }
}
set(EGD1,81)
{
  Node activation { ALL 0.2 }
}
set(EGD2,81)
{
  Node activation { ALL 0.2 }
}

% STG units
set(ESTG,81)
{
  Node activation { ALL 0.05 }
}
set(EGTG,81)
{
  Node activation { ALL 0.05 }
}
