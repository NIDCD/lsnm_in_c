function down_sweep = make_downsweep(start_freq, len, buffer)
    sweep = zeros(100, len);
    buffer_low = start_freq-round(buffer/2);
    buffer_high = start_freq+floor(buffer/2);
    for i = 1:len
        if buffer_low > 1
            sweep(buffer_low:buffer_high, i) = 1;
        else
            sweep(1:buffer_high, i) = 1;
        end
        buffer_low = buffer_low - 1;
        buffer_high = buffer_high - 1;
    end
    down_sweep = sweep;
end