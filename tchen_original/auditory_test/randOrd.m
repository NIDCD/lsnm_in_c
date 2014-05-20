function trialOrd=randOrd(Ntrial,Nmatch);

flag=1;
while flag
    trialOrd=round(abs(randn(Ntrial,1)));
    NN=find(trialOrd==0);
    if length(NN)==Nmatch
        flag=0;
        break
    end
end