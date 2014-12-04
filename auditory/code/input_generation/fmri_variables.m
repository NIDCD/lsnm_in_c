%%Currently supports 1-99 subjects, attention levels and trials


clear all
%cd /home/deckerp/software/lsnm/pearce_test/auditory/batchrlc_output

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Variables%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Step = .02;%Timestep to seconds conversion factor

%MRI parameters
Ti = .1;%Number of seconds per scan
Tr = 1;
delay = 0;
lambda = 6;
save scanparam Ti Tr delay lambda;
WAPET = Ti/Step; %This is for fMRI, for which the +/- values have already absolute summed
%WPET = (2*Ti)/Step; %This is for MEG, because MEG output is twice as big
%since it has + and - values. In this case, it doesn't really make sense to
%calculate it, since Ti is a fMRI variable

%in mkbatchrlc_au.in
batch_name = 'mkbatchrlc_au';
batch_path = strcat('../code/',batch_name,'.in');
batch_file = fopen(batch_path);
batch_text = textscan(batch_file,'%s','delimiter','\n');
input_line = strsplit(batch_text{1}{3},'\t');
ns = str2double(input_line{1}); % # subjects
nt = str2double(input_line{2}); % # trials - Note that fmrigen_2 breaks if you have only 1 trial. This is likely because it removes the first trial from the scan
b_start = str2double(input_line{3});
b_end = str2double(input_line{4});
b_step = str2double(input_line{5});
if b_step ~= 0
    nb = (b_end-b_start)/b_step; % # blocks(attention levels)
else
    nb = 0;
end

%in auseq*.rsb - these are the length of each section of your trial in
%timeteps. i.e. if Tr1 consists of a single bothtc*.inp file, which uses 10
%Run 5 statements, the value here would be 50.
Tr0 = 50;
Tr1 = 70;
Tr2 = 100;
Tr3 = 70;
Tr4 = 250;
%will normally be 0 -- if not will probably be located at start of first
%auseq*.rsb and end of last auseq*.rsb
Tb1 = 0;
Tb3 = 0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%Calc Task%%%
T0 = Tr0 * Step;
T1 = Tr1 * Step;
T2 = Tr2 * Step;
T3 = Tr3 * Step;
T4 = Tr4 * Step;
Ttrial = T0+T1+T2+T3+T4;
Tb2 = Ttrial * nt;WPET = (2*Ti)/Step;
Tblock = Tb1+Tb2+Tb3;
T = Tblock *nb;
save task nb nt T0 T1 T2 T3 T4 Ttrial Tb1 Tb2 Tb3 Tblock T;
%%%Calc Triallist%%%
for i = 1:nt
    if i <10
        triallist(i,:) = ['trial',num2str(i),' '];
    else
        triallist(i,:) = ['trial',num2str(i)];
    end
end
save triallist triallist;
%%%Calc Attn%%%
b_num = b_start;
for i = 1:nb
    if b_num < 10
        attnlist(i,:) = ['b0',num2str(b_num)];
    else
        attnlist(i,:) = ['b',num2str(b_num)];
    end
    b_num = b_num+b_step;
end
save attnlist attnlist;
%%Calc Subj%%%
for i = 1:ns
    if i < 10
        subjectlist(i,:) = ['subj',num2str(i),' '];
    else
        subjectlist(i,:) = ['subj',num2str(i)];
    end
end
save subjectlist subjectlist;
%%%Calc WPET%%%
fprintf('\nYou should use a WAPET of [%s]!!\n', num2str(WAPET))
%fprintf('\nYou should use a WPET of [%s]!!\n', num2str(WPET))
