#include "SQLiteContainer.h"
#include "LinuxFactory.h"
#include "DerivedDistribs.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

// Сериализация
static std::string serializeDistro(LinuxDistrib* distro) {
    json j;
    j["name"] = distro->get_name();
    j["stability_score"] = distro->get_stability_score();
    
    if (dynamic_cast<DebianBased*>(distro)) {
        j["type"] = "DebianBased";
    } else if (dynamic_cast<ArchBased*>(distro)) {
        j["type"] = "ArchBased";
    } else if (dynamic_cast<RedHatBased*>(distro)) {
        j["type"] = "RedHatBased";
    }
    
    return j.dump();
}

// Десериализация
static std::shared_ptr<LinuxDistrib> deserializeDistro(const std::string& jsonStr) {
    try {
        json j = json::parse(jsonStr);
        std::string type = j["type"];
        
        DistroType distroType;
        if (type == "DebianBased") distroType = DistroType::DebianBased;
        else if (type == "ArchBased") distroType = DistroType::ArchBased;
        else distroType = DistroType::RedHatBased;
        
        return LinuxFactory::createDistro(distroType, 0);
    } catch (...) {
        return nullptr;
    }
}

// ========== Iterator ==========

SQLiteContainer::Iterator::Iterator(SQLiteContainer* cont, const std::string& sql) 
    : stmt(nullptr), isValid(false), currentId(-1), container(cont) {
    
    sqlite3_prepare_v2(container->db, sql.c_str(), -1, &stmt, nullptr);
    if (stmt) {
        isValid = (sqlite3_step(stmt) == SQLITE_ROW);
        if (isValid) {
            currentId = sqlite3_column_int(stmt, 0);
        }
    }
}

SQLiteContainer::Iterator::~Iterator() {
    if (stmt) sqlite3_finalize(stmt);
}

SQLiteContainer::Iterator& SQLiteContainer::Iterator::operator++() {
    if (stmt) {
        isValid = (sqlite3_step(stmt) == SQLITE_ROW);
        if (isValid) {
            currentId = sqlite3_column_int(stmt, 0);
        } else {
            currentId = -1;
        }
    }
    return *this;
}

bool SQLiteContainer::Iterator::operator!=(const Iterator& other) const {
    return isValid != other.isValid;
}

std::shared_ptr<LinuxDistrib> SQLiteContainer::Iterator::operator*() {
    if (!isValid || currentId == -1) return nullptr;
    return container->findById(currentId);
}

// ========== SQLiteContainer ==========

SQLiteContainer::SQLiteContainer(const std::string& path) : dbPath(path), db(nullptr) {
    sqlite3_open(path.c_str(), &db);
    createTable();
}

SQLiteContainer::~SQLiteContainer() {
    if (db) sqlite3_close(db);
}

void SQLiteContainer::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (errMsg) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void SQLiteContainer::createTable() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS distributives (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            type TEXT,
            stability INTEGER,
            data TEXT
        );
    )";
    executeSQL(sql);
}

void SQLiteContainer::add(std::unique_ptr<LinuxDistrib> distro) {
    if (!distro) return;
    
    std::string jsonData = serializeDistro(distro.get());
    std::string sql = "INSERT INTO distributives (name, type, stability, data) VALUES ('" +
                      distro->get_name() + "', '', " +
                      std::to_string(distro->get_stability_score()) + ", '" +
                      jsonData + "');";
    executeSQL(sql);
    std::cout << "[SQLite] Добавлен: " << distro->get_name() << std::endl;
}

size_t SQLiteContainer::size() const {
    sqlite3_stmt* stmt;
    size_t count = 0;
    
    const char* sql = "SELECT COUNT(*) FROM distributives;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return count;
}

void SQLiteContainer::clear() {
    executeSQL("DELETE FROM distributives;");
    std::cout << "[SQLite] Контейнер очищен" << std::endl;
}

std::unique_ptr<SQLiteContainer::Iterator> SQLiteContainer::begin() {
    return std::make_unique<Iterator>(this, "SELECT id FROM distributives ORDER BY id;");
}

std::unique_ptr<SQLiteContainer::Iterator> SQLiteContainer::end() {
    return std::make_unique<Iterator>(this, "SELECT id FROM distributives WHERE id = -1;");
}

std::shared_ptr<LinuxDistrib> SQLiteContainer::findById(int id) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT data FROM distributives WHERE id = " + std::to_string(id) + ";";
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* jsonData = (const char*)sqlite3_column_text(stmt, 0);
            if (jsonData) {
                auto distro = deserializeDistro(jsonData);
                sqlite3_finalize(stmt);
                return distro;
            }
        }
        sqlite3_finalize(stmt);
    }
    return nullptr;
}

std::vector<std::shared_ptr<LinuxDistrib>> SQLiteContainer::getAll() {
    std::vector<std::shared_ptr<LinuxDistrib>> result;
    auto it = begin();
    auto endIt = end();
    
    while (*it != *endIt) {
        result.push_back(**it);
        ++(*it);
    }
    return result;
}