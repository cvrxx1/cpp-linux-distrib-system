#include <iostream>
#include <memory>
#include "SQLiteContainer.h"
#include "LinuxFactory.h"
#include "algorithms.h"
#include "InstallStrategies.h"

using namespace std;

void demonstrateSQLiteContainer() {
    cout << "\n=== SQLiteContainer с умными указателями ===\n" << endl;
    
    SQLiteContainer container("distributives.db");
    container.clear();
    
    cout << "Добавляем дистрибутивы:" << endl;
    container.add(LinuxFactory::createDistro(DistroType::DebianBased, 0));
    container.add(LinuxFactory::createDistro(DistroType::ArchBased, 0));
    container.add(LinuxFactory::createDistro(DistroType::RedHatBased, 0));
    container.add(LinuxFactory::createDistro(DistroType::DebianBased, 1));
    container.add(LinuxFactory::createDistro(DistroType::ArchBased, 1));
    
    cout << "\nВсего дистрибутивов: " << container.size() << endl;
    
    cout << "\nОбход через итератор:" << endl;
    auto it = container.begin();
    auto end = container.end();
    
    int index = 0;
    while (*it != *end) {
        cout << "  [" << index++ << "] ";
        (**it)->get_info();
        ++(*it);
    }
    
    cout << "\nПолучаем все дистрибутивы (shared_ptr):" << endl;
    auto all = container.getAll();
    
    cout << "\nСортировка по стабильности:" << endl;
    selectionSort(all);
    
    for (size_t i = 0; i < all.size(); i++) {
        cout << "  [" << i << "] " << *all[i] << endl;
    }
    
    // Не нужно вручную удалять — shared_ptr сам позаботится
}

void demonstrateStrategy() {
    cout << "\n=== ПАТТЕРН СТРАТЕГИЯ ===\n" << endl;
    
    auto ubuntu = LinuxFactory::createDistro(DistroType::DebianBased, 0);
    auto arch = LinuxFactory::createDistro(DistroType::ArchBased, 0);
    
    cout << "--- Обычное поведение ---" << endl;
    ubuntu->install_program("firefox");
    arch->install_program("chromium");
    
    cout << "\n--- Смена стратегии на лету ---" << endl;
    ubuntu->setInstallStrategy(make_unique<PacmanStrategy>());
    ubuntu->install_program("firefox");
}

void demonstrateTemplateMethod() {
    cout << "\n=== ПАТТЕРН ШАБЛОННЫЙ МЕТОД ===\n" << endl;
    
    auto ubuntu = LinuxFactory::createDistro(DistroType::DebianBased, 0);
    auto arch = LinuxFactory::createDistro(DistroType::ArchBased, 0);
    
    ubuntu->update_system_template();
    arch->update_system_template();
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    demonstrateSQLiteContainer();
    demonstrateStrategy();
    demonstrateTemplateMethod();
    
    return 0;
}