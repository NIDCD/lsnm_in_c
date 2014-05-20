% Reset all delay units to low activation


Set(EFD1,81) {
 Node activation { ALL 0.2 }
}
Set(EFD2,81) {
 Node activation { ALL 0.2 }
}


set (MGNs, 81)          % Turn OFF LGN, the Input
{
  Node activation {ALL 0.05 }
}

set(GMGN,81)
{
  Node activation { ALL 0.00 }
}
