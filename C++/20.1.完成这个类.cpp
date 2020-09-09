#include <stdio.h>

using std::string;

class AfInteger
{
    pubilic:
        int AfInteger(){
            this -> value = 0;
        }
        AfInteger(int value):value(value){}
        operator int(){
            return value;
        }

        string toString() const{
            char buf[32];
            sprintf(buf,"%d",value);
            return string(buf);
        }
    private:
        int value;
}

int main (){
    AfInteger obj(12);
    string strValue = obj.toString();
    printf("value: %s \n", strValue.c_str());
    return 0;
}