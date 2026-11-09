#include <iostream>

#include "mylib.h"

int main() {
    std::cout << "3 + 4 = " << mylib::add(3, 4) << '\n';
    std::cout << "5! = " << mylib::factorial(5) << '\n';

    for (int n : {1, 7, 10, 13}) {
        std::cout << n << (mylib::isPrime(n) ? " este prim" : " nu este prim") << '\n';
    }

    return 0;
}
