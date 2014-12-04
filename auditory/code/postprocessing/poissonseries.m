%  poissonseries.m
%
%  Format:  h1=poissonseries(T,lambda)
%
%         where h1 is the output Poissonseries
%               T is the entire time interval for the series
%               lambda is the Poisson time constant
%
%  Calls:  poissondbn.m
%
%  Written:  Jan, 1998 by B. Horwitz

function h1=poissonseries(T,lambda)

TP=round(T);

h1=[];

for t=0:TP
  h1=[h1; poissondbn(lambda,t)];
end





