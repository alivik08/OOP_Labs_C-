#include <iostream>
#include <string>

// Базовый класс Entity
class Entity {
protected:
    std::string name; // Имя сущности
    int health; // Здоровье сущности

public:
    // Конструктор для инициализации имени и здоровья
    Entity(const std::string& name, int health) : name(name), health(health) {}

    // Метод для отображения информации о сущности
    virtual void displayInfo() {
        std::cout << "Name: " << name << "\nHealth: " << health << "\n";
    }
};

// Класс Player, наследует от Entity
class Player : public Entity {
private:
    int experience; // Опыт игрока

public:
    // Конструктор для инициализации имени, здоровья и опыта
    Player(const std::string& name, int health, int experience)
        : Entity(name, health), experience(experience) {}

    // Переопределение метода displayInfo
    void displayInfo() override {
        Entity::displayInfo(); // Вызов метода базового класса
        std::cout << "Experience: " << experience << "\n"; // Добавление информации об опыте
    }
};

// Класс Enemy, наследует от Entity
class Enemy : public Entity {
private:
    std::string type; // Тип врага

public:
    // Конструктор для инициализации имени, здоровья и типа
    Enemy(const std::string& name, int health, const std::string& type)
        : Entity(name, health), type(type) {}

    // Переопределение метода displayInfo
    void displayInfo() override {
        Entity::displayInfo(); // Вызов метода базового класса
        std::cout << "Type: " << type << "\n"; // Добавление информации о типе врага
    }
};

// Класс Boss, наследует от Enemy
class Boss : public Enemy {
private:
    std::string specialAbility; // Уникальная способность босса

public:
    // Конструктор для инициализации имени, здоровья, типа и способности
    Boss(const std::string& name, int health, const std::string& type, const std::string& specialAbility)
        : Enemy(name, health, type), specialAbility(specialAbility) {}

    // Переопределение метода displayInfo
    void displayInfo() override {
        Enemy::displayInfo(); // Вызов метода базового класса
        std::cout << "Special Ability: " << specialAbility << "\n"; // Добавление информации о способности
    }
};

// Главная функция
int main() {
    // Создание объекта Player
    Player player("Hero", 100, 50);
    player.displayInfo(); // Вывод информации о игроке

    std::cout << "\n";

    // Создание объекта Enemy
    Enemy enemy("Goblin", 50, "Melee");
    enemy.displayInfo(); // Вывод информации о враге

    std::cout << "\n";

    // Создание объекта Boss
    Boss boss("Dragon", 200, "Fire", "Fire Breath");
    boss.displayInfo(); // Вывод информации о боссе

    return 0;
}