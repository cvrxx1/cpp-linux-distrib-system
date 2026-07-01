#include "Container.h"
#include <algorithm>

// ========== Iterator implementation ==========
Container::Iterator::Iterator(std::vector<std::unique_ptr<LinuxDistrib>>::iterator iter)
    : it(iter) {}

Container::Iterator& Container::Iterator::operator++() {
    ++it;
    return *this;
}

Container::Iterator Container::Iterator::operator++(int) {
    Iterator temp = *this;
    ++it;
    return temp;
}

bool Container::Iterator::operator!=(const Iterator& other) const {
    return it != other.it;
}

bool Container::Iterator::operator==(const Iterator& other) const {
    return it == other.it;
}

LinuxDistrib* Container::Iterator::operator*() const {
    return it->get();
}

// ========== Container implementation ==========
void Container::add(std::unique_ptr<LinuxDistrib> distro) {
    data.push_back(std::move(distro));
}

size_t Container::size() const {
    return data.size();
}

void Container::clear() {
    data.clear();
}

std::unique_ptr<Container::Iterator> Container::begin() {
    return std::make_unique<Iterator>(data.begin());
}

std::unique_ptr<Container::Iterator> Container::end() {
    return std::make_unique<Iterator>(data.end());
}

std::vector<LinuxDistrib*> Container::getRawPointers() const {
    std::vector<LinuxDistrib*> rawPtrs;
    for (const auto& d : data) {
        rawPtrs.push_back(d.get());
    }
    return rawPtrs;
}