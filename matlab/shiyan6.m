clear;
wm=1;
wc=wm;
Ts=1.5*pi/wm;
ws=2*pi/Ts;
n=-100:100;
nTs=n*Ts;
f=sinc(nTs/pi);
Dt=0.005;
t=-15:Dt:15;
fa=f*Ts*wc/pi*sinc((wc/pi)*(ones(length(nTs),1)*t-nTs'*ones(1,length(t))));
error=abs(fa-sinc(t-pi));
t1=-15:0.5:15;
f1=sinc(t1/pi);

subplot(3,1,1);
stem(t1,f1);
xlabel('kTs');
ylabel('f(kTs)');
title('sa(t)=sinc(t/pi)临界采样信号');

subplot(3,1,2);
plot(t,fa);
xlabel('t');
ylabel('fa(t)');
title('由sa(t)=sinc(t/pi)的临界采样信号重构sa(t)');
grid;

subplot(3,1,3);
plot(t,error);
xlabel('t');
ylabel('error(t)');
title('临界采样信号与原信号的误差error(t)');
