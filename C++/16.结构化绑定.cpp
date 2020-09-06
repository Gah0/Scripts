#include <iostream>

struct Entry{
    string name;
    int value;
}

Entry read_entry(istream& is){
    string s;
    int i ;
    is >> s >> i;
    return {s,i};
}

auto e = read_entry(cin);
cout<<"{"<<e.name<<"，"<<e.value<<"}\n";

//结构化绑定
auto [n,v] = read_entry(is);
cout << "{" << n << "," << v << "}" << "\n";


//
map<string,int>,m;
//填充m
for(const auto [key,value]:m){
    cout << "{" << key"," << value << "}\n";
}

void incr(map<string,int>& m){
    for(auto &[key,value]:m){
        value ++;
    }
}



complex <double> z = {1,2};
auto [re,im] = z+2;  // 3+2i;

