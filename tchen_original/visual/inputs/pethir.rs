%  WM Task with 1-second delay

WAPet 10		% Write PET every 10 iterations and reset

Randseed  1000	%seed for random number generator

#include /home/bhguest/brent/visual/sfiles/loattn_r.s
Run 100		% 100 ticks without input

% *************************************************************
%  STIMULUS # 1
% *********************


#include /home/bhguest/brent/visual/sfiles/hiattn_r.s	 % High Attention

#include /home/bhguest/brent/visual/inputs/input1.inp 	 %  Input ON
Run 200					 %  200=1sec.
#include /home/bhguest/brent/visual/inputs/noinp.lgn  	 %  Input OFF
Run 200					 %  Delay	
#include /home/bhguest/brent/visual/inputs/input1.inp 	 %  Input ON-match
Run 200
#include /home/bhguest/brent/visual/inputs/noinp.lgn  	 %  Input OFF
#include /home/bhguest/brent/visual/sfiles/loattn_r.s
Run 100

% ********************   INTERTRIAL INTERVAL


#include /home/bhguest/brent/visual/sfiles/reset_r.s    % Input OFF and reset delay units
Run 100


% *************************************************************
%  STIMULUS # 2
% *********************


#include /home/bhguest/brent/visual/sfiles/hiattn_r.s	% High Attention

#include /home/bhguest/brent/visual/inputs/input2.inp 	 %  Input ON
Run 200					 %  200=1sec.
#include /home/bhguest/brent/visual/inputs/noinp.lgn  	 %  Input OFF
Run 200					 %  Delay	
#include /home/bhguest/brent/visual/inputs/input1.inp 	 %  Input ON-match
Run 200
#include /home/bhguest/brent/visual/inputs/noinp.lgn  	 %  Input OFF
#include /home/bhguest/brent/visual/sfiles/loattn_r.s
Run 100

% ********************   INTERTRIAL INTERVAL


#include /home/bhguest/brent/visual/sfiles/reset_r.s    % Input OFF and reset delay units
Run 100


% *************************************************************
%  STIMULUS # 3
% *********************


#include /home/bhguest/brent/visual/sfiles/hiattn_r.s	% High Attention

#include /home/bhguest/brent/visual/inputs/input3.inp 	 %  Input ON
Run 200					 %  200=1sec.
#include /home/bhguest/brent/visual/inputs/noinp.lgn  	 %  Input OFF
Run 200					 %  Delay	
#include /home/bhguest/brent/visual/inputs/input3.inp 	 %  Input ON-match
Run 200
#include /home/bhguest/brent/visual/inputs/noinp.lgn  	 %  Input OFF
#include /home/bhguest/brent/visual/sfiles/loattn_r.s
Run 100

% ********************   INTERTRIAL INTERVAL


#include /home/bhguest/brent/visual/sfiles/reset_r.s    % Input OFF and reset delay units
Run 100


