#include "bad_examples.h"

#include <algorithm>
#include <iostream>

#include "heap_counter.h"

//LeakyArray
LeakyArray::LeakyArray(std::size_t size) : size(size), data(new int[size]) 
{
    ++heapcounter::liveBlocks;
    std::fill(data, data + size, 0);
    std::cout << "[LeakyArray] constructor: am alocat " << size << " int pe heap la "
              << static_cast<const void*>(data) << '\n';
}

int* LeakyArray::rawPointerForDemo() const { return data; }

//ShallowArray
ShallowArray::ShallowArray(std::size_t size, int initialValue) : size(size), data(new int[size]) 
{
    ++heapcounter::liveBlocks;
    std::fill(data, data + size, initialValue);
    std::cout << "[ShallowArray] constructor: am alocat " << size << " int pe heap la "
              << static_cast<const void*>(data) << '\n';
}

ShallowArray::~ShallowArray() 
{
    if (data != nullptr) 
    {
        // std::endl forteaza afisarea imediata, ca mesajul sa apara chiar daca
        // programul se opreste brusc la un double free.
        std::cout << "[ShallowArray] destructor: delete[] la " << static_cast<const void*>(data)
                  << std::endl;
        delete[] data;
        --heapcounter::liveBlocks;
    }
}

std::size_t ShallowArray::getSize() const { return size; }

int ShallowArray::get(std::size_t index) const { return data[index]; }

void ShallowArray::set(std::size_t index, int value) { data[index] = value; }

const int* ShallowArray::getData() const { return data; }

void ShallowArray::abandon() 
{
    data = nullptr;
    size = 0;
}
