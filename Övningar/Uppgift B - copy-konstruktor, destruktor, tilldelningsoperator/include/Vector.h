
#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector(int n) : siz(n), data(new int[siz]){}        

        // CC
        Vector(const Vector& other)
        {
            siz = other.siz;
            data = new int[siz];
            for(int i = 0; i < siz; i++)
                data[i] = other.data[i];
        }

        // tilldelningsOp
        const Vector& operator=(const Vector& other)
        {
            if(this != &other)
            {
                delete [] data;

                siz = other.siz;

                data = new int[siz];

                for(int i = 0; i < siz; i++)
                    data[i] = other.data[i];
            }

            return *this;
        }

        // Destruktor
        ~Vector()
        {
            siz = 0;
            delete [] data;
        }


        int& operator[](int index) {return data[index];}

        

    private:
        int siz;
        int *data;

};


#endif