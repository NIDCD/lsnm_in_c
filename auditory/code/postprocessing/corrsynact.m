%  corrsynact.m
%
%  Format:  corrsynact
%
%  This program constructs the interregional correlations between the 
%  simulated synaptic activity(allsynact); it also does the same thing 
%  for the integrated activity (allintgract).  It produces both a standard
%  correlation matrix and a vector of correlation values in the order:
%
%  (r12 r13 r14 ... r23 r24 r25 ... etc)
%
%  Written:  2-00 by B. Horwitz
%  Modified: 3-03 by B. Horwitz

load allactivity

[ri,ci]=size(allintgract);
[r,c]=size(allsynact);

%  Eliminate the control column

allintgract=allintgract(:,2:ci);
allsynact=allsynact(:,2:c);
ncols=c-1;

%  Calculate the correlation matrix

r_intgract=corrcoef(allintgract);
r_synact=corrcoef(allsynact);

%  Convert correl. matrices in vectors, eliminating 
%  redundant and irrelavant elements.
%  The resulting vector will look like the column version
%  of:  (r12 r13 r14 ... r23 r24 r25 ... etc)

r1_intgract=tril(r_intgract);
r1_synact=tril(r_synact);

r2_intgract=r1_intgract - diag(diag(r1_intgract));
r2_synact=r1_synact - diag(diag(r1_synact));

rp_intgract=compress(r2_intgract(:));
rp_synact=compress(r2_synact(:));

indexmat=[];
for i=1:ncols
  for j=i+1:ncols
    indexmat=[indexmat; [i j]];
  end
end

rmat=[indexmat rp_synact rp_intgract];

save corrvalues rmat r_intgract r_synact rp_intgract rp_synact

