xn=[1,1,1,1];
w=-pi:pi/128:pi;
[X,PH]=DTFT(xn,w);
figure;
subplot(211);plot(w/pi,X,'r','LineWidth',2);title('Amplitude frequency');
xlabel('频率（单位\pi）');ylabel('|X(e^{j\omega})|');
subplot(212);plot(w/pi,PH,'r','LineWidth',2);title('Phase frequency');
xlabel('频率(单位\pi)');ylabel('弧度/\pi');

function [X,ph]=DTFT(x,W,n0)
x=x(:).';
Nt=length(x);
n=0:Nt-1;
X=x*exp(-j*(n)'*W);
if nargout==2,ph=angle(X);X=abs(X);end
end