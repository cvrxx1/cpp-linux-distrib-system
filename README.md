# Linux Distributions Management System

## О проекте

Проект представляет собой систему управления Linux-дистрибутивами, разработанную на C++ с применением современных паттернов проектирования и принципов ООП. Система демонстрирует глубокое понимание:

- Объектно-ориентированного программирования (наследование, полиморфизм, инкапсуляция)
- Паттернов проектирования (Factory, Strategy, Template Method, Iterator, Decorator)
- Современного C++ (умные указатели, RAII, move-семантика)
- Работы с базами данных (SQLite)
- STL (контейнеры, алгоритмы, итераторы)

### Ключевые возможности

- Иерархия классов с 3+ наследниками (DebianBased, ArchBased, RedHatBased)
- Паттерн "Фабрика" для создания объектов
- Паттерн "Стратегия" для гибкой установки/обновления
- Паттерн "Шаблонный метод" для единого алгоритма обновления
- Контейнер с итератором на основе SQLite
- Декораторы итераторов для фильтрации
- Интеллектуальные указатели (unique_ptr, shared_ptr)
- Сортировка и бинарный поиск с замером производительности

### Структура проекта

.

├── CMakeLists.txt # Конфигурация сборки

├── README.md # Документация

│

├── Core/ # Базовые классы

│ ├── LinuxDistrib.h

│ ├── LinuxDistrib.cpp

│ ├── DerivedDistribs.h

│ └── DerivedDistribs.cpp

│

├── Patterns/ # Паттерны проектирования

│ ├── InstallStrategy.h # Интерфейс Strategy

│ ├── InstallStrategies.h # Конкретные стратегии

│ ├── LinuxFactory.h

│ ├── LinuxFactory.cpp

│ └── IteratorDecorators.h # Декораторы итераторов

│

├── Container/ # Контейнеры

│ ├── SQLiteContainer.h

│ └── SQLiteContainer.cpp

│

├── Algorithms/ # Алгоритмы

│ └── algorithms.h

│

└── 
main.cpp # Демонстрация

## Установка и сборка

### Клонирование
```bash
git clone https://github.com/cvrxx1/cpp-linux-distrib-system
```
```bash
cd linux-distrib-system
```

### Сборка через CMake
```bash
mkdir build && cd build
cmake ..
make
```

### Запуск
```bash
./linux_distrib
```

## Ключевые концепции, демонстрируемые в проекте
1. ООП: наследование, полиморфизм, инкапсуляция
2. Паттерны: Factory, Strategy, Template Method, Iterator, Decorator
3. STL: контейнеры, алгоритмы, умные указатели
4. Базы данных: SQLite, сериализация/десериализация
5. Алгоритмы: сортировка, бинарный поиск, замеры производительности
6. Сборка: CMake, разделение на файлы
