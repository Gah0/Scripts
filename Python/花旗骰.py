from random import randint

money = 500

while money > 0:
    print('你的资产为：' ,money)
    need_go_on = False
    while True:
        debt = int(input('请下注：'))
        if 0<debt<=money:
            break
    first = randint(1,6) + randint(1,6) + randint(1,6)
    print('玩家摇出了%d点'%first)

    if first == 7 or first == 11:
        print('win')
        money += debt
    elif first ==2 or first ==3 or first ==12:
        print('lose')
        money -= debt
    else:
        need_go_on = True

    while need_go_on:
        need_go_on = False
        current = randint(1,6)+randint(1,6)
        print('玩家摇出了%d点'%current)
        if current == 7:
            print('lose')
            money -= debt
        elif current == first:
            print('win')
            money += debt
        else:
            need_go_on = True
print('you dead!')