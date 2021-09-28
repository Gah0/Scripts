# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
font = FontProperties(fname=r"C:\Windows\Fonts\simhei.ttf", size=14)  

row= [0, 1, 2, 3, 4, 5, 6, 7]
grey =[0.1, 0.05, 0.15, 0.2, 0.2, 0.15, 0.05, 0.1]
new_grey = []
tmp = 0
i=0

def accu_grey(i,tmp,grey,new_grey):

    while(i<len(row)):
        tmp = tmp + grey[i] 
        new_grey.append(round(tmp,3))
        i+=1

def interga(i,new_grey,new_s):
    te=new_grey[i]
    te1=round(te**7)
    new_s.append(te1)
    i=i+1

def mapping(i,grey,new_s,balance):
    s=new_s[i] #{0,1,2,4,5,6,6,7}
    if s == row[i]:
        balance.append(grey[i])
        if s>row[i]:
            b=row[i]
            if b not in new_s[i]:
               balance.append(0)



'''
    for i in grey:
        if i == 0:
            new_grey[i] = grey[i]
            i=i+1
            continue
        else:
            new_grey[i] = new_grey[i-1] + grey[i]
            i=i+1
'''

def plot(row,grey,new_grey):
    fig = plt.figure()
    picture1= fig.subplots(2,1)
    plt.xlabel('Gray level')
    plt.ylabel('Pixel')
    plt.bar(row, grey , label=picture1)
    
    picture2= fig.subplots(2,2)
    plt.xlabel('Gray level')
    plt.ylabel('Pixel')
#    plt.bar(row, new_grey,label=picture2)
    plt.show()

if __name__ == '__main__':
    accu_grey(i,tmp,grey,new_grey)
    interga(i, new_grey, new_s)
    mapping(i, grey, new_s, balance)
    plot(row, grey,new_grey,balance)