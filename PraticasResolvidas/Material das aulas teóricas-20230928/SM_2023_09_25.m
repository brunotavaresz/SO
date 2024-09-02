% signal parameters
T=2;
a=0.3;
% time instants
t=(-1000:1000)/1000*(1.5*T);
% approximation with only the n=0 term
x=c(0,T,a)*ones(size(t));
plot(t,x);
grid on;
axis([-1.5*T,+1.5*T,-0.2,+1.2]);
title('n=0');
drawnow;
for n=1:100
  % adding the n and -n terms
  x=x+c( n,T,a)*exp(1j*2*pi* n*t/T) + ...
      c(-n,T,a)*exp(1j*2*pi*-n*t/T);
  pause(0.1);
  plot(t,real(x));
  grid on;
  axis([-1.5*T,+1.5*T,-0.2,+1.2]);
  title(sprintf('%d <= n <= %d',-n,n));
  drawnow;
end

% the expansion coefficients
function cn = c(n,T,a)
  if n==0
    cn = 2*a/T;
  else
    cn = sin(2*pi*n*a/T)/(pi*n);
  end
end
