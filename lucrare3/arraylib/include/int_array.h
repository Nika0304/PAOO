#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <cstddef>
#include <string>

// vector de int-uri alocat pe heap
// varianta corecta: are constructor cu lista de initializare, destructor,
// copy constructor si move constructor
class IntArray
{
public:
    explicit IntArray(std::size_t size, int initialValue = 0);  // constructor
    ~IntArray();                                                 // destructor: elibereaza blocul de pe heap
    IntArray(const IntArray& other);                             // copy constructor: copie profunda, aloca bloc nou
    IntArray(IntArray&& other) noexcept;                         // move constructor: ia blocul de la sursa, fara alocare

    // atribuirea nu e ceruta in tema, o interzic ca sa nu apara din greseala o copie superficiala cu a = b
    IntArray& operator=(const IntArray&) = delete;
    IntArray& operator=(IntArray&&) = delete;

    // interfata publica: membrii sunt privati, deci accesul se face doar prin metodele astea
    int getId() const;
    std::size_t getSize() const;
    int get(std::size_t index) const;        // arunca out_of_range daca indexul e prea mare
    void set(std::size_t index, int value);  // arunca out_of_range daca indexul e prea mare
    const int* getData() const;              // doar pentru citire, il folosesc ca sa compar adresele
    void print(const std::string& label) const;

private:
    // membrii se initializeaza in ordinea in care sunt declarati aici
    static int nextId;  // o singura copie pentru toata clasa, de aici iau id-urile
    const int id;       // const, deci poate fi setat doar in lista de initializare
    std::size_t size;   // cate elemente are
    int* data;          // pointer catre blocul de pe heap
};

#endif
