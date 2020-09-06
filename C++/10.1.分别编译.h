/*
 * 写入vector.h中
*/

vector接口
class Vector{
    public:
        Vector(int s);
        double& operator[](int i);
        int size();
///分离
    private:
        double *elem;
        int sz;
}

