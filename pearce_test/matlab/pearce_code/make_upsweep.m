%start_freq must be between 1 and 100
%buffer should not cause line to go outside this range
%len determines the end point of the sweep
function up_sweep = make_upsweep(start_freq, len, buffer)
    sweep = zeros(100, len);
    buffer_low = start_freq-round(buffer/2);
    buffer_high = start_freq+floor(buffer/2);
    for i = 1:len
        if buffer_high < 100
            sweep(buffer_low:buffer_high, i) = 1;
        else
            sweep(buffer_low:100, i) = 1;
        end
        buffer_low = buffer_low + 1;
        buffer_high = buffer_high + 1;
    end
    up_sweep = sweep;
end