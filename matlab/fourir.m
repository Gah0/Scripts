clear;
syms t;
syms u;
u=heaviside(t);
t1=abs(t);
%x=1/2*exp(-2*t1)*sym(u);
x=exp(-2*t1);
subplot(1,2,1);
ezplot(x);
F=fourier(x);

subplot(1,2,2);
ezplot(abs(F));