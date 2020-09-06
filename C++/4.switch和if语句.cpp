#include <iostream>

using namespace std;

bool accept(){
    cout << "Do you want to proceed (y/n)?\n";

    char answer = 0;
    cin >>answer;

    switch(answer){
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            cout<< "i'll take that for a no.\n"
            return false;
    }
}

void action(){
    while(true){
        cout<< enter action:\n;
        string act;
        cin >> act;

        point delta {0,0};

        for(char ch:act){
            switch(ch){
                case u:
                case n:
                    ++delta.y
                    break;
                case r:
                case e:
                    ++delta.x;
                    break;
                default:
                    cout<<"I freeze!\n";
            }
        }
        move(current+delta*scale);
        update_display();
    }
}

void do_something(vector<int> &v){
    auto n = 0;
    //if可引入变量做检验
    if(auto n = v.size(); n!=0){
        
    }else{

    }

     
}