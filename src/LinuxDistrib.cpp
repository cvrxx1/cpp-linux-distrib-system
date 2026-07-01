#include "LinuxDistrib.h"

LinuxDistrib::LinuxDistrib(std::string n, std::string v, std::string kernel, 
                           bool stable, std::string pm, int score)
    : name(n), version(v), kernel_version(kernel), is_stable(stable), 
      package_manager(pm), stability_score(score), installStrategy(nullptr) {}

LinuxDistrib::~LinuxDistrib() {}

void LinuxDistrib::install_program(const std::string& prog_name) {
    std::cout << name << ": ";
    if (installStrategy) {
        installStrategy->install(prog_name);
    } else {
        std::cout << "Нет стратегии установки!" << std::endl;
    }
}

void LinuxDistrib::update_system() {
    std::cout << name << ": ";
    if (installStrategy) {
        installStrategy->update();
    } else {
        std::cout << "Нет стратегии обновления!" << std::endl;
    }
}

// ========== ШАБЛОННЫЙ МЕТОД ==========
void LinuxDistrib::update_system_template() {
    std::cout << "\n========== ОБНОВЛЕНИЕ " << name << " ==========" << std::endl;
    
    // Шаг 1: Проверка прав
    check_permissions();
    
    // Шаг 2: Создание бэкапа
    backup_system();
    
    // Шаг 3: Обновление пакетов (специфичный шаг)
    do_update();
    
    // Шаг 4: Проверка успешности
    verify_update();
    
    // Шаг 5: Перезагрузка при необходимости
    reboot_if_needed();
    
    std::cout << "=========================================\n" << std::endl;
}

// ========== ОБЩИЕ ШАГИ (могут быть переопределены) ==========
void LinuxDistrib::check_permissions() {
    std::cout << "  [1] Проверка прав доступа: OK" << std::endl;
}

void LinuxDistrib::backup_system() {
    std::cout << "  [2] Создание резервной копии конфигов..." << std::endl;
}

void LinuxDistrib::do_update() {
    // По умолчанию используем стратегию
    std::cout << "  [3] Обновление пакетов: ";
    if (installStrategy) {
        installStrategy->update();
    } else {
        std::cout << "Нет стратегии обновления!" << std::endl;
    }
}

void LinuxDistrib::verify_update() {
    std::cout << "  [4] Проверка целостности системы: OK" << std::endl;
}

void LinuxDistrib::reboot_if_needed() {
    std::cout << "  [5] Перезагрузка не требуется" << std::endl;
}

// ========== GETTERS ==========
void LinuxDistrib::get_info() const {
    std::cout << "Имя: " << name << ", Версия: " << version 
              << ", Стабильность: " << stability_score << std::endl;
}

std::string LinuxDistrib::get_name() const { return name; }
int LinuxDistrib::get_stability_score() const { return stability_score; }

void LinuxDistrib::setInstallStrategy(std::unique_ptr<InstallStrategy> strategy) {
    installStrategy = std::move(strategy);
}

// ========== ОПЕРАТОРЫ ==========
bool LinuxDistrib::operator<(const LinuxDistrib& other) const {
    return this->stability_score < other.stability_score;
}

bool LinuxDistrib::operator>(const LinuxDistrib& other) const {
    return this->stability_score > other.stability_score;
}

bool LinuxDistrib::operator==(const LinuxDistrib& other) const {
    return this->stability_score == other.stability_score && 
           this->name == other.name;
}

std::ostream& operator<<(std::ostream& os, const LinuxDistrib& distro) {
    os << distro.name << " (стабильность: " << distro.stability_score << ")";
    return os;
}