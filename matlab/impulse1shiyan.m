%学生实验内容 微分方程
a=[2,1,8];
b=[1];
t=(0:5:30);

yi=impulse(b,a,t);

ys=step(b,a,t);

disp(yi);

%xlabel('time/second'),ylabel('amplitude');
%figure('NumberTitle', 'off', 'Name', '绘制微分方程');
%title('冲击响应与时域响应');
%plot(yi,'g');
%subplot(2,1,1);
%plot(yi,'r');
%subplot(2,1,2);


