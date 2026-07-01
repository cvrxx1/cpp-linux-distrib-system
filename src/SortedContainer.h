#ifndef SORTEDCONTAINER_H
#define SORTEDCONTAINER_H

#include <vector>
#include <memory>
#include "LinuxDistrib.h"

using namespace std;

class SortedContainer {
private:
    std::vector<std::unique_ptr<LinuxDistrib>> data;
    
    // Вспомогательная функция для поиска позиции вставки
    int findInsertPosition(LinuxDistrib* distro) const;
    
public:
    // Вложенный класс итератора (такой же как в Container)
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
    
    // Методы контейнера (тот же интерфейс)
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