#ifndef POLY_H
#define POLY_H

namespace poly
{
    struct divReturn 
    {
        unsigned int r;
        unsigned int q;
    };

    int get_degree(unsigned int a);
    divReturn divide_galois(unsigned int a, unsigned int m);
    unsigned int multiply_galois(int a, int b, int m);
}

#endif