
t=0:0.001:50;
y=sin(2*pi*50*t);
s=y+randn(size(t));
figure(1);
subplot(3,1,1);
plot(t(1:50),s(1:50),'r');
title('random noise of sin(100πt)');
xlabel('t1=[0:0.01:50]');ylabel('y1');
grid;
%%%
t1=0:0.001:50;
y1=sin(pi*50*t1);
s1=y1+randn(size(t1));
subplot(3,1,2);
plot(t1(1:50),s1(1:50),'r');
title('random noise of sin(50πt)');
xlabel('t1=[0:0.01:50]');ylabel('y2');
grid;
%%%
t2=0:0.005:30;
y2=sin(2*pi*50*t2);
s2=y2+randn(size(t2));
subplot(3,1,3);
plot(t2(1:30),s2(1:30),'r');
title('random noise of sin(100πt)');
xlabel('t1=[0:0.05:30]');ylabel('y3');
grid;
%%%
