b =1 ;
c1=1;
c2=1;
a1= [1,-c1];%系数
a2=[1,-c2];%系数
[H1,w1]=freqz(b,a1,1000,'whole');
[H2,w2]=freqz(b,a2,1000,'whole');
subplot(4,1,1)
plot(w1,abs(H1),'g');
xlabel('频率（弧度）');ylabel('幅度');
title ('系统的幅频响应');
grid;
subplot(4,1,2)
plot(w2,abs(H2),'g');
xlabel('频率（弧度）');ylabel('幅度');
grid;
