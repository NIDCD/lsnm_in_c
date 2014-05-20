%Note that currently this will result in exactly 'tone_len' number of ticks
%with the sf centered on the tone's freq. i.e. if freq(2) = 20 and tone_len
%= 4, there will be 4 points centered at sf of 20... the upsweep and
%downsweep end and begin centered on 1 point above this number,
%respectively
function down_tc = make_down_tc(freqs,buffers,tone_len)
    start_freq = freqs(1);
    tone_freq = freqs(2);
    end_freq = freqs(3);
    down_buffer = buffers(1);
    tone_buffer = buffers(2);
    up_buffer = buffers(3);
    down_len = start_freq-tone_freq;
    up_len = end_freq-tone_freq;
    downsweep = make_downsweep(start_freq,down_len,down_buffer);
    tone = make_tone(tone_freq,tone_len,tone_buffer);
    upsweep = make_upsweep(tone_freq+1,up_len,up_buffer);
    down_tc = [downsweep tone upsweep];
end