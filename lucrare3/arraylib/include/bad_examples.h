#ifndef BAD_EXAMPLES_H
#define BAD_EXAMPLES_H

#include <cstddef>

//clasele de mai jos sunt scrise GRESIT, intentionat

// Fara destructor: blocul alocat cu new[] nu este eliberat niciodata.
class LeakyArray 
{
public:
    explicit LeakyArray(std::size_t size);
    // (nu exista ~LeakyArray)

    int* rawPointerForDemo() const;  // doar ca sa putem face curatenie dupa demo

private:
    std::size_t size;
    int* data;
};

//are constructor și destructor, dar nu are copy constructor => două obiecte pe același bloc
class ShallowArray 
{
public:
    explicit ShallowArray(std::size_t size, int initialValue = 0);
    ~ShallowArray();
    

    std::size_t getSize() const;
    int get(std::size_t index) const;
    void set(std::size_t index, int value);
    const int* getData() const;

    // Doar pentru demo: renunta la bloc fara sa-l elibereze, ca sa nu apara double free in varianta "sigura" a demonstratiei
    void abandon();

private:
    std::size_t size;
    int* data;
};

#endif  
