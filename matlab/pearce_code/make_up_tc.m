%Note that currently this will result in exactly 'tone_len' number of ticks
%with the sf centered on the tone's freq. i.e. if freq(2) = 20 and tone_len
%= 4, there will be 4 points centered at sf of 20... the upsweep and
%downsweep end and begin centered on 1 point below this number,
%respectively
function up_tc = make_up_tc(freqs,buffers,tone_len)
    start_freq = freqs(1);
    tone_freq = freqs(2);
    end_freq = freqs(3);
    up_buffer = buffers(1);
    tone_buffer = buffers(2);
    down_buffer = buffers(3);
    up_len = tone_freq-start_freq;
    down_len = tone_freq-end_freq;
    upsweep = make_upsweep(start_freq,up_len,up_buffer);
    tone = make_tone(tone_freq,tone_len,tone_buffer);
    downsweep = make_downsweep(tone_freq-1,down_len,down_buffer);
    up_tc = [upsweep tone downsweep];
end