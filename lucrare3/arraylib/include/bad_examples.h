#ifndef BAD_EXAMPLES_H
#define BAD_EXAMPLES_H

#include <cstddef>

// ATENTIE: clasele de mai jos sunt scrise GRESIT, intentionat, ca sa se vada
// ce se intampla cand lipsesc destructorul sau copy constructorul.

// Fara destructor: blocul alocat cu new[] nu este eliberat niciodata.
class LeakyArray {
public:
    explicit LeakyArray(std::size_t size);
    // (nu exista ~LeakyArray)

    int* rawPointerForDemo() const;  // doar ca sa putem face curatenie dupa demo

private:
    std::size_t size_;
    int* data_;
};

// Are destructor, dar NU are copy constructor. Cel generat de compilator copiaza
// doar pointerul, deci doua obiecte ajung sa arate spre acelasi bloc de pe heap.
class ShallowArray {
public:
    explicit ShallowArray(std::size_t size, int initialValue = 0);
    ~ShallowArray();
    // (nu exista ShallowArray(const ShallowArray&))

    std::size_t size() const;
    int get(std::size_t index) const;
    void set(std::size_t index, int value);
    const int* data() const;

    // Doar pentru demo: renunta la bloc fara sa-l elibereze, ca sa nu apara
    // double free in varianta "sigura" a demonstratiei.
    void abandon();

private:
    std::size_t size_;
    int* data_;
};

#endif  // BAD_EXAMPLES_H
