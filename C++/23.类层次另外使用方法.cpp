#include <iostream>

enum class Kind{circle,triangle,smiley}

Shape *read_shape(istream& is){
    char cir = is.circle;

    switch(k){
        case Kind::circle:
            return new Circle{p,r};
        case Kind::traingle:
            return new triangle{p1,p2,p3};
        case Kind::smiley:
            Smiley *ps = new Smiley{p,r};
            ps->add_eye(e1);
            ps->add_eye(e2);
            ps->set_mouth(m);
            return ps;
    }
}


//
void user(){
    std::vector<Shape*> v;
    while(cin)
        v.push_back(read_shape(cin));
    draw_all(v);
    rotate_all(v,45);
    for(auto p:v)
        delete p;

}