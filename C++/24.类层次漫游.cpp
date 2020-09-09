/*使用某个特定派生类提供的成员函数，smiley的wink()*/
Shape *ps{read_shape(cin)};

//dynamic_cast ps指向一个Smiley吗？
if(Smiley *p = dynamic_cast<Smiley*>(ps)){
    //使用
}else{
    //不使用
}
//如果dynamic_cast指向类型不是期待的类型，则dynamic_cast返回nullptr

//直接使用如果对象不是与其类型，会抛出bad_cast异常
Smiley& r{dynamic_cast<Smiley&>(*ps)};



//unique_ptr可以防止裸指针
//23.类层次的补充
unique_ptr<Shape> read_shape(istream& is){
    switch(k){
        case Kind::circle
            return unique_ptr<Shape>{new Circle{p, r}}
    }
}


void user(){
    vector<unique_ptr<Shape>> v;
    while(cin){
        v.push_back(read_shape(cin));
    }
    draw_all(v);
    rotate_all(v,45);
}