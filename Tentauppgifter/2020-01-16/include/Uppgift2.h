#ifndef UPPGIFT2_h
#define UPPGIFT2_h

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <iostream>

class Figure
{   
    public:
        virtual double Area() = 0;
        std::string GetName() { return name; }
    protected:
        Figure(std::string n) : name(n) {}
    private:
        std::string name;

        Figure(const Figure&) = delete;
        const Figure& operator=(const Figure&) = delete;
};

class Circle : public Figure
{   
    public:
        static Circle* GetInstance(double r){ return new Circle(r); }
        double Area() { return radie * radie * 3.14; }
    protected:
        Circle(double r) : Figure("Circle"), radie(r)
        {}

    private:
        double radie;

};


class Polygon : Figure
{
    public:
        unsigned int Corners() { return corners; }
    protected:
        Polygon(std::string n, unsigned int c) : Figure(n), corners(c)
        {}

    private:
        unsigned int corners;
};


class Triangle : public Polygon
{
    public:
        static Triangle* GetInstance(double b, double h) { return new Triangle(b,h); }
        double Area() { return (base * height) / 2.0f;}
    
    protected:
        Triangle(double b, double h) : Polygon("Triangle", 3), base(b), height(h)
        {}
    
    private:
        double base, height;
};

class Compound : public Figure
{
    public:
        static Compound* GetInstance(){ return new Compound(); }
        void AddFigure(Figure* f) { figures.push_back(f); }

        double Area()
        {
            double sumArea = 0.0f;

            for(Figure* f : figures)
                sumArea += f->Area();
            
            return sumArea;
        }

        unsigned int GetCornerSum()
        {
            unsigned int sumCorners = 0;

            for(Figure* f : figures)
            {
                if(Polygon* p = dynamic_cast<Polygon*>(f))
                    sumCorners += p->Corners();
            }

            return sumCorners;
        }

    protected:
        Compound(): Figure("Compound")
        {}
    
    private:
        std::vector<Figure*> figures;
};



#endif