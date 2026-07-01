#include "DerivedDistribs.h"
#include "InstallStrategies.h"
#include <iostream>

// ========== DebianBased ==========
DebianBased::DebianBased(std::string n, std::string v, std::string kernel, 
                         bool stable, std::string cycle, int score)
    : LinuxDistrib(n, v, kernel, stable, "APT (dpkg)", score), release_cycle(cycle) {
    installStrategy = std::make_unique<AptStrategy>();
}

DebianBased::DebianBased(const DebianBased& other)
    : LinuxDistrib(other.name, other.version, other.kernel_version, 
                   other.is_stable, other.package_manager, other.stability_score),
      release_cycle(other.release_cycle) {
    if (other.installStrategy) {
        installStrategy = std::unique_ptr<InstallStrategy>(other.installStrategy->clone());
    }
    std::cout << "[COPY] DebianBased: " << name << std::endl;
}

std::unique_ptr<LinuxDistrib> DebianBased::copy() const {
    return std::make_unique<DebianBased>(*this);
}

void DebianBased::do_update() {
    std::cout << "  [3][Debian] Обновление через APT с проверкой зависимостей" << std::endl;
    if (installStrategy) {
        installStrategy->update();
    }
}

void DebianBased::reboot_if_needed() {
    if (release_cycle == "LTS") {
        std::cout << "  [5][Debian LTS] Ядро обновлено, рекомендуется перезагрузка" << std::endl;
    } else {
        std::cout << "  [5][Debian] Перезагрузка не требуется" << std::endl;
    }
}

// ========== ArchBased ==========
ArchBased::ArchBased(std::string n, std::string v, std::string kernel, 
                     bool stable, std::string model, int score)
    : LinuxDistrib(n, v, kernel, stable, "Pacman", score), update_model(model) {
    installStrategy = std::make_unique<PacmanStrategy>();
}

ArchBased::ArchBased(const ArchBased& other)
    : LinuxDistrib(other.name, other.version, other.kernel_version, 
                   other.is_stable, other.package_manager, other.stability_score),
      update_model(other.update_model) {
    if (other.installStrategy) {
        installStrategy = std::unique_ptr<InstallStrategy>(other.installStrategy->clone());
    }
    std::cout << "[COPY] ArchBased: " << name << std::endl;
}

std::unique_ptr<LinuxDistrib> ArchBased::copy() const {
    return std::make_unique<ArchBased>(*this);
}

void ArchBased::do_update() {
    std::cout << "  [3][Arch] Полное обновление системы (rolling release)" << std::endl;
    if (installStrategy) {
        installStrategy->update();
    }
}

// ========== RedHatBased ==========
RedHatBased::RedHatBased(std::string n, std::string v, std::string kernel, 
                         bool stable, std::string audience, int score)
    : LinuxDistrib(n, v, kernel, stable, "RPM (DNF/YUM)", score), target_audience(audience) {
    installStrategy = std::make_unique<DnfStrategy>();
}

RedHatBased::RedHatBased(const RedHatBased& other)
    : LinuxDistrib(other.name, other.version, other.kernel_version, 
                   other.is_stable, other.package_manager, other.stability_score),
      target_audience(other.target_audience) {
    if (other.installStrategy) {
        installStrategy = std::unique_ptr<InstallStrategy>(other.installStrategy->clone());
    }
    std::cout << "[COPY] RedHatBased: " << name << std::endl;
}

std::unique_ptr<LinuxDistrib> RedHatBased::copy() const {
    return std::make_unique<RedHatBased>(*this);
}

void RedHatBased::do_update() {
    std::cout << "  [3][RedHat] Обновление с проверкой совместимости" << std::endl;
    if (installStrategy) {
        installStrategy->update();
    }
}

void RedHatBased::reboot_if_needed() {
    if (target_audience == "Server") {
        std::cout << "  [5][RedHat Server] Обновление ядра, требуется перезагрузка" << std::endl;
    } else {
        std::cout << "  [5][RedHat] Перезагрузка не требуется" << std::endl;
    }
}