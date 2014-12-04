%  PETcorr.m

load subjectlist
[nsub nscols]=size(subjectlist);
workdir=pwd;

relpettask=[];
relpetctrl=[];
pet_task=[];
pet_ctrl=[];

for iis=1:nsub
  eval(['cd ',subjectlist(iis,:)]);
  load fmritask
  taskdata=fmridata(:,2:end);
  taskpet=sum(taskdata);
  pet_task=[pet_task;taskpet];
  globaltask=mean(taskpet);
  relpettask=[relpettask; taskpet./globaltask];
  
  load fmrictrl
  ctrldata=fmridata(:,2:end);
  ctrlpet=sum(ctrldata);
  pet_ctrl=[pet_ctrl; ctrlpet];
  globalctrl=mean(ctrlpet);
  relpetctrl=[relpetctrl; ctrlpet./globalctrl];
  eval(['cd ',workdir]);
end

rtask=corrcoef(pet_task);
rctrl=corrcoef(pet_ctrl);
rPETtask=corrcoef(relpettask); 
rPETctrl=corrcoef(relpetctrl);

save corrPET rtask rctrl rPETtask rPETctrl
