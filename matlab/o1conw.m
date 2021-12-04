clear;
p=0.1;p1=1;
k1=-1:p:1;
k2=-2:p:2;
k5=-1:p1:1;
k6=-2:p1:2;

f1=2*ones(size(k1)).*and(k1>=-1,k1<=1);
f2=ones(size(k2)).*and(k2>=-2,k2<=2);
f3=2*ones(size(k5)).*and(k5>=-1,k5<=1);
f4=ones(size(k6)).*and(k6>=-2,k6<=2);


w=conv(f1,f2,'full');
w=w*p;

v=conv(f3,f4,'full');
v=v*p1;

k8=k1(1)+k2(1);
k3=length(f1)+length(f2)-2;
k=k8:p:k8+k3*p;

k4=k5(1)+k6(1);
k7=length(f3)+length(f4)-2;
k9=k4:p1:k4+k7*p1;

subplot(2,2,1)
plot(k1,f1,'b');
title('f1(t)');
xlabel('t');
ylabel('f1(t)');
%
subplot(2,2,2);
plot(k2,f2,'b');
title('f2(t)');
xlabel('t');
ylabel('f2(t)');

%
subplot(2,2,3);
plot(k,w,'b');
title('w=f1(t)*f2(t),p=0.1');
xlabel('t');
ylabel('w(t)');
%
subplot(2,2,4);
plot(k9,v,'b');
title('v=f1(t)*f2(t),p=1');
xlabel('t');
ylabel('v(t)');