% image_to_stim.m
% Version 2.1
% Written by Pearce Decker
% April 4 2014

%__________________________________________________________________________

% This program is intended to be used to generate stimuli for the auditory
% model. In future it should be implemented in a "seq_gen_au" type file
% that creates a paired associate trial sequence. The current version takes
% the name of the file to be created, the matrix of the stimulus, with rows
% representing frequencies and columns representing time_steps of size
% run_unit which is currently the third and final input.

% Initial design will aim to create stimulus files that look like those
% used most recently by Ted Chen. Here is an example of a single segment of
% an auditory stimulus file:
% 
% % set (MGNs, 81)
% % {
% %    Node activation {ALL 0.0}
% %    Node activation {([1,42] 1.00)([1,43] 1.00)}
% % }
% % set (GMGN, 81)
% % {
% %    Node activation {ALL 0.0}
% %    Node activation {([1,17] 0.75)([1,18] 0.75)}
% % }
% % 
% % Run 5
% Note that neither stim_to_image.m nor the simulation itself cares whether
% the individual Node activations are on one line (as done here) or on
% separate lines. Older versions of inputs used both, but this implements a
% 1 line standard for simplicity and to shorten files.

% 2.0: provisional randomization of the GMGN was removed and
% turned into its own image generator called make_rand_clusters.m. As such
% a new input GMGN_mat was added and the old input stim_mat was changed to
% MGN_mat.
% 2.1: added variable 'num_freqs', which represents the total number of
% frequencies possible (i.e. the number of freq selective populations of
% "neurons). Subsequently this was changed from 100 to 81, to reflect the
% fact that the current version of the model uses 81.
% Future changes may include: taking the name with full directory
% preceding as input. This obviously makes the function transfer to
% different people/directory systems s/t no one has to alter the code.

% INPUTS: 
%   name - name of the file to which the stimulus text will be output
%   MGN_mat - the frequency by time matrix of the stimulus for the specific 
% (MGN) neurons. Rows represent frequency populations from 1-81 and 
% columns represent time. The time dimension is not bounded. Currently 
% using make_up_tc.m (or down) is the standard method since standard input 
% for the model has been tonal contours. See below for an example. 
% However, anything that is in time-steps and 1-100 frequencies should work
% fine. Pure tones can be % generated using make_tone.m.
%   GMGN_mat - same as MGN_mat but for the non-specific neurons (GMGN).
% Standard is to use make_rand_clusters to create this. See below for an
% example.
%   run_unit - this is the "Run x" value that will follow each activation
% in the text stimulus. This number essentially determines the number of
% timesteps for which each activation will run.

%NOTES: (A) This version will accept stimuli of any length with any cell values as
%long as there are exactly 81 input frequencies. Therefore the
%MGN_mat and GMGN_mat should have exactly 81 rows.
%
%(B) Currently, this version does not insert a switch to low attention just
%prior to the tone component of the tc. Not sure why that is done and
%will implement if necessary.

%The standard method for using this function:

%    %%Make MGN_mat%%%
%    start_freq = 25;
%    tone_freq = 30;
%    end_freq = 25;
%    buffers = [2,2,2];
%    tone_len = 5;
%    freqs = [start_freq,tone_freq,end_freq];
%    MGN_mat = make_up_tc(freqs,buffers,tone_len);
%    %%Make GMGN_mat%%%
%    c_num = [1,2];
%    c_size = [2,4];
%    c_val = [.65,.85];
%    len = 10;
%    GMGN_mat = make_rand_clusters(c_num,c_size,c_val,len);
%    %%%Create Stimulus%%%
%    name = 'test_au_stim1.inp';
%    run_unit = 5;
%    image_to_stim(name,MGN_mat,GMGN_mat,run_unit);

%__________________________________________________________________________

function image_to_stim(name,MGN_mat,GMGN_mat,run_unit)

    %%Starting/Input Variables%%
    %Might be best to make this pwd and simply require user to use this
    %from the /inputs directory
    base_path = '/home/deckerp/software/lsnm/pearce_test/auditory/inputs/';
    path = strcat(base_path,name);
    num_freqs = 81;
    
    %If stim_path already exists this will overwrite it
    file = fopen(path,'wt');
    steps = size(MGN_mat,2);
    for i = 1:steps
        %MGN Activation
        fprintf(file,'set (MGNs, 81)\n{\n\tNode activation {ALL 0.0}\n');
        fprintf(file,'\tNode activation {');
        for j = 1:num_freqs
            if MGN_mat(j,i) > 0
                fprintf(file,'([1,%2.0f] %1.2f)',j,MGN_mat(j,i));
            end
        end
        fprintf(file,'}\n}\n');
        %GMGN Activation
        fprintf(file,'set (GMGN, 81)\n{\n\tNode activation {ALL 0.0}\n');
        fprintf(file,'\tNode activation {');
        for j = 1:num_freqs
            if GMGN_mat(j,i) > 0
                fprintf(file,'([1,%2.0f] %1.2f)',j,GMGN_mat(j,i));
            end
        end
        fprintf(file,'}\n}\n');
        %Run Statement
        fprintf(file,'Run %2.0f\n',run_unit);
        %fprintf(file,'}\n\nRun %1.0f\n\n%-------------------------------------/n',run_unit);
    end
    fclose(file);
end