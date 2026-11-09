#include "entry.h"

#include <iostream>

// membrii theName si theAddress sunt deja construiti (cu constructorul implicit) cand intru in corp
EntryBody::EntryBody(const std::string& name, const std::string& address)
{
    std::cout << "    [EntryBody] intru in corpul constructorului\n";
    theName = name;        // atribuire, nu initializare
    theAddress = address;  // atribuire, nu initializare
    numTimesConsulted = 0;
}

int EntryBody::getTimesConsulted() const
{
    return numTimesConsulted;
}

// ordinea din lista e aceeasi cu ordinea in care sunt declarati membrii in clasa
EntryList::EntryList(const std::string& name, const std::string& address, int& counter)
    : theName(name), theAddress(address), numTimesConsulted(0), id(++counter), sharedCounter(counter)
{
    std::cout << "    [EntryList] intru in corpul constructorului, membrii sunt deja gata\n";
}

int EntryList::getId() const
{
    return id;
}

int EntryList::getTimesConsulted() const
{
    return numTimesConsulted;
}

int EntryList::getSharedCounter() const
{
    return sharedCounter;
}
