clc;
N=4;%长度
nx=0:1:N-1;%步长1
X=[1,1,1,1];%序列
subplot(5,1,1);stem(nx,X,'r');grid;
xlabel('时间');ylabel('高度');title ('R4(n)');

n=0:0.01:8;
X2=(n+1).*(n>=0&n<3)+(8-n).*(n>=4&n<7)+0;
subplot(5,1,2);stem(n,X2,'r','.');
xlabel('n');ylabel('X2(n)');title ('分段函数2');

n1=0:0.01:8;
X3=(4-n1).*(n1>=0&n<3)+(n1-3).*(n1>=4&n1<7)+0;
subplot(5,1,3);stem(n1,X3,'r','.');
xlabel('n1');ylabel('X3(n)');title ('分段函数3');

n2=0:0.1:8*pi;
X4=cos(n2*pi/4);
subplot(5,1,4);stem(n2,X4,'r');
xlabel('n2');ylabel('X4(n2)');title ('X4=cos(n2*pi/4)');

n3=0:0.1:8;
X5=10*(0.8).^(n3);
subplot(5,1,5);stem(n3,X5,'r');
xlabel('n3');ylabel('X5(n3)');title ('X5=10*0.8.^n;');
