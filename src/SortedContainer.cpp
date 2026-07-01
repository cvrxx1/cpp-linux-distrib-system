#include "SortedContainer.h"
#include <algorithm>

// ========== Iterator implementation ==========
SortedContainer::Iterator::Iterator(std::vector<std::unique_ptr<LinuxDistrib>>::iterator iter)
    : it(iter) {}

SortedContainer::Iterator& SortedContainer::Iterator::operator++() {
    ++it;
    return *this;
}

SortedContainer::Iterator SortedContainer::Iterator::operator++(int) {
    Iterator temp = *this;
    ++it;
    return temp;
}

bool SortedContainer::Iterator::operator!=(const Iterator& other) const {
    return it != other.it;
}

bool SortedContainer::Iterator::operator==(const Iterator& other) const {
    return it == other.it;
}

LinuxDistrib* SortedContainer::Iterator::operator*() const {
    return it->get();
}

// ========== SortedContainer implementation ==========
int SortedContainer::findInsertPosition(LinuxDistrib* distro) const {
    for (size_t i = 0; i < data.size(); i++) {
        if (*data[i] > *distro) {  // используем operator>
            return i;
        }
    }
    return data.size();
}

void SortedContainer::add(std::unique_ptr<LinuxDistrib> distro) {
    // Вставляем в отсортированном порядке
    int pos = findInsertPosition(distro.get());
    data.insert(data.begin() + pos, std::move(distro));
    
    cout << " [SortedContainer] Вставка на позицию " << pos << endl;
}

size_t SortedContainer::size() const {
    return data.size();
}

void SortedContainer::clear() {
    data.clear();
}

std::unique_ptr<SortedContainer::Iterator> SortedContainer::begin() {
    return std::make_unique<Iterator>(data.begin());
}

std::unique_ptr<SortedContainer::Iterator> SortedContainer::end() {
    return std::make_unique<Iterator>(data.end());
}

std::vector<LinuxDistrib*> SortedContainer::getRawPointers() const {
    std::vector<LinuxDistrib*> rawPtrs;
    for (const auto& d : data) {
        rawPtrs.push_back(d.get());
    }
    return rawPtrs;
}