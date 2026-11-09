#ifndef GENERATED_H
#define GENERATED_H

#include <string>

#include "tracer.h"

// Item 5: ce functii scrie compilatorul singur

// clasa goala: compilatorul ii scrie constructor implicit, copy constructor, operator= si destructor
class Empty
{
};

// nu scriu niciun constructor, destructor sau operator=, dar membrii afiseaza mesaje
// ca sa se vada ca functiile generate de compilator chiar sunt apelate
class AutoStudent
{
public:
    int getYear() const;

private:
    Tracer tracer{"student"};
    std::string faculty = "Calculatoare";
    int year = 3;
};

// am scris un constructor, deci compilatorul nu mai scrie constructorul implicit
class WithCtor
{
public:
    explicit WithCtor(int newValue);

    int getValue() const;

private:
    int value;
};

// are un pointer si nu am scris destructor sau copy constructor
// copy constructorul generat copiaza doar adresa, iar destructorul generat nu sterge ce e la adresa
class PtrHolder
{
public:
    explicit PtrHolder(int newValue);

    int* getPtr() const;

private:
    int* ptr;
};

// din carte: are membru referinta si membru const, deci operator= nu se mai genereaza
template <typename T>
class NamedObject
{
public:
    NamedObject(std::string& name, const T& value) : nameValue(name), objectValue(value)
    {
    }

    const std::string& getName() const
    {
        return nameValue;
    }

    const T& getValue() const
    {
        return objectValue;
    }

private:
    std::string& nameValue;  // referinta
    const T objectValue;     // const
};

// nu declar nimic, deci compilatorul scrie si move constructorul
class AutoMove
{
private:
    Tracer tracer{"fara destructor"};
};

// am declarat destructorul, deci compilatorul nu mai scrie move constructorul
// la std::move se apeleaza copy constructorul
class DtorMove
{
public:
    ~DtorMove()
    {
    }

private:
    Tracer tracer{"cu destructor"};
};

#endif
