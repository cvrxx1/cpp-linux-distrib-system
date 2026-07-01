#ifndef LINUXDISTRIB_H
#define LINUXDISTRIB_H

#include <iostream>
#include <string>
#include <memory>
#include "InstallStrategy.h"

enum class DistroType {
    DebianBased,
    ArchBased,
    RedHatBased
};

class LinuxDistrib {
protected:
    std::string name;
    std::string version;
    std::string kernel_version;
    bool is_stable;
    std::string package_manager;
    int stability_score;
    
    std::unique_ptr<InstallStrategy> installStrategy;

public:
    LinuxDistrib(std::string n, std::string v, std::string kernel, 
                 bool stable, std::string pm, int score = 50);
    virtual ~LinuxDistrib();

    virtual std::unique_ptr<LinuxDistrib> copy() const = 0;

    void install_program(const std::string& prog_name);
    void update_system();  // старый метод, оставляем для совместимости
    
    // НОВЫЙ ШАБЛОННЫЙ МЕТОД
    void update_system_template();
    
    virtual void get_info() const;
    
    virtual std::string get_name() const;
    virtual int get_stability_score() const;
    
    void setInstallStrategy(std::unique_ptr<InstallStrategy> strategy);
    
    // Шаги шаблонного метода (могут быть переопределены)
    virtual void check_permissions();      // общий шаг 1
    virtual void backup_system();          // общий шаг 2
    virtual void do_update();              // специфичный шаг (переопределяется)
    virtual void verify_update();          // общий шаг 4
    virtual void reboot_if_needed();       // общий шаг 5
    
    bool operator<(const LinuxDistrib& other) const;
    bool operator>(const LinuxDistrib& other) const;
    bool operator==(const LinuxDistrib& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const LinuxDistrib& distro);
};

#endif