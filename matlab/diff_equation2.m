 xcoeff = [1,1];
x1coeff = [1,-1];

[H1,w1] = freqz(xcoeff,1,1000,'whole');
subplot(4,1,1)
plot(w1,abs(H1),'g');
xlabel('频率（弧度）');ylabel('幅度');
title ('系统的幅频响应');
grid;


