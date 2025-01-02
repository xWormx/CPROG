#ifndef DJURKLASSER_H
#define DJURKLASSER_H

#include <string>


using namespace std;


class Djur
{
    public:
        virtual int getVarde() const = 0;
        virtual ~Djur(){}
        string getNamn() const { return namn; }
        int getVikt() const { return vikt; }
    protected:
        Djur(string n, int v) : namn(n), vikt(v){}

    private:
        string namn;
        int vikt;
        Djur(const Djur&) = delete;
        const Djur& operator=(const Djur&) = delete;
};

class Elefant : public Djur
{

    public:
        static Elefant* GetInstance(string n, int v, int s) { return new Elefant(n,v,s);}
        int getSnabel() const { return snabel; }
        void setSnabel(int nySnabel) { snabel = nySnabel;}
        int getVarde() const { return snabel * getVikt(); }
    protected:
        Elefant(string n, int v, int s) : Djur(n, v), snabel(s) {}

    private:
        int snabel;
};


class TusenFoting : public Djur
{
    public:
        static TusenFoting* GetInstance(string n, int v) { return new TusenFoting(n,v); }
        ~TusenFoting(){
            delete fotter;
        }

        void setFot(int pos, double vad){ fotter[pos] = vad;}
        int getVarde() const{
            double sum = 0;
            for(int i = 0; i < 1000; i++){
                sum += fotter[i];
            }
            return getVikt() + sum;
        }
    protected:
        TusenFoting(string n, int v) : Djur(n, v){
            fotter = new double[2000];
        }

    private:
    double* fotter;

};


#endif