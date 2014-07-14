%  convol.m  Jan 1998
%
%  FORMAT:  activity=convol(infunct,lambda,Ti,T)
%_________________________________________________
%
%  This function convolves the hemodynamic delay (represented
%  by the parameter lambda) with any function (infunct) assoicated with
%  the time interval of the simulated experiment, represented by
%  Ti and T.
%
%  	Ti=time interval over which synaptic activity was integrated
%
%	T=total time interval of entire data set
%
%  It is assumed that the input function starts at zero time.  If
%  infunct has more than one column, it is assumed that the first
%  column is the time in units of Ti.
%
%  Calls:  poissonseries.m

%  Written:  1-98 by B. Horwitz


function activity=convol(infunct,lambda,Ti,T);

[r,c]=size(infunct);

if c==1
  infunct=[(0:Ti:T)' infunct];
end

[r c]=size(infunct);

ntp=length(infunct(:,1));

h=poissonseries(T,lambda);
n=length(h);

nn=round(ntp/n)+1;
h1=abs(interp(h,nn));
h2=h1(1:ntp);
h3=[infunct(:,1),h2];

for i=1:c-1
  act(:,i)=conv(infunct(:,i+1),h2);
  activity(:,i)=act(1:ntp,i);
end

activity=[infunct(:,1) activity];



