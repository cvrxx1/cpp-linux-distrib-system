#ifndef DERIVEDDISTRIBS_H
#define DERIVEDDISTRIBS_H

#include "LinuxDistrib.h"

class DebianBased : public LinuxDistrib {
private:
    std::string release_cycle;
public:
    DebianBased(std::string n, std::string v, std::string kernel, 
                bool stable, std::string cycle, int score = 70);
    DebianBased(const DebianBased& other);
    std::unique_ptr<LinuxDistrib> copy() const override;
    
    // Переопределяем специфичный шаг (опционально)
    void do_update() override;
    void reboot_if_needed() override;
};

class ArchBased : public LinuxDistrib {
private:
    std::string update_model;
public:
    ArchBased(std::string n, std::string v, std::string kernel, 
              bool stable, std::string model, int score = 40);
    ArchBased(const ArchBased& other);
    std::unique_ptr<LinuxDistrib> copy() const override;
    
    void do_update() override;
};

class RedHatBased : public LinuxDistrib {
private:
    std::string target_audience;
public:
    RedHatBased(std::string n, std::string v, std::string kernel, 
                bool stable, std::string audience, int score = 60);
    RedHatBased(const RedHatBased& other);
    std::unique_ptr<LinuxDistrib> copy() const override;
    
    void do_update() override;
    void reboot_if_needed() override;
};

#endif