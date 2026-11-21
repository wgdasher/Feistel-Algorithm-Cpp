#include <iostream>
#include "poly.h"

int poly::get_degree(unsigned int a) {
    int degree = -1;
    if (a == 0)
        return degree;

    while (a != 0) {
        ++degree;
        a = a >> 1;
    }

    return degree;
}

poly::divReturn poly::divide_galois(unsigned int a, unsigned int m) {
    poly::divReturn output = {a, 0};

    int deg_m = poly::get_degree(m);

    if (deg_m < 0)
        return output;

    int deg_r = poly::get_degree(output.r);

    while (deg_r >= deg_m) {
        int shift = deg_r - deg_m;
        output.r ^= (m << shift);
        output.q |= (1u << shift);

        deg_r = poly::get_degree(output.r);
    }

    return output;
}

unsigned int poly::multiply_galois(int a, int b, int m) {
    int index = 0;
    int result = 0;

    while (b != 0) {
        if (b & 1) {
            result = result ^ (a << index);
        }
        b = b >> 1;
        ++index;
    }

    return (poly::divide_galois(result, m).r);
}