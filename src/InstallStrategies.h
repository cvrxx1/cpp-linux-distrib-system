#ifndef INSTALLSTRATEGIES_H
#define INSTALLSTRATEGIES_H

#include "InstallStrategy.h"
#include <memory>
#include <iostream>

// Стратегия для Debian-подобных (apt)
class AptStrategy : public InstallStrategy {
public:
    void install(const std::string& programName) const override {
        std::cout << "  [APT] sudo apt install " << programName << std::endl;
    }
    
    void update() const override {
        std::cout << "  [APT] sudo apt update && sudo apt upgrade" << std::endl;
    }
    
    InstallStrategy* clone() const override {
        return new AptStrategy(*this);
    }
};

// Стратегия для Arch-подобных (pacman)
class PacmanStrategy : public InstallStrategy {
public:
    void install(const std::string& programName) const override {
        std::cout << "  [PACMAN] sudo pacman -S " << programName << std::endl;
    }
    
    void update() const override {
        std::cout << "  [PACMAN] sudo pacman -Syu" << std::endl;
    }
    
    InstallStrategy* clone() const override {
        return new PacmanStrategy(*this);
    }
};

// Стратегия для RedHat-подобных (dnf)
class DnfStrategy : public InstallStrategy {
public:
    void install(const std::string& programName) const override {
        std::cout << "  [DNF] sudo dnf install " << programName << std::endl;
    }
    
    void update() const override {
        std::cout << "  [DNF] sudo dnf update" << std::endl;
    }
    
    InstallStrategy* clone() const override {
        return new DnfStrategy(*this);
    }
};

#endif