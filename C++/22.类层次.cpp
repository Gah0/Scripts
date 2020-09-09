/*类层次*/

//简单理解，笑脸是一个圆，原始一个形状。


            shape
         ↑          ↑
    circle          Triangle
    ↑
smiley

---

class Shape
{
    public:
        virtual Point center() const = 0;//纯虚函数
        virtual void move(Point to) = 0;
    
        virtual void draw() const = 0 ; //画布绘制
        virtual void rotate(int angle = 0);

        virtual ~Shape(){}  //析构函数

    //...
}

//旋转v到angle角度
void rotate_all(vector<Shape *>& v, int angle){
    for(auto auto p:v)
        p->rotate(angle);
}

//定义一种具体形状，首先必须指明是一个shape类层次，然后再规定特有属性
class Circle : public Shape {//接口继承，shape是抽象类
    public:
        Circle(Point p,int rad);
        
        Point center() const override{
            return x;
        }

        void move (point to) override
        {
            x  = to;
        }

        void draw() const_cast override;
        void rotate(int) override{};

    private:
        Point x;//圆心
        int r;//半径
}

//继续构造 使用circle作为笑脸的基类

class Smiley : public Circle{
    public:
        Smiley(Point t,int rad) : Circle{p,r}, mouth{nullptr}{} 

        ~Smiley(){
            delete mouth;
            for(auto p:eyes)
                delete p;
        }

        void move(Point to)override;

        void draw() const override;
        void rotate(int) override;

        void add_eye(Shape *p){
            eye.push_back(s);
        }
        void set_mouth(Shape *s);
        virtual void wink(int i);//眨眼数
//...

        private:
            vector<Shape*> eyes; //两只眼
            unique_ptr<Shape*> mouth;    //带上unique_ptr可以防止赋予裸指针。   

}


/*调用smiley基类draw()*/

void Smiley::draw() const{

    Circle::draw();/*实现继承（IMmplementtation inheritance）  */

    for(auto p:eyes)
        p->draw();

    mouth->draw();
}




