#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <memory>
#include "LinuxDistrib.h"

class Container {
private:
    std::vector<std::unique_ptr<LinuxDistrib>> data;
    
public:
    // Вложенный класс итератора
    class Iterator {
    private:
        std::vector<std::unique_ptr<LinuxDistrib>>::iterator it;
    public:
        Iterator(std::vector<std::unique_ptr<LinuxDistrib>>::iterator iter);
        
        Iterator& operator++();
        Iterator operator++(int);
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        LinuxDistrib* operator*() const;
    };
    
    // Методы контейнера
    void add(std::unique_ptr<LinuxDistrib> distro);
    size_t size() const;
    void clear();
    
    // Возврат итераторов через unique_ptr<>
    std::unique_ptr<Iterator> begin();
    std::unique_ptr<Iterator> end();
    
    // Для доступа к сырым указателям (для сортировки/поиска)
    std::vector<LinuxDistrib*> getRawPointers() const;
};

#endif