Fs=1000;
Fc=400;
N=1000;
n=0:N-2;
t=n/Fs;
x=sin(2*pi*50*t);
subplot(2,2,1);
plot(t,x);
xlabel('t(s)');
ylabel('x');
title('被调信号');
axis([0 0.1 -1 1]);


Nfft=1024;
windows=hamming(512);
noverlap=256;
dflang='none';
[Pxx,f]=pwelch(x,window,noverlap,Nfft,Fs);
subplot(2,2,2);
plot(f,Pxx);
xlabel('频率(HZ)');
ylabel('功率谱(X)');
title('被调信号的功率谱');
grid


y=modulate(x,Fc,Fs,'am');
subplot(2,2,3);
plot(t,y);
xlabel('t(s)');
ylabel('y');
axis([0 0.1 -1 1]);
title('已调信号');

[Pxx,f]=pwelch(y,window,noverlap,1024,Fs);
subplot(2,2,4);
plot(f,Pxx);
xlabel('频率(Hz)');
ylabel('功率谱(Y)');
title('已调信号的功率谱');
grid
