%学生实验内容 微分方程
a=[2,1,8];
b=[1];
yi=impulse(b,a,0:0.01:30);
subplot(2,1,2);
ys=step(b,a,0:0.01:30);
subplot(2,1,1);

impulse(b,a,0:0.01:30);
step(b,a,0:0.01:30);
grid;