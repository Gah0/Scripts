clc;
close;
B=[1,0,0,-1];A=[1,-1];
[H,w]=freqz(B,A,'whole');
plot(w,abs(H),'r','linewidth',2);grid on;
axis([0,2,0,1.3]);
xlabel('Frequency');ylabel('H(e^jw)');grid on;