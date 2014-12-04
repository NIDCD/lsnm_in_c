workdir=pwd;

[nrowsp,ncolsp]=size(subjectlist);
[nrp,ncp]=size(attnlist);

for i=1:nrowsp
  eval(['cd ',subjectlist(i,:)]);
  cworkdir=pwd;
  for j=1:nrp
	eval(['cd ',attnlist(j,:)]);
  	load spec_pet;
	[x,y]=size(spec_pet);
	spec_pet=spec_pet(1:(x-20),:);
	save spec_pet spec_pet;
 	eval(['cd ',cworkdir]);
  end
  eval(['cd ',workdir]);	
end
