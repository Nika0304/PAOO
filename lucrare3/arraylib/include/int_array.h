#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <cstddef>
#include <string>

// Vector de int-uri alocat pe heap. Varianta CORECTA: are constructor cu lista
// de initializare, destructor, copy constructor si move constructor.
class IntArray {
public:
    // Constructor. Foloseste lista de initializare (vezi int_array.cpp).
    explicit IntArray(std::size_t size, int initialValue = 0);

    // Destructor: elibereaza blocul de pe heap.
    ~IntArray();

    // Copy constructor: copie "profunda" (aloca un bloc nou si copiaza continutul).
    IntArray(const IntArray& other);

    // Move constructor: "fura" blocul de pe heap de la obiectul sursa, fara alocare.
    IntArray(IntArray&& other) noexcept;

    // Operatorii de atribuire nu fac parte din tema; ii interzicem ca sa nu
    // apara din greseala o copie superficiala prin "a = b".
    IntArray& operator=(const IntArray&) = delete;
    IntArray& operator=(IntArray&&) = delete;

    // Interfata publica (incapsulare): membrii sunt privati, accesul se face
    // doar prin aceste metode, care verifica indexul.
    int id() const;
    std::size_t size() const;
    int get(std::size_t index) const;            // arunca std::out_of_range
    void set(std::size_t index, int value);      // arunca std::out_of_range
    const int* data() const;                     // doar citire, folosit pentru a compara adrese in demo
    void print(const std::string& label) const;

private:
    // Ordinea declararii = ordinea in care se initializeaza membrii,
    // indiferent de ordinea din lista de initializare.
    static int nextId_;
    const int id_;       // const => poate fi setat NUMAI in lista de initializare
    std::size_t size_;
    int* data_;
};

#endif  // INT_ARRAY_H
