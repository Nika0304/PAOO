#ifndef ENTRY_H
#define ENTRY_H

#include <string>

#include "tracer.h"

// Item 4: atribuire in corpul constructorului
// membrii Tracer se construiesc intai goi (constructor implicit), apoi se atribuie: doi pasi
class EntryBody
{
public:
    EntryBody(const std::string& name, const std::string& address);

    int getTimesConsulted() const;

private:
    Tracer theName;
    Tracer theAddress;
    int numTimesConsulted;
};

// Item 4: lista de initializare
// fiecare membru se construieste direct din argument: un singur pas
// const si referintele pot fi setate doar aici
class EntryList
{
public:
    EntryList(const std::string& name, const std::string& address, int& counter);

    int getId() const;
    int getTimesConsulted() const;
    int getSharedCounter() const;

private:
    Tracer theName;
    Tracer theAddress;
    int numTimesConsulted;
    const int id;        // const: se poate seta doar in lista de initializare
    int& sharedCounter;  // referinta: la fel, doar in lista de initializare
};

#endif
