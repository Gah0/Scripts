"""
输出斐波那契数列的前20个数
1 1 2 3 5 8 13 21 ...
"""
number = []
count=0

while count < 20:
    for i in range(count):
        if count == 0:
            num = 1
        else:
            num = num + num-1
            count += 1
            number.append(num)
            print(number)

#另一种写法
a = 0
b = 1
for _ in range(20):
    a, b = b, a + b
    print(a, end=' ')
