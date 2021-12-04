clear;
syms t w;
F=4/(4+w^2);
subplot(1,2,1);
ezplot(F);
f=ifourier(F,t);
subplot(1,2,2);
ezplot(f);

