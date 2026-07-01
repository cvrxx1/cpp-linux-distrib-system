#ifndef ITERATORDECORATORS_H
#define ITERATORDECORATORS_H

#include "LinuxDistrib.h"
#include "DerivedDistribs.h"

// ДЕКОРАТОР 1: Фильтр по минимальной стабильности
template<typename BaseIterator>
class StabilityFilterIterator {
private:
    BaseIterator it;
    BaseIterator end_it;
    int minStability;
    
    void skipToNextValid() {
        while (it != end_it && (*it)->get_stability_score() < minStability) {
            ++it;
        }
    }
    
public:
    StabilityFilterIterator(BaseIterator begin, BaseIterator end, int minStab)
        : it(begin), end_it(end), minStability(minStab) {
        skipToNextValid();
    }
    
    StabilityFilterIterator& operator++() {
        ++it;
        skipToNextValid();
        return *this;
    }
    
    bool operator!=(const StabilityFilterIterator& other) const {
        return it != other.it;
    }
    
    LinuxDistrib* operator*() const {
        return *it;
    }
};

// ДЕКОРАТОР 2: Фильтр по семейству (типу дистрибутива)
template<typename BaseIterator>
class TypeFilterIterator {
private:
    BaseIterator it;
    BaseIterator end_it;
    DistroType targetType;
    
    void skipToNextValid() {
        while (it != end_it) {
            LinuxDistrib* distro = *it;
            
            // Определяем тип дистрибутива
            if (dynamic_cast<DebianBased*>(distro) && targetType == DistroType::DebianBased) {
                break;
            }
            if (dynamic_cast<ArchBased*>(distro) && targetType == DistroType::ArchBased) {
                break;
            }
            if (dynamic_cast<RedHatBased*>(distro) && targetType == DistroType::RedHatBased) {
                break;
            }
            ++it;
        }
    }
    
public:
    TypeFilterIterator(BaseIterator begin, BaseIterator end, DistroType type)
        : it(begin), end_it(end), targetType(type) {
        skipToNextValid();
    }
    
    TypeFilterIterator& operator++() {
        ++it;
        skipToNextValid();
        return *this;
    }
    
    bool operator!=(const TypeFilterIterator& other) const {
        return it != other.it;
    }
    
    LinuxDistrib* operator*() const {
        return *it;
    }
};

#endif