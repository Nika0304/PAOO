// g++ -Wall da avertismente (-Wreorder si -Wuninitialized) pentru clasele din init_order.h
// le opresc doar in acest fisier, ca sa nu apara la build; greselile sunt facute intentionat
// pragma trebuie sa fie inaintea #include, pentru ca avertismentul apare la declaratiile din header
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

#include "init_order.h"

#include <iostream>

// in lista scriu second inaintea lui first, dar se construieste tot first primul
OrderDemo::OrderDemo() : second("second"), first("first")
{
    std::cout << "    [OrderDemo] intru in corpul constructorului\n";
}

// b se initializeaza primul (e declarat primul), deci b(a) citeste un a neinitializat
BadOrder::BadOrder(int x) : a(x), b(a)
{
}

int BadOrder::getA() const
{
    return a;
}

int BadOrder::getB() const
{
    return b;
}

// a se initializeaza primul, deci b(a) primeste valoarea corecta
GoodOrder::GoodOrder(int x) : a(x), b(a)
{
}

int GoodOrder::getA() const
{
    return a;
}

int GoodOrder::getB() const
{
    return b;
}
