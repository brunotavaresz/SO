f0=200;                % frequency of the sinosoid
Fs=8000;               % sampling frequency
t=(0:5*Fs)/Fs;         % time instants for 5 seconds
x=sin(2*pi*f0*t);      % the sinusoid
sound(x,Fs);           % output sound

help chirp             % how to use chirp()
x=chirp(t,500,2,4000); % a chirp signal
sound(x,Fs);
