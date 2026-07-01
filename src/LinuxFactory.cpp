#include "LinuxFactory.h"
#include "DerivedDistribs.h"

std::unique_ptr<LinuxDistrib> LinuxFactory::createDistro(DistroType type, int variant) {
    switch(type) {
        case DistroType::DebianBased:
            if (variant == 0) return std::make_unique<DebianBased>("Ubuntu 24.04", "24.04", "6.8.0", true, "LTS", 75);
            if (variant == 1) return std::make_unique<DebianBased>("Debian 12", "12", "6.1.0", true, "Stable", 85);
            return std::make_unique<DebianBased>("Linux Mint 21", "21.3", "6.5.0", true, "LTS", 80);
        case DistroType::ArchBased:
            if (variant == 0) return std::make_unique<ArchBased>("CachyOS", "24.0", "6.6", false, "Rolling", 45);
            if (variant == 1) return std::make_unique<ArchBased>("Manjaro", "23.1", "6.6", false, "Rolling", 50);
            return std::make_unique<ArchBased>("EndeavourOS", "23", "6.6", false, "Rolling", 48);
        case DistroType::RedHatBased:
            if (variant == 0) return std::make_unique<RedHatBased>("Fedora 40", "40", "6.9", true, "Workstation", 65);
            if (variant == 1) return std::make_unique<RedHatBased>("RHEL 9", "9.3", "5.14", true, "Corporation", 90);
            return std::make_unique<RedHatBased>("CentOS 9", "9", "5.14", true, "Server", 70);
        default:
            return nullptr;
    }
}