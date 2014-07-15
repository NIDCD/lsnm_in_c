function tone = make_tone(central_freq, len, buffer)
    tone = zeros(100, len);
    buffer_low = central_freq-round(buffer/2);
    buffer_high = central_freq+floor(buffer/2);
    if buffer_high <= 100
        tone(buffer_low:buffer_high, :) = 1;
    else
        tone(buffer_low:100, :) = 1;
    end
end