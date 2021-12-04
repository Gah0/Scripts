clear;
p1=0.5;p=0.01;
k1=0:p:2;k2=0:p:2;
k4=0:p1:2;k5=0:p1:2;
f1=0.5*k1;f2=0.5*k2;
f3=0.5*k4;f4=0.5*k5;

w=conv(f1,f2,'full');
v=conv(f3,f4,'full');%

w=w*p;
v=v*p1;%

k0=k1(1)+k2(1);
k3=length(f1)+length(f2)-2;

k6=k4(1)+k5(1);
k7=length(f3)+length(f4)-2;

k=k0:p:k0+k3*p;
kv=k6:p1:k6+k7*p1;%
%
subplot(2,2,1)
plot(k1,f1,'r');
title('f1(t)');
xlabel('t');
ylabel('f1(t)');
%
subplot(2,2,2);
plot(k2,f2,'r');
title('f2(t)');
xlabel('t');
ylabel('f2(t)');
%
subplot(2,2,3);
plot(k,w,'g+');
axis([0 6 0 1])
title('w=f1(t)*f2(t),p=0.01');
xlabel('t');
ylabel('w');
%
subplot(2,2,4);
plot(kv,v,'g+');
axis([0 6 0 1])
title('v=f1(t)*f2(t),p=0.6');
xlabel('t');
ylabel('v');

