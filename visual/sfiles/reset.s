
% Reset all delay units to low activation


Set(EFD1,81) {
 Node activation { ALL 0.2 }
}
Set(EFD2,81) {
 Node activation { ALL 0.2 }
}


set (LGNs, 81)          % Turn OFF LGN, the Input
{
  Node activation {ALL 0.05 }
}

Set(EXSS, 81)
{
  Node activation {ALL 0.05 }
}


% Reset all delay units to low activation

set (GGNs, 81)          % Turn OFF GGN, the Input
{
  Node activation {ALL 0.05 }
}

Set(EGD1,81) {
 Node activation { ALL 0.2 }
}
Set(EGD2,81) {
 Node activation { ALL 0.2 }
}

Set(EXGT,81)
{
  Node activation { ALL 0.05 }
}