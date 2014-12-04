%  factorial.m
%
%  Format:  f=factorial(n)
%
%  Would you believe factorial n?
%  n - vector
%
%  Written by SPM group

function f=factorial(n)

f=cumprod(1:max(n));
f=f(n);

