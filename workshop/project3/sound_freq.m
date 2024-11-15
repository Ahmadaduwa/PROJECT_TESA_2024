function spectrum = sound_freq(X)
arguments
    X(1,4096) double 
end
    Y = fft(X); %complex num
    mag = abs(Y); % abs sulute 
    spectrum = mag(1:2048); % หา magnitude 
end