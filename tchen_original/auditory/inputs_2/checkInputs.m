function checkInputs(filename)
%Read the input files and figure out the structur of the input
% ONLY FOR THE AUDITORY INPUTS
% Saves the output as mat file with the filename.mat
%  Mat
%  Mat file contains
%                 1. mgnId -> struct with values of node each set MGNs in .inp
%                 2. gmgnId -> struct with values of node each set GMGN in .inp file
%                 3 runVals -> array with each value of Run * instruction
%   Example:  mgnId(1).node(:) will give the nodes stimulated with the
%  first set MGNs command in the .inp files and so on
%

%%
expr1 ='(?<!.*[\#%].*)(MGNs)'; %MGNs not preceded by # or %
expr2 ='(?<!.*[\#%].*)(GMGN)'; % GMGN not preceded # or %
expr3 = '(?<=Node.*activation.*\{.*\(.*\[.*\d,)(\d*)'; % two numbers preceded by "Node activation { ([*, "
expr4 ='(?<!.*[\#%].*)(?<=Run.*)(\d*)'; % get the Run valuues
% expr2 =

% Bunch of variables to keep track and initialize stuff. Probably
% excessive. Whittle down when time permits.

Nmgn = 0;
Ngmgn = 0;
fid = fopen(filename,'r');

tline = 'string';

mgnFlag = 0; gmgnFlag = 0; % Flags
ii =0; jj = 0; kk  = 0; rr = 0; % Various indices
mgns = {}; gmgn = {}; % strings to store matches
nodeStr = {}; runStr2 = {}; % strings to store matches
mgnId = struct('node',[]); % struct to store node ids
gmgnId = struct('node',[]); % struct to store node ids
runVals = [];
while (ischar(tline))
    tline =    fgetl(fid);
    %     if ~ischar(tline),   break,   end
    %     disp([tline '\n'])
    if ischar(tline)
        ii = ii + 1;
        % Make sure the sub-indices of the nodes struct are reinitizialized
        % for each GMGN/MGNs
        jj = mgnFlag*jj;
        kk = gmgnFlag * kk;
        %  Test for MGNs string
        [mgns s e] = regexp(tline,expr1,'match');
        % Test for GMGN string
        [gmgn s2 e2] = regexp(tline,expr2, 'match');
        %  Match for numbers following the Node activation...
        [nodeStr s2 e2] = regexp(tline,expr3,'match');
        
        %    Match for the Run * values
        [runStr s2 e2] = regexp(tline,expr4,'match');
        %  If MGNs was found set MGN flag to 1 and GMGN flag to 0 and continue reading file
        if(~isempty(mgns) && strcmp(mgns{:},'MGNs')),
            mgnFlag = 1; gmgnFlag = 0;
            Nmgn = Nmgn + 1;
        end
        %  If GMGN was found set MGN flag to 0 and GMGN flag to 1 and continue reading file
        if(~isempty(gmgn) && strcmp(gmgn{:},'GMGN')),
            mgnFlag = 0; gmgnFlag = 1;
            Ngmgn = Ngmgn + 1;

        end
        %  For numbers following 'MGNs' line store
        if (mgnFlag & ~isempty(nodeStr))
            jj = jj + 1; ind =1 ;
            for ndind = jj:jj+length(nodeStr)-1
                mgnId(Nmgn).node(ndind) = str2double(nodeStr{ind});
                ind = ind + 1;
            end
            jj = jj+length(nodeStr)-1;
        end
        % For numbers following GMGN line store
        if (gmgnFlag & ~isempty(nodeStr))
            kk = kk + 1;    ind = 1;
            for ndind = kk:kk+length(nodeStr)-1
                gmgnId(Ngmgn).node(ndind) = str2double(nodeStr{ind});
                ind = ind + 1;
            end
            kk = kk+length(nodeStr)-1;
        end
        if(~isempty(runStr))
            rr = rr + 1;
            runVals(rr) = str2double(runStr{:});
        end
    end
    %     pause
end
fclose(fid);

%%
svname = strrep(filename,'.inp','')

save([svname '.mat'],'mgnId','gmgnId','runVals','-v6','-mat')


