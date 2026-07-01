#ifndef LINUXFACTORY_H
#define LINUXFACTORY_H

#include <memory>
#include "LinuxDistrib.h"
#include "LinuxFactory.h" 

class LinuxFactory {
public:
    static std::unique_ptr<LinuxDistrib> createDistro(DistroType type, int variant = 0);
};

#endif