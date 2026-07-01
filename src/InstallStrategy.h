#ifndef INSTALLSTRATEGY_H
#define INSTALLSTRATEGY_H

#include <string>
#include <iostream>

// Интерфейс стратегии установки
class InstallStrategy {
public:
    virtual ~InstallStrategy() = default;
    virtual void install(const std::string& programName) const = 0;
    virtual void update() const = 0;
    virtual InstallStrategy* clone() const = 0;
};

#endif