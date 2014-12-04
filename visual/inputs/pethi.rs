%  WM Task with 1-second delay

WAPet 10		% Write PET every 10 iterations and reset

Randseed  0	%seed for random number generator

Run 100		% 100 ticks without input

% *************************************************************
%  STIMULUS # 1
% *********************


#include sfiles/hiattn_r.s	% High Attention
#include inputs/input1.inp 	 %  Input ON
Run 200					 %  200=1sec.
#include inputs/noinp.lgn  	 %  Input OFF
Run 200					 %  Delay	
#include inputs/input1.inp 	 %  Input ON-match
Run 200
#include inputs/noinp.lgn  	 %  Input OFF
#include sfiles/loattn_r.s

Run 100

% ********************   INTERTRIAL INTERVAL


#include sfiles/reset_r.s    % Input OFF and reset delay units
Run 100


% *************************************************************
%  STIMULUS # 2
% *********************


#include sfiles/hiattn_r.s		% High Attention

#include inputs/input2.inp 	 %  Input ON
Run 200					 %  200=1sec.
#include inputs/noinp.lgn  	 %  Input OFF
Run 200					 %  Delay	
#include inputs/input1.inp 	 %  Input ON-match
Run 200
#include inputs/noinp.lgn  	 %  Input OFF
#include sfiles/loattn_r.s

Run 100

% ********************   INTERTRIAL INTERVAL


#include sfiles/reset_r.s    % Input OFF and reset delay units
Run 100


% *************************************************************
%  STIMULUS # 3
% *********************


#include sfiles/hiattn_r.s		% High Attention

#include inputs/input3.inp 	 %  Input ON
Run 200					 %  200=1sec.
#include inputs/noinp.lgn  	 %  Input OFF
Run 200					 %  Delay	
#include inputs/input3.inp 	 %  Input ON-match
Run 200
#include inputs/noinp.lgn  	 %  Input OFF
#include sfiles/loattn_r.s

Run 100

% ********************   INTERTRIAL INTERVAL


#include sfiles/reset_r.s    % Input OFF and reset delay units
Run 100








