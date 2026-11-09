#include "int_array.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "heap_counter.h"

int IntArray::nextId = 0;

//Initializarea membrilor din constructor: lista de initializare
IntArray::IntArray(std::size_t size, int initialValue): id(++nextId), size(size), data(new int[size]) 
{
    ++heapcounter::liveBlocks;
    std::fill(data, data + size, initialValue);
    std::cout << "[IntArray #" << id << "] constructor: am alocat " << size
              << " int pe heap la " << static_cast<const void*>(data) << '\n';
}

//Destructorul elibereaza heap-ul
IntArray::~IntArray() 
{
    if (data != nullptr) 
    {
        std::cout << "[IntArray #" << id << "] destructor: eliberez blocul de " << size
                  << " int de la " << static_cast<const void*>(data) << '\n';
        delete[] data;
        --heapcounter::liveBlocks;
    } 
    else 
    {
        std::cout << "[IntArray #" << id
                  << "] destructor: nu am nimic de eliberat (continutul a fost mutat)\n";
    }
}

//Copy constructor: fiecare obiect isi primeste propriul bloc pe heap
IntArray::IntArray(const IntArray& other): id(++nextId), size(other.size), data(new int[other.size]) 
{
    ++heapcounter::liveBlocks;
    std::copy(other.data, other.data + size, data);
    std::cout << "[IntArray #" << id << "] copy constructor: copie profunda din #" << other.id
              << ", bloc nou la " << static_cast<const void*>(data) << '\n';
}

//Move constructor: preia pointerul sursei si o lasa goala
IntArray::IntArray(IntArray&& other) noexcept: id(++nextId), size(other.size), data(other.data) 
{
    other.size = 0;
    other.data = nullptr;
    std::cout << "[IntArray #" << id << "] move constructor: am preluat blocul de la #"
              << other.id << " (" << static_cast<const void*>(data) << "), fara alocare\n";
}

int IntArray::getId() const { return id; }

std::size_t IntArray::getSize() const { return size; }

int IntArray::get(std::size_t index) const 
{
    if (index >= size) 
    {
        throw std::out_of_range("index " + std::to_string(index) + " in afara limitelor (size = " +
                                std::to_string(size) + ")");
    }
    return data[index];
}

void IntArray::set(std::size_t index, int value) 
{
    if (index >= size) 
    {
        throw std::out_of_range("index " + std::to_string(index) + " in afara limitelor (size = " +
                                std::to_string(size) + ")");
    }
    data[index] = value;
}

const int* IntArray::getData() const { return data; }

void IntArray::print(const std::string& label) const
{
    std::cout << "  " << label << " -> IntArray #" << id << ", size = " << size;
    if (data == nullptr) 
    {
        std::cout << ", data = nullptr (obiect gol)\n";
        return;
    }
    std::cout << ", data = " << static_cast<const void*>(data) << ", continut = {";
    for (std::size_t i = 0; i < size; ++i) 
    {
        std::cout << (i == 0 ? "" : ", ") << data[i];
    }
    std::cout << "}\n";
}