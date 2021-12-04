function [f,k]=convolution(f1,f2,k1,k2,p,l)
f=conv(f1,f2);
f=f*p;
k0=k1(1)+k2(1);
k3=length(f1)+length(f2)-2;
k=k0:p:k3*p;
subplot(2,2,1);
plot(k1,f1);
