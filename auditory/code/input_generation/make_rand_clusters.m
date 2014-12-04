%Consider implementing rand_style (i.e. gaussian vs. flat)
% c_num = [1,2];
% c_size = [2,4];
% c_val = [.65,.85];
% len = 10;
function out_mat = make_rand_clusters(c_num,c_size,c_val,len)
    num_freqs = 81;
    num_min = c_num(1);
    num_max = c_num(2);
    size_min = c_size(1);
    size_max = c_size(2);
    val_min = 1000*c_val(1);
    val_max = 1000*c_val(2);
    out_mat = zeros(100, len);
    buff_low = 1 + (size_max);
    for time_step = 1:len
        current_num = randi([num_min,num_max],1);
        upper_freqs = randsample((buff_low:num_freqs),current_num);
        for cluster_step = 1:current_num
            current_size = randi([size_min,size_max],1);
            lower_freq = upper_freqs(cluster_step)-current_size+1;
            cluster_freqs = (lower_freq:upper_freqs(cluster_step));
            current_vals = (randi([val_min,val_max],1,current_size))/1000;
            out_mat(cluster_freqs,time_step) = current_vals;
        end
    end
end