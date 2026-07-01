#ifndef SQLITECONTAINER_H
#define SQLITECONTAINER_H

#include <sqlite3.h>
#include <memory>
#include <string>
#include <vector>
#include "LinuxDistrib.h"
#include "LinuxFactory.h"

class SQLiteContainer {
private:
    sqlite3* db;
    std::string dbPath;
    
    void executeSQL(const std::string& sql);
    void createTable();
    
public:
    class Iterator {
    private:
        sqlite3_stmt* stmt;
        bool isValid;
        int currentId;
        SQLiteContainer* container;
        
    public:
        Iterator(SQLiteContainer* cont, const std::string& sql);
        ~Iterator();
        
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        std::shared_ptr<LinuxDistrib> operator*();  
    };
    
    SQLiteContainer(const std::string& path = "distributives.db");
    ~SQLiteContainer();
    
    void add(std::unique_ptr<LinuxDistrib> distro);
    size_t size() const;
    void clear();
    
    std::unique_ptr<Iterator> begin();
    std::unique_ptr<Iterator> end();
    
    std::shared_ptr<LinuxDistrib> findById(int id); 
    std::vector<std::shared_ptr<LinuxDistrib>> getAll();  
};

#endif