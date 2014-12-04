%  poisson.m
%
%  Format:  h=poisson(lambda,tau)
%
%        where h is the output Poisson function
%              lambda is the Poisson time constant
%              tau is the time step
%
%  Calls:  factorial.m
%
%  Written:  Jan, 1998 by B. Horwitz

function h=poisson(lambda,tau)

if tau~=0
  h=((lambda)^tau)*(exp(-lambda))/factorial(tau);
elseif tau==0
  h=((lambda)^tau)*(exp(-lambda));
end

