#include "int_array.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "heap_counter.h"

int IntArray::nextId_ = 0;

// 3) Initializarea membrilor din constructor: lista de initializare.
//    id_ este const, deci NU poate fi atribuit in corpul constructorului,
//    singura lui sansa de a primi o valoare este lista de initializare.
IntArray::IntArray(std::size_t size, int initialValue)
    : id_(++nextId_), size_(size), data_(new int[size]) {
    ++heapcounter::liveBlocks;
    std::fill(data_, data_ + size_, initialValue);
    std::cout << "[IntArray #" << id_ << "] constructor: am alocat " << size_
              << " int pe heap la " << static_cast<const void*>(data_) << '\n';
}

// 4) Destructorul elibereaza heap-ul. Fara el, fiecare obiect distrus
//    ar lasa in urma un bloc de memorie nefolosit (scurgere de memorie).
IntArray::~IntArray() {
    if (data_ != nullptr) {
        std::cout << "[IntArray #" << id_ << "] destructor: eliberez blocul de " << size_
                  << " int de la " << static_cast<const void*>(data_) << '\n';
        delete[] data_;
        --heapcounter::liveBlocks;
    } else {
        std::cout << "[IntArray #" << id_
                  << "] destructor: nu am nimic de eliberat (continutul a fost mutat)\n";
    }
}

// 5) Copy constructor: fiecare obiect isi primeste propriul bloc pe heap.
//    Fara el, compilatorul copiaza doar pointerul (copie superficiala) si
//    doua obiecte ar folosi acelasi bloc (vezi ShallowArray in bad_examples).
IntArray::IntArray(const IntArray& other)
    : id_(++nextId_), size_(other.size_), data_(new int[other.size_]) {
    ++heapcounter::liveBlocks;
    std::copy(other.data_, other.data_ + size_, data_);
    std::cout << "[IntArray #" << id_ << "] copy constructor: copie profunda din #" << other.id_
              << ", bloc nou la " << static_cast<const void*>(data_) << '\n';
}

// 6) Move constructor: preia pointerul sursei si o lasa goala. Nu se aloca
//    si nu se copiaza nimic, deci e foarte ieftin pentru obiecte temporare.
IntArray::IntArray(IntArray&& other) noexcept
    : id_(++nextId_), size_(other.size_), data_(other.data_) {
    other.size_ = 0;
    other.data_ = nullptr;
    std::cout << "[IntArray #" << id_ << "] move constructor: am preluat blocul de la #"
              << other.id_ << " (" << static_cast<const void*>(data_) << "), fara alocare\n";
}

int IntArray::id() const { return id_; }

std::size_t IntArray::size() const { return size_; }

int IntArray::get(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("index " + std::to_string(index) + " in afara limitelor (size = " +
                                std::to_string(size_) + ")");
    }
    return data_[index];
}

void IntArray::set(std::size_t index, int value) {
    if (index >= size_) {
        throw std::out_of_range("index " + std::to_string(index) + " in afara limitelor (size = " +
                                std::to_string(size_) + ")");
    }
    data_[index] = value;
}

const int* IntArray::data() const { return data_; }

void IntArray::print(const std::string& label) const {
    std::cout << "  " << label << " -> IntArray #" << id_ << ", size = " << size_;
    if (data_ == nullptr) {
        std::cout << ", data = nullptr (obiect gol)\n";
        return;
    }
    std::cout << ", data = " << static_cast<const void*>(data_) << ", continut = {";
    for (std::size_t i = 0; i < size_; ++i) {
        std::cout << (i == 0 ? "" : ", ") << data_[i];
    }
    std::cout << "}\n";
}
