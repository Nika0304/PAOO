#include "bad_examples.h"

#include <algorithm>
#include <iostream>

#include "heap_counter.h"

// ---------- LeakyArray ----------

LeakyArray::LeakyArray(std::size_t size) : size_(size), data_(new int[size]) {
    ++heapcounter::liveBlocks;
    std::fill(data_, data_ + size_, 0);
    std::cout << "[LeakyArray] constructor: am alocat " << size_ << " int pe heap la "
              << static_cast<const void*>(data_) << '\n';
}

int* LeakyArray::rawPointerForDemo() const { return data_; }

// ---------- ShallowArray ----------

ShallowArray::ShallowArray(std::size_t size, int initialValue) : size_(size), data_(new int[size]) {
    ++heapcounter::liveBlocks;
    std::fill(data_, data_ + size_, initialValue);
    std::cout << "[ShallowArray] constructor: am alocat " << size_ << " int pe heap la "
              << static_cast<const void*>(data_) << '\n';
}

ShallowArray::~ShallowArray() {
    if (data_ != nullptr) {
        // std::endl forteaza afisarea imediata, ca mesajul sa apara chiar daca
        // programul se opreste brusc la un double free.
        std::cout << "[ShallowArray] destructor: delete[] la " << static_cast<const void*>(data_)
                  << std::endl;
        delete[] data_;
        --heapcounter::liveBlocks;
    }
}

std::size_t ShallowArray::size() const { return size_; }

int ShallowArray::get(std::size_t index) const { return data_[index]; }

void ShallowArray::set(std::size_t index, int value) { data_[index] = value; }

const int* ShallowArray::data() const { return data_; }

void ShallowArray::abandon() {
    data_ = nullptr;
    size_ = 0;
}
