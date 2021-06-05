// LSP : (Liskov Substitution Principle) 리스코프 치환 원칙

#include <iostream>

using namespace std;

class Rectangle
{
public:
    Rectangle(int width, int height)
        : width{ width }, height{ height } { }

    int get_width() const { return width; }
    int get_height() const { return height; }
    int get_area() const { return width * height; }

    virtual void set_width(int w) { width = w; }
    virtual void set_height(int h) { height = h; }
    
protected:
    int width, height;
};

class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {}
    void set_width(int w) override { width = height = w; }
    void set_height(int h) override { height = width = h; }
};

void process(Rectangle& r)
{
    int w = r.get_width() + 10;
    int h = r.get_height();
    r.set_width(w);

    cout << "expected area = " << (w * h)
        << ", got " << r.get_area() << std::endl;
}

int main()
{
    Rectangle r{ 3, 4 };
    process(r);

    Square sq{ 5 };
    process(sq);
}