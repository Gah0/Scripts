max = int(input())


def fib(max):
    a, b = 1, 1
    while a < max:
        yield a
        a, b = b, a + b


for n in fib(15):
    print(n)
#以上是一段关于斐波那契数列的程序。fib()函数因为含有yield，
# 被系统默认为是一个生成器。for语句调用了fib(15)。
# 当max=15时，进入fib()生成器，执行到yield a，
# 返回a值以及整个生成器暂停的状态，将a值赋给n，
# 打印出来；因为是for语句循环，所以又回到fib(15)语句，
# 由于是生成器，因此从上次截断的位置开始执行，b值赋给a, a+b值赋给b，
# 又因为是while语句，则继续while循环，yield a值，
# 循环暂停跳出返回a值及生成器状态，把a值赋给n, 打印n。如此往复，
# 一直循环到15结束。
