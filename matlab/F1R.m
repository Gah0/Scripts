close all;
clear all;
wn = 0.25;N1=15;N2=33;
windows1=hanning(N1+1);
windows2= hanning(N2+1);
b1 = fir1(N1,wn,windows1);
b2 = fir1(N2,wn,windows2);
[H1,W1]=freqz(b1,1,512,2);
[H2,W2]=freqz(b1,1,512,2);
figure;
subplot(3,3,1);

plot(W1,20*log(abs(H1)),'r+');
hold on ;
plot(W2,20*log(abs(H2)),'b');
plot(W1,3*ones(size(W1)),'r-');
plot(W1,-20*ones(size(W1)),'k-');
hold off;

ylabel('幅度/dB'),xlabel('归一化频率');
legend('N1=15','N2=33')


subplot(2,2,2)
plot(W1,angle(H1),'r+');
hold on;
plot(W2,angle(H2),'b');
hold off;
ylabel('幅度/dB'),xlabel('归一化频率');
legend('N1=15','N2=33')

windows3=boxcar(N2+1);
windows4=trainning(N2+1);
%windows5=hamming(N2+1);
%windows6= blackman(N2+1);
b3 = fir1(N2,wn,windows3);
b4 = fir1(N2,wn,windows4);
%b5 = fir1(N2,wn,windows5);
%b6 = fir1(N2,wn,windows6);
[H3,W3]=freqz(b1,1,512,2);
[H4,W4]=freqz(b1,1,512,2);
figure1;
subplot(2,2,1);
plot(W3,20*log(abs(H3)),'r+');
plot(W3,20*log(abs(H3)),'b');
ylabel('幅度/dB'),xlabel('归一化频率');
subplot(2,2,2);
plot(W4,20*log(abs(H4)),'r+');
plot(W4,20*log(abs(H4)),'b');
ylabel('幅度/dB'),xlabel('归一化频率');


%[H5,W5]=freqz(b1,1,512,2);
%figure;
%subplot(3,3,5);
%plot(W5,20*log(abs(H5)),'b');
%ylabel('幅度/dB'),xlabel('归一化频率');


%[H6,W6]=freqz(b1,1,512,2);
%figure;
%subplot(3,3,6);
%plot(W6,20*log(abs(H6)),'b');
%ylabel('幅度/dB'),xlabel('归一化频率');




