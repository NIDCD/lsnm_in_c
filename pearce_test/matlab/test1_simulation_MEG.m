

load('allactivity.mat');

area_name={'Ai', 'Aii', 'ST', 'PFs', 'PFD1', 'PFD2', 'PFR'};
cutoff_freq=20; 
trial_length=2000;
inter_trial=[4.5 10];
silent_time=0.5;
t=(1:length(allsynact))*5/1000;
t_trial=(1:trial_length)*5/1000;


figure;title('origninal simulation');
for i=1:size(allsynact,2)
subplot(size(allsynact,2),1,i);
plot(t,allsynact(:,i));
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

figure;title('filtered simulation');
for i=1:size(allsynact_new,2)
subplot(size(allsynact_new,2),1,i);
plot(t,allsynact_new(:,i));
 if i<size(allsynact,2)
    axis off;
 end;
 title(area_name(i));
end;

aud_activity=sum(allsynact_new(:,1:3),2);
frontal_activity=sum(allsynact_new(:,4:7),2);
figure;
subplot(2,1,1);
plot(t,aud_activity);title('auditory-alltrials');
subplot(2,1,2);
plot(t,frontal_activity);title('frontal-alltrials');

all_aud_activity=reshape(aud_activity,trial_length,length(aud_activity)/trial_length);
all_fro_activity=reshape(frontal_activity,trial_length,length(frontal_activity)/trial_length);

avg_aud=mean(all_aud_activity,2);
avg_fro=mean(all_fro_activity,2);
figure;
subplot(2,1,1);
plot(t_trial,avg_aud);title('auditory-average');
subplot(2,1,2);
plot(t_trial,avg_fro);title('frontal-average');

baseline_aud=[avg_aud(inter_trial(1)*1000/5+1:inter_trial(2)*1000/5);avg_aud(1:silent_time*1000/5)];
baseline_fro=[avg_fro(inter_trial(1)*1000/5+1:inter_trial(2)*1000/5);avg_fro(1:silent_time*1000/5)];
avg_baseline_aud=mean(baseline_aud);
avg_baseline_fro=mean(baseline_fro);

new_avg_aud=avg_aud-repmat(avg_baseline_aud,length(avg_aud),1);
new_avg_fro=avg_fro-repmat(avg_baseline_fro,length(avg_fro),1);

figure;
subplot(2,1,1);
plot(t_trial,new_avg_aud);title('auditory-averge-baselinecorrected');
subplot(2,1,2);
plot(t_trial,new_avg_fro);title('frontal-averge-baselinecorrected');
