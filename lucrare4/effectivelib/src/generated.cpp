#include "generated.h"

int AutoStudent::getYear() const
{
    return year;
}

WithCtor::WithCtor(int newValue) : value(newValue)
{
}

int WithCtor::getValue() const
{
    return value;
}

PtrHolder::PtrHolder(int newValue) : ptr(new int(newValue))
{
}

int* PtrHolder::getPtr() const
{
    return ptr;
}
