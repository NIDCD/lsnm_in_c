

load('allactivity.mat');

area_name={'Ai', 'Aii', 'ST', 'PFs', 'PFD1', 'PFD2', 'PFR'};
cutoff_freq=20; 
trial_length=750;%2000;
inter_trial=[2.5 3.75];%[4.5 10];
silent_time=0.5;%0.5;
signal_length=400;%1000;
t_signal=(1:length(allsynact))*5/1000;
t_trial=(1:trial_length)*5/1000;
t_signal=(1:signal_length)*5/1000;
signal_index=(1:signal_length)+silent_time*1000/5;


figure;title('origninal simulation');
for i=1:size(allsynact,2)
subplot(size(allsynact,2),1,i);
plot(allsynact(:,i));
 if i<size(allsynact,2)
    axis off;
 end;
 title(area_name(i));
end;

new_fs=1000/5;

b = fir1(5,cutoff_freq/new_fs*2);
for i=1:size(allsynact,2)
allsynact_new(:,i)=filtfilt(b,1,allsynact(:,i));
end;

% figure;title('filtered simulation');
% for i=1:size(allsynact_new,2)
% subplot(size(allsynact_new,2),1,i);
% plot(t,allsynact_new(:,i));
%  if i<size(allsynact,2)
%     axis off;
%  end;
%  title(area_name(i));
% end;


A1_activity=allsynact_new(:,1);
A2_activity=allsynact_new(:,2);
ST_activity=allsynact_new(:,3);
frontal_activity=sum(allsynact_new(:,5:6),2);

%%%%%%%%%%%%%%%%%%%%%%%%%%%
% aud_activity=sum(allsynact_new(:,1:2),2);
% frontal_activity=sum(allsynact_new(:,5:6),2);
% figure;
% subplot(2,1,1);
% plot(t,aud_activity);title('auditory-alltrials');
% subplot(2,1,2);
% plot(t,frontal_activity);title('frontal-alltrials');

all_A1_activity=reshape(A1_activity,trial_length,length(A1_activity)/trial_length);
all_A2_activity=reshape(A2_activity,trial_length,length(A2_activity)/trial_length);
all_ST_activity=reshape(ST_activity,trial_length,length(ST_activity)/trial_length);
all_fro_activity=reshape(frontal_activity,trial_length,length(frontal_activity)/trial_length);

avg_A1=mean(all_A1_activity,2);
avg_A2=mean(all_A2_activity,2);
avg_ST=mean(all_ST_activity,2);
avg_fro=mean(all_fro_activity,2);

filtered_avg_A1=filtfilt(b,1,avg_A1);
filtered_avg_A2=filtfilt(b,1,avg_A2);
filtered_avg_ST=filtfilt(b,1,avg_ST);
filtered_avg_fro=filtfilt(b,1,avg_fro);
filtered_avg_AUD=filtered_avg_A1+filtered_avg_A2;%+filtered_avg_ST;

avg_A1_signal=filtered_avg_A1(signal_index);
avg_A2_signal=filtered_avg_A2(signal_index);
avg_ST_signal=filtered_avg_ST(signal_index);
avg_fro_signal=filtered_avg_fro(signal_index);
avg_AUD_signal=filtered_avg_AUD(signal_index);


figure;
subplot(5,1,1);
plot(t_signal,avg_A1_signal);title('A1');
subplot(5,1,2);
plot(t_signal,avg_A2_signal);title('A2');
subplot(5,1,3);
plot(t_signal,avg_ST_signal);title('ST');
subplot(5,1,4);
plot(t_signal,avg_fro_signal);title('frontal');
subplot(5,1,5);
plot(t_signal,avg_AUD_signal);title('auditory');

baseline_aud=[filtered_avg_AUD(inter_trial(1)*1000/5+1:inter_trial(2)*1000/5);filtered_avg_AUD(1:silent_time*1000/5)];
baseline_fro=[filtered_avg_fro(inter_trial(1)*1000/5+1:inter_trial(2)*1000/5);filtered_avg_fro(1:silent_time*1000/5)];
avg_baseline_aud=mean(baseline_aud);
avg_baseline_fro=mean(baseline_fro);
% 
% baseline_A1=mean(avg_A1_signal);
% baseline_A2=mean(avg_A2_signal);
% baseline_ST=mean(avg_ST_signal);
%baseline_fro=mean(avg_fro_signal);
%baseline_aud=mean(avg_AUD_signal);

%%baseline correction
new_avg_aud=avg_AUD_signal-repmat(avg_baseline_aud,length(avg_AUD_signal),1);
new_avg_fro=avg_fro_signal-repmat(avg_baseline_fro,length(avg_fro_signal),1);
%%make the time series always above zero
new_avg_aud=new_avg_aud-repmat(min(new_avg_aud),length(new_avg_aud),1);
new_avg_fro=new_avg_fro-repmat(min(new_avg_fro),length(new_avg_fro),1);

% 
figure;
subplot(2,1,1);
plot(t_signal,new_avg_aud);title('auditory-averge-baselinecorrected');
subplot(2,1,2);
plot(t_signal,new_avg_fro);title('frontal-averge-baselinecorrected');


weight=0:0.1:0.9;
for i=1:length(weight)
signal_combined(:,i)=new_avg_aud*weight(i)+new_avg_fro*(1-weight(i));
end;
figure;
for i=1:length(weight)
    subplot(5,2,i);plot(t_signal,signal_combined(:,i));title(strcat('aud: ',num2str(weight(i)),' fro: ',num2str(1-weight(i))));
end;

