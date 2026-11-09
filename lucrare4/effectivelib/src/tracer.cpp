#include "tracer.h"

#include <iostream>
#include <utility>

Tracer::Tracer() : name("fara nume")
{
    std::cout << "      [Tracer '" << name << "'] constructor implicit\n";
}

Tracer::Tracer(const std::string& newName) : name(newName)
{
    std::cout << "      [Tracer '" << name << "'] constructor cu nume\n";
}

Tracer::Tracer(const Tracer& other) : name(other.name)
{
    std::cout << "      [Tracer '" << name << "'] copy constructor\n";
}

Tracer::Tracer(Tracer&& other) noexcept : name(std::move(other.name))
{
    std::cout << "      [Tracer '" << name << "'] move constructor\n";
}

Tracer& Tracer::operator=(const Tracer& other)
{
    name = other.name;
    std::cout << "      [Tracer '" << name << "'] copy assignment\n";
    return *this;
}

Tracer& Tracer::operator=(Tracer&& other) noexcept
{
    name = std::move(other.name);
    std::cout << "      [Tracer '" << name << "'] move assignment\n";
    return *this;
}

Tracer& Tracer::operator=(const std::string& newName)
{
    name = newName;
    std::cout << "      [Tracer '" << name << "'] atribuire dintr-un string\n";
    return *this;
}

Tracer::~Tracer()
{
    std::cout << "      [Tracer '" << name << "'] destructor\n";
}

const std::string& Tracer::getName() const
{
    return name;
}
