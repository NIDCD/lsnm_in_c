

load subjectlist
workdir=pwd;

[nr,nc]=size(subjectlist);

for i=1:nr
  eval(['cd ',subjectlist(i,:)]);
  eval(['! mv fmritask.mat fmritask2.mat']);
  eval(['! mv fmrictrl.mat fmrictrl2.mat']);
  eval(['! mv correl.mat correl2.mat']);
  eval(['cd ',workdir]);
end


