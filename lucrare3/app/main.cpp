// Tema 3 - incapsulare, lista de initializare, destructor, copy constructor, move constructor
// Rulare normala: ./app/app
// Pentru crash cu double free: ./app/app --double-free

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "bad_examples.h"
#include "heap_counter.h"
#include "int_array.h"

// afiseaza un titlu pentru fiecare sectiune
static void title(const std::string& text)
{
    std::cout << "\n " << text << " \n";
}


// afiseaza cate blocuri sunt acum pe heap
static void liveBlocks(const std::string& when)
{
    std::cout << "  >> blocuri pe heap " << when << ": " << heapcounter::liveBlocks << '\n';
}

// parametrul e luat prin valoare, deci se face o copie (copy constructor)
static void modifyCopy(IntArray copy)
{
    copy.set(0, -1);
    copy.print("in functie (copia)");
}

// incapsulare si lista de initializare
static void demoEncapsulationAndInit()
{
    title("Incapsulare si initializare din constructor");

    IntArray a(5, 7);  // constructorul seteaza id, size si data
    a.print("a");

    a.set(2, 42);
    a.print("a dupa set(2, 42)");

    // membrii sunt privati, deci linia de mai jos nu compileaza
    // a.data[100] = 1;

    // accesul se face doar prin metode, care verifica indexul
    try
    {
        a.set(10, 1);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "  eroare prinsa: " << e.what() << '\n';
    }
}

// destructorul elibereaza heap-ul
static void demoDestructor()
{
    title("Destructorul elibereaza heap-ul");

    std::cout << "\nVarianta corecta (IntArray are destructor)\n";
    liveBlocks("inainte");
    {
        IntArray scoped(3);
        liveBlocks("cat timp exista obiectul");
    }  // aici se apeleaza destructorul
    liveBlocks("dupa ce obiectul a iesit din scope");

    std::cout << "\nVarianta gresita (LeakyArray nu are destructor)\n";
    int* rescue = nullptr;
    {
        LeakyArray leaky(4);
        rescue = leaky.rawPointerForDemo();  // salvez adresa ca sa pot sterge blocul dupa
    }  // obiectul dispare, dar blocul ramane pe heap
    liveBlocks("dupa ce obiectul a iesit din scope");
    std::cout << "  SCURGERE DE MEMORIE: obiectul a disparut, dar blocul a ramas pe heap\n";

    delete[] rescue;  // il sterg manual ca sa nu ramana scurgere adevarata
    --heapcounter::liveBlocks;
    liveBlocks("dupa stergerea manuala");
}

// copy constructor
static void demoCopyConstructor()
{
    title("Copy constructor");

    std::cout << "\nFara copy constructor (ShallowArray copiaza doar pointerul)\n";
    {
        ShallowArray a(3, 1);
        ShallowArray b = a;  // copy constructorul facut de compilator copiaza doar pointerul
        std::cout << "  adresa lui a: " << static_cast<const void*>(a.getData()) << '\n';
        std::cout << "  adresa lui b: " << static_cast<const void*>(b.getData()) << '\n';
        std::cout << "  a si b arata spre acelasi bloc? " << (a.getData() == b.getData() ? "DA" : "NU") << '\n';

        b.set(0, 99);
        std::cout << "  schimb b[0] = 99 si a[0] a devenit " << a.get(0) << '\n';

        std::cout << "  la final ambele obiecte ar sterge acelasi bloc (double free)\n"
                  << "  de aceea renunt la b aici; crash-ul real: ./app/app --double-free\n";
        b.abandon();  // b nu mai arata spre bloc, deci nu se mai sterge de doua ori
    }

    std::cout << "\nCu copy constructor (IntArray face copie profunda)\n";
    {
        IntArray a(3, 1);
        IntArray b = a;  // aici se apeleaza copy constructorul meu
        a.print("a");
        b.print("b");
        std::cout << "  a si b arata spre acelasi bloc? " << (a.getData() == b.getData() ? "DA" : "NU") << '\n';

        b.set(0, 99);
        std::cout << "  schimb b[0] = 99 si a[0] a ramas " << a.get(0) << '\n';
    }

    std::cout << "\nCopie facuta la pasarea prin valoare intr-o functie\n";
    {
        IntArray a(3, 5);
        a.print("a inainte");
        modifyCopy(a);  // functia lucreaza pe o copie, care se distruge la return
        a.print("a dupa");
    }
}

// move constructor
static void demoMoveConstructor()
{
    title("Move constructor");

    std::cout << "\nstd::move pe un obiect existent\n";
    {
        IntArray a(4, 5);
        a.print("a inainte de mutare");
        IntArray b = std::move(a);  // se apeleaza move constructorul
        a.print("a dupa mutare");
        b.print("b dupa mutare");
        std::cout << "  blocul a fost luat, nu copiat (aceeasi adresa, fara alocare noua)\n";
    }

    std::cout << "\nObiect temporar adaugat intr-un vector\n";
    {
        std::vector<IntArray> v;
        // IntArray(3, 9) e un obiect temporar care dispare oricum imediat,
        // deci in loc sa-l copiem ii luam blocul cu move constructorul
        v.push_back(IntArray(3, 9));
        v[0].print("v[0]");
    }
}

// scenariul care se opreste cu eroare: fara copy constructor apare double free
static void runDoubleFree()
{
    title("Double free (lipseste copy constructorul)");
    std::cout << "Urmeaza doua destructoare pe acelasi bloc, programul se va opri cu eroare.\n";
    ShallowArray a(3, 1);
    ShallowArray b = a;  // copie superficiala, a si b arata spre acelasi bloc
    (void)b;             // ca sa nu dea warning ca b nu e folosit
}  // aici se apeleaza destructorul pentru b si pentru a, deci doua delete[] pe aceeasi adresa

int main(int argc, char* argv[])
{
    // daca pornesc programul cu --double-free, ruleaza doar scenariul cu crash
    if (argc > 1 && std::string(argv[1]) == "--double-free")
    {
        runDoubleFree();
        return 0;
    }

    demoEncapsulationAndInit();
    demoDestructor();
    demoCopyConstructor();
    demoMoveConstructor();

    title("Final");
    liveBlocks("la sfarsitul programului");
    std::cout << (heapcounter::liveBlocks == 0 ? "  Toata memoria a fost eliberata.\n"
                                               : "  ATENTIE: exista scurgeri de memorie!\n");
    return 0;
}
