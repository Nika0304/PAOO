// Tema 3 - incapsulare, lista de initializare, destructor, copy constructor, move constructor.
//
// Rulare:
//   ./app                 -> toate demonstratiile, fara crash
//   ./app --double-free   -> scenariul care chiar se opreste cu eroare (lipsa copy constructor)

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "bad_examples.h"
#include "heap_counter.h"
#include "int_array.h"

static void title(const std::string& text) {
    std::cout << "\n==================== " << text << " ====================\n";
}

static void liveBlocks(const std::string& when) {
    std::cout << "  >> blocuri alocate pe heap " << when << ": " << heapcounter::liveBlocks << '\n';
}

// Primeste obiectul PRIN VALOARE, deci apare o copie (se apeleaza copy constructorul).
static void modifyCopy(IntArray copy) {
    copy.set(0, -1);
    copy.print("in functie (copia)");
}

// ---------------------------------------------------------------------------
// 2) + 3) Incapsulare si initializarea membrilor din constructor
// ---------------------------------------------------------------------------
static void demoEncapsulationAndInit() {
    title("2) + 3) Incapsulare si initializare din constructor");

    IntArray a(5, 7);  // constructorul initializeaza id_, size_, data_ din lista de initializare
    a.print("a");

    a.set(2, 42);
    a.print("a dupa set(2, 42)");

    // Membrii sunt privati: urmatoarea linie nu compileaza, deci nu putem strica
    // starea obiectului din exterior.
    //   a.data_[100] = 1;   // eroare: 'data_' is private

    // Singura cale de acces este interfata publica, care verifica indexul:
    try {
        a.set(10, 1);
    } catch (const std::out_of_range& e) {
        std::cout << "  acces respins de interfata publica: " << e.what() << '\n';
    }
}

// ---------------------------------------------------------------------------
// 4) Eliberarea heap-ului in destructor
// ---------------------------------------------------------------------------
static void demoDestructor() {
    title("4) Destructorul elibereaza heap-ul");

    std::cout << "\n-- Varianta corecta (IntArray are destructor) --\n";
    liveBlocks("inainte");
    {
        IntArray scoped(3);
        liveBlocks("cat timp obiectul exista");
    }  // aici se apeleaza destructorul
    liveBlocks("dupa iesirea din scope");

    std::cout << "\n-- Varianta gresita (LeakyArray nu are destructor) --\n";
    int* rescue = nullptr;
    {
        LeakyArray leaky(4);
        rescue = leaky.rawPointerForDemo();  // pastram adresa doar ca sa curatam dupa demo
    }  // obiectul dispare, dar nimeni nu face delete[]
    liveBlocks("dupa iesirea din scope");
    std::cout << "  >> SCURGERE DE MEMORIE: obiectul nu mai exista, dar blocul lui a ramas pe heap\n";

    delete[] rescue;  // curatenie manuala, numai pentru ca demonstratia sa nu lase scurgeri reale
    --heapcounter::liveBlocks;
    liveBlocks("dupa curatenia manuala");
}

// ---------------------------------------------------------------------------
// 5) Copy constructor
// ---------------------------------------------------------------------------
static void demoCopyConstructor() {
    title("5) Copy constructor");

    std::cout << "\n-- Fara copy constructor (ShallowArray: copiaza doar pointerul) --\n";
    {
        ShallowArray a(3, 1);
        ShallowArray b = a;  // copy constructor generat de compilator: copiaza pointerul
        std::cout << "  a.data() = " << static_cast<const void*>(a.data())
                  << ", b.data() = " << static_cast<const void*>(b.data()) << '\n';
        std::cout << "  acelasi bloc de pe heap? " << (a.data() == b.data() ? "DA" : "NU") << '\n';

        b.set(0, 99);
        std::cout << "  am modificat doar b[0] = 99, dar a[0] = " << a.get(0) << " (a s-a stricat!)\n";

        std::cout << "  La iesirea din scope ar fi apelat destructorul si pentru a, si pentru b:\n"
                  << "  ambele ar face delete[] pe acelasi bloc => double free (crash).\n"
                  << "  Aici renunt la b ca sa nu se opreasca programul; pentru crash real: ./app --double-free\n";
        b.abandon();
    }

    std::cout << "\n-- Cu copy constructor (IntArray: copie profunda) --\n";
    {
        IntArray a(3, 1);
        IntArray b = a;  // se apeleaza copy constructorul definit de noi
        a.print("a");
        b.print("b");
        std::cout << "  acelasi bloc de pe heap? " << (a.data() == b.data() ? "DA" : "NU") << '\n';

        b.set(0, 99);
        std::cout << "  am modificat doar b[0] = 99, a[0] = " << a.get(0) << " (a ramane intact)\n";
    }

    std::cout << "\n-- Copie facuta la pasarea prin valoare intr-o functie --\n";
    {
        IntArray a(3, 5);
        a.print("a inainte");
        modifyCopy(a);  // functia lucreaza pe o copie; la return, copia este distrusa
        a.print("a dupa");
    }
}

// ---------------------------------------------------------------------------
// 6) Move constructor
// ---------------------------------------------------------------------------
static void demoMoveConstructor() {
    title("6) Move constructor");

    std::cout << "\n-- std::move pe un obiect existent --\n";
    {
        IntArray a(4, 5);
        a.print("a inainte de mutare");
        IntArray b = std::move(a);  // se apeleaza move constructorul
        a.print("a dupa mutare");
        b.print("b dupa mutare");
        std::cout << "  blocul de pe heap a fost preluat, nu copiat (acelasi pointer, nicio alocare noua)\n";
    }

    std::cout << "\n-- Obiect temporar adaugat intr-un std::vector --\n";
    {
        std::vector<IntArray> v;
        // IntArray(3, 9) este un temporar care oricum dispare imediat. Cu move constructor
        // i se preia blocul; fara el s-ar face o copie profunda (alocare + copiere) degeaba.
        v.push_back(IntArray(3, 9));
        v[0].print("v[0]");
    }
}

// ---------------------------------------------------------------------------
// Scenariul care se opreste cu eroare: lipsa copy constructorului => double free
// ---------------------------------------------------------------------------
static void runDoubleFree() {
    title("double free (lipsa copy constructor)");
    std::cout << "Urmeaza doua destructoare pe acelasi bloc. Programul se va opri cu eroare.\n";
    ShallowArray a(3, 1);
    ShallowArray b = a;  // copie superficiala: a si b arata spre acelasi bloc
    (void)b;
}  // iesire din functie: ~b face delete[], apoi ~a face delete[] pe aceeasi adresa

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--double-free") {
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
