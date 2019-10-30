

import random, time, sys, datetime

print(sys.platform)
print(sys.version)

print(datetime.date.today().year)
print(datetime.date.today().month)
print(datetime.date.today().day)
print(datetime.date.today())

print(time.strftime("%H:%M:%S %A %p"))

print(random.randint(1,10))

girls = ["cuihua","meili","xishi","madongmei"]

for i in range(3):

    #girls_name = random.sample(girls,1)
    #↑列表切片
    girls_name = random.choice(girls)
    the_one = "".join(girls_name)

    #print (the_one)

    your_love = input("please input the name from girls list")

    if the_one == your_love:
        print("Y")
    else:
        for ii in girls:
            #sep:   string inserted between values, default a space.
            print(ii + "不是你的\n菜","poi",sep='#')

#在console窗户输入help(print)，可以看到built in function “print” 这个module



#Help on built-in function print in module builtins:
#print(...)
#    print(value, ..., sep=' ', end='\n', file=sys.stdout, flush=False)

#    Prints the values to a stream, or to sys.stdout by default.
#    Optional keyword arguments:
#    file:  a file-like object (stream); defaults to the current sys.stdout.
#    sep:   string inserted between values, default a space.
#    end:   string appended after the last value, default a newline.
#    flush: whether to forcibly flush the stream.
#    time.sleep(3)

