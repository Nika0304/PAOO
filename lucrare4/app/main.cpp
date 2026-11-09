// Lucrare 4 - Effective C++, Item 4, Item 5, Item 6
// Rulare: ./app/app

#include <cstring>
#include <iostream>
#include <new>
#include <string>
#include <type_traits>
#include <utility>

#include "entry.h"
#include "file_system.h"
#include "generated.h"
#include "globals.h"
#include "home_for_sale.h"
#include "init_order.h"
#include "point.h"
#include "tracer.h"

int globalNumber;

static_assert(std::is_default_constructible<Empty>::value, "Empty constructor");
static_assert(std::is_copy_constructible<Empty>::value, "Empty copy ctor");
static_assert(std::is_copy_assignable<Empty>::value, "Empty operator=");
static_assert(!std::is_default_constructible<WithCtor>::value, "WithCtor no default ctor");
static_assert(std::is_copy_constructible<NamedObject<int>>::value, "NamedObject copy ctor");
static_assert(!std::is_copy_assignable<NamedObject<int>>::value, "NamedObject no operator=");
static_assert(!std::is_copy_constructible<HomeForSale>::value, "HomeForSale no copy ctor");
static_assert(!std::is_copy_assignable<HomeForSale>::value, "HomeForSale no operator=");
static_assert(!std::is_copy_constructible<HomeForSale98>::value, "HomeForSale98 no copy ctor");
static_assert(!std::is_copy_assignable<HomeForSale98>::value, "HomeForSale98 no operator=");
static_assert(!std::is_copy_constructible<Account>::value, "Account no copy ctor");
static_assert(!std::is_copy_assignable<Account>::value, "Account no operator=");

static void title(const std::string& text)
{
    std::cout << "\n" << text << "\n";
}

static void yesNo(const std::string& text, bool value)
{
    std::cout << "  " << text << ": " << (value ? "DA" : "NU") << '\n';
}

static const void* addr(const void* p)
{
    return p;
}


// Item 4


static void demoUninitialized()
{
    title("Item 4: Valori neinitializate");

    std::cout << "Global int (auto 0): " << globalNumber << '\n';

    alignas(BadPoint) unsigned char buffer[sizeof(BadPoint)];
    std::memset(buffer, 0xAB, sizeof(buffer));

    BadPoint* bad = new (buffer) BadPoint;
    std::cout << std::hex << "BadPoint fara (): x = 0x" << static_cast<unsigned>(bad->x) 
              << ", y = 0x" << static_cast<unsigned>(bad->y) << std::dec << '\n';

    BadPoint* zero = new (buffer) BadPoint();
    std::cout << "BadPoint cu (): x = " << zero->x << ", y = " << zero->y << '\n';

    GoodPoint good;
    std::cout << "GoodPoint implicit: x = " << good.getX() << ", y = " << good.getY() << '\n';
    GoodPoint good2(3, 4);
    std::cout << "GoodPoint parametric: x = " << good2.getX() << ", y = " << good2.getY() << '\n';
}

static void demoAssignVsInit()
{
    title("Item 4: Atribuire vs Lista de initializare");

    std::cout << "EntryBody (Atribuire):\n";
    {
        EntryBody entry("Ana", "Timisoara");
        std::cout << "  numTimesConsulted = " << entry.getTimesConsulted() << '\n';
    }

    std::cout << "EntryList (Initializare):\n";
    {
        int counter = 0;
        EntryList entry("Ana", "Timisoara", counter);
        std::cout << "  id = " << entry.getId() << ", numTimesConsulted = " << entry.getTimesConsulted() << '\n';
        std::cout << "  sharedCounter = " << entry.getSharedCounter() << '\n';
    }
}

static void demoOrder()
{
    title("Item 4: Ordinea de initializare");

    std::cout << "OrderDemo:\n";
    {
        OrderDemo demo;
    }

    alignas(BadOrder) unsigned char buffer[sizeof(BadOrder)];
    std::memset(buffer, 0xAB, sizeof(buffer));

    std::cout << "BadOrder(5):\n";
    BadOrder* bad = new (buffer) BadOrder(5);
    std::cout << std::hex << "  a = 0x" << static_cast<unsigned>(bad->getA()) 
              << ", b = 0x" << static_cast<unsigned>(bad->getB()) << std::dec << '\n';

    std::cout << "GoodOrder(5):\n";
    GoodOrder good(5);
    std::cout << "  a = " << good.getA() << ", b = " << good.getB() << '\n';
}

static void demoStaticObjects()
{
    title("Item 4: Obiecte statice (Cross-translation unit)");

    yesNo("tempDirBad a gasit file system gata", tempDirBad.wasFileSystemReady());

    FileSystem& fs1 = tfs();
    FileSystem& fs2 = tfs();
    yesNo("tfs() returneaza acelasi obiect", &fs1 == &fs2);

    Directory good(tfs(), "good");
    yesNo("Directory cu tfs() a gasit file system gata", good.wasFileSystemReady());
}


// Item 5


static void demoGeneratedFunctions()
{
    title("Item 5: Functii generate implicit de compilator");

    Empty e1;
    Empty e2(e1);
    e2 = e1;
    yesNo("Empty: default ctor", std::is_default_constructible<Empty>::value);
    yesNo("Empty: copy ctor", std::is_copy_constructible<Empty>::value);
    yesNo("Empty: copy assignment", std::is_copy_assignable<Empty>::value);

    std::cout << "AutoStudent:\n";
    {
        AutoStudent a;
        AutoStudent b(a);
        AutoStudent c;
        c = a;
    }

    WithCtor w(7);
    std::cout << "WithCtor value = " << w.getValue() << '\n';

    std::cout << "PtrHolder (shallow copy):\n";
    {
        PtrHolder a(10);
        PtrHolder b(a);
        std::cout << "  adresa din a: " << addr(a.getPtr()) << '\n';
        std::cout << "  adresa din b: " << addr(b.getPtr()) << '\n';
        yesNo("PtrHolder a si b impart acelasi pointer", a.getPtr() == b.getPtr());
        *b.getPtr() = 99;
        std::cout << "  valoare prin a: " << *a.getPtr() << '\n';
        delete a.getPtr();
    }

    std::cout << "NamedObject<int>:\n";
    std::string dogName("Persephone");
    NamedObject<int> p(dogName, 2);
    NamedObject<int> c(p);
    std::cout << "  c: name = " << c.getName() << ", value = " << c.getValue() << '\n';

    std::cout << "Move semantics (C++11):\n";
    {
        AutoMove a1;
        AutoMove a2(std::move(a1));
    }
    {
        DtorMove d1;
        DtorMove d2(std::move(d1));
    }
}


// Item 6


static void printHome(const HomeForSale& home)
{
    std::cout << "  casa: " << home.getAddress() << '\n';
}

static void demoDisallow()
{
    title("Item 6: Interzicerea functiilor generate (= delete / private)");

    std::cout << "HomeForSale (= delete):\n";
    HomeForSale h1("Strada Florilor 5");
    HomeForSale h2("Bulevardul Victoriei 10");
    HomeForSale h3;
    printHome(h1);
    printHome(h2);
    printHome(h3);

    std::cout << "HomeForSale98 (private):\n";
    HomeForSale98 old("Strada Veche 1");
    std::cout << "  casa: " << old.getAddress() << '\n';

    std::cout << "Account (Uncopyable base):\n";
    Account account(100.5);
    std::cout << "  sold: " << account.getBalance() << '\n';
}

int main()
{
    demoUninitialized();
    demoAssignVsInit();
    demoOrder();
    demoStaticObjects();
    demoGeneratedFunctions();
    demoDisallow();

    title("Final");
    std::cout << "Executie terminata cu succes.\n";
    return 0;
}