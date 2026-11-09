#ifndef INIT_ORDER_H
#define INIT_ORDER_H

#include "tracer.h"

// Item 4: ordinea de initializare
// membrii se initializeaza in ordinea in care sunt declarati in clasa, nu in ordinea din lista
class OrderDemo
{
public:
    OrderDemo();

private:
    Tracer first;   // declarat primul
    Tracer second;  // declarat al doilea
};

// b e declarat primul, deci se initializeaza primul si il citeste pe a, care nu e inca initializat
class BadOrder
{
public:
    explicit BadOrder(int x);

    int getA() const;
    int getB() const;

private:
    int b;  // declarat primul
    int a;
};

// varianta corecta: a e declarat inaintea lui b
class GoodOrder
{
public:
    explicit GoodOrder(int x);

    int getA() const;
    int getB() const;

private:
    int a;  // declarat primul
    int b;
};

#endif
