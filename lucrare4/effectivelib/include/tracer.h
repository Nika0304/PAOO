#ifndef TRACER_H
#define TRACER_H

#include <string>

// obiect care afiseaza un mesaj cand e construit, copiat, mutat, atribuit sau distrus
// il folosesc ca sa se vada ce functii apeleaza compilatorul
class Tracer
{
public:
    Tracer();                                       // constructor implicit
    explicit Tracer(const std::string& newName);    // constructor cu nume
    Tracer(const Tracer& other);                    // copy constructor
    Tracer(Tracer&& other) noexcept;                // move constructor
    Tracer& operator=(const Tracer& other);         // copy assignment
    Tracer& operator=(Tracer&& other) noexcept;     // move assignment
    Tracer& operator=(const std::string& newName);  // atribuire dintr-un string
    ~Tracer();                                      // destructor

    const std::string& getName() const;

private:
    std::string name;
};

#endif
