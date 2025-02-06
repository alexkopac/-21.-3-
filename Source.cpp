#include <iostream>
#include <fstream>

class Equation {
public:
    virtual void Solve() const = 0;  
    virtual ~Equation() {}
};

class LinearEquation : public Equation {
private:
    double a, b;
public:
    LinearEquation(double a, double b) : a(a), b(b) {}

    void Solve() const override {
        if (a == 0) {
            if (b == 0)
                std::cout << "Infinite solutions.\n";  
            else
                std::cout << "No solution.\n";  
        }
        else {
            double x = -b / a;  
            std::cout << "Linear equation solution: x = " << x << std::endl;
        }
    }
};

class QuadraticEquation : public Equation {
private:
    double a, b, c;
public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    void Solve() const override {
        double D = b * b - 4 * a * c;  

        if (D < 0)
            std::cout << "No real solutions.\n"; 
        else if (D == 0)
            std::cout << "Quadratic equation has one solution: x = " << -b / (2 * a) << std::endl;
        else {
            double x1 = (-b + D / (2 * a));  
            double x2 = (-b - D / (2 * a));  
            std::cout << "Quadratic equation solutions: x1 = " << x1 << ", x2 = " << x2 << std::endl;
        }
    }
};



class Shape {
public:
    virtual void Show() const = 0;  
    virtual void Save(std::ofstream& out) const = 0; 
    virtual void Load(std::ifstream& in) = 0;  
    virtual ~Shape() {}
};

class Square : public Shape {
private:
    int size;
public:
    Square(int size = 3) : size(size) {}

    void Show() const override {
        std::cout << "Square (" << size << "x" << size << "):\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << "* ";
            }
            std::cout << std::endl;
        }
    }

    void Save(std::ofstream& out) const override {
        out << "Square " << size << std::endl;
    }

    void Load(std::ifstream& in) override {
        in >> size;
    }

    int getSize() const { return size; }
    void setSize(int newSize) { size = newSize; }
};

class Rectangle : public Shape {
private:
    int width, height;
public:
    Rectangle(int width = 4, int height = 2) : width(width), height(height) {}

    void Show() const override {
        std::cout << "Rectangle (" << width << "x" << height << "):\n";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << "* ";
            }
            std::cout << std::endl;
        }
    }

    void Save(std::ofstream& out) const override {
        out << "Rectangle " << width << " " << height << std::endl;
    }

    void Load(std::ifstream& in) override {
        in >> width >> height;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void setWidth(int newWidth) { width = newWidth; }
    void setHeight(int newHeight) { height = newHeight; }
};

class Circle : public Shape {
private:
    int radius;
public:
    Circle(int radius = 3) : radius(radius) {}

    void Show() const override {
        std::cout << "Circle (radius = " << radius << "):\n";
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    std::cout << "* ";
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << std::endl;
        }
    }

    void Save(std::ofstream& out) const override {
        out << "Circle " << radius << std::endl;
    }

    void Load(std::ifstream& in) override {
        in >> radius;
    }

    int getRadius() const { return radius; }
    void setRadius(int newRadius) { radius = newRadius; }
};

int main() {
    
    LinearEquation eq1(2, -4);
    eq1.Solve();

    QuadraticEquation eq2(1, -3, 2);
    eq2.Solve();

    
    Square square(5);
    Rectangle rectangle(6, 3);
    Circle circle(4);

    
    std::cout << "Shapes:\n";
    square.Show();
    rectangle.Show();
    circle.Show();

    
    std::ofstream outFile("shapes.txt");
    if (outFile) {
        square.Save(outFile);
        rectangle.Save(outFile);
        circle.Save(outFile);
        outFile.close();
    }

    
    Square loadedSquare;
    Rectangle loadedRectangle;
    Circle loadedCircle;

    std::ifstream inFile("shapes.txt");
    if (inFile) {
        std::string type;
        inFile >> type;
        if (type == "Square") loadedSquare.Load(inFile);

        inFile >> type;
        if (type == "Rectangle") loadedRectangle.Load(inFile);

        inFile >> type;
        if (type == "Circle") loadedCircle.Load(inFile);

        inFile.close();
    }

   
    std::cout << "\nLoaded Shapes:\n";
    loadedSquare.Show();
    loadedRectangle.Show();
    loadedCircle.Show();

    return 0;
}
