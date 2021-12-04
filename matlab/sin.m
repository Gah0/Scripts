t=0:0.001:50;
y=sin(2*pi*50*t);
xlabel('t'),ylabel('y');
subplot(2,2,1);
plot(t(1:50),y(1:50));
s= y +randn(size(t));
xlabel('t'),ylabel('s');
subplot(2,2,2);
title('sin')
plot(t(1:50),s(1:50));

t1
