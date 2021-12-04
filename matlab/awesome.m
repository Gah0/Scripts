dt=0.01;
sys=tf([1,10],[1,4,4]);
t=0:dt:10;
f=exp(-t).*heaviside(t);
y=lsim(sys,f,t);
plot(t,y,'r');
xlabel('Time(sec)'); ylabel('y(t)');
title('思考拓展题by朱嘉浩')