%%Write up documentation
function [M_outmat,G_outmat] = stim_to_image(name,time_points)
    base_path = '/home/deckerp/software/lsnm/pearce_test/auditory/inputs/';
    path = strcat(base_path,name);
    num_freqs = 81;
    file = fopen(path);
    MGN_header = 'set(MGNs,81)';
    GMGN_header = 'set(GMGN,81)';
    MGN_length = size(MGN_header,2);
    GMGN_length = size(GMGN_header,2);
    starter = 'Nodeactivation{([1,';
    starter_length = size(starter,2);
    current_line = fgets(file);
    M_outmat = zeros(num_freqs,time_points);
    G_outmat = zeros(num_freqs,time_points);
    mi = 1;
    gi = 1;
    while current_line ~= -1
        current_line = current_line(~isspace(current_line));
        if strncmpi(current_line, MGN_header, MGN_length)
            while strncmp(current_line, '}', 1) == 0
                if strncmpi(current_line, starter, starter_length)
                    activations = regexpi(current_line,'\(\[1,(\d+)\](1|0\.\d{2})','tokens');
                    for j = 1:size(activations,2)
                        frequency = str2double(activations{j}{1});
                        value = str2double(activations{j}{2});
                        M_outmat(frequency,mi) = value;
                    end
                end
                current_line = fgets(file);
                current_line = current_line(~isspace(current_line));
            end
            mi = mi+1;
        end
        if strncmpi(current_line, GMGN_header, GMGN_length)
            while strncmp(current_line, '}', 1) == 0
                if strncmpi(current_line, starter, starter_length)
                    activations = regexpi(current_line,'\(\[1,(\d+)\](1|0\.\d{2})','tokens');
                    for j = 1:size(activations,2)
                        frequency = str2double(activations{j}{1});
                        value = str2double(activations{j}{2});
                        G_outmat(frequency,gi) = value;
                    end
                end
                current_line = fgets(file);
                current_line = current_line(~isspace(current_line));
            end
            gi = gi+1;
        end
        current_line = fgets(file);
    end
    fclose(file);
end
%name = 'gtc2_ctrltask4.inp';
%time_points = 10;