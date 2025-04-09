#include <iostream>
#include <vector>
#include <string>

// Базовый класс Entity
class Entity {
protected:
    std::string name;
    int health;
    int attackStrength;
    int defense;

public:
    Entity(const std::string& name, int health, int attackStrength, int defense)
        : name(name), health(health), attackStrength(attackStrength), defense(defense) {}

    virtual void attack(Entity& target) = 0; // Виртуальный метод атаки
    virtual void displayInfo() const = 0; // Виртуальный метод отображения информации
    virtual void heal(int amount) {
        health += amount; // Лечит на указанную величину
        std::cout << name << " heals for " << amount << " health points. Current health: " << health << "\n";
    }

    virtual ~Entity() = default; // Виртуальный деструктор
};

// Класс Character, наследующий от Entity
class Character : public Entity {
public:
    Character(const std::string& name, int health, int attackStrength, int defense)
        : Entity(name, health, attackStrength, defense) {}

    void attack(Entity& target) override {
        std::cout << name << " attacks " << target.getName() << " with a critical strike! Damage dealt: " << attackStrength * 2 << "\n";
        target.takeDamage(attackStrength * 2);
    }

    void displayInfo() const override {
        std::cout << "Character: " << name << ", Health: " << health << ", Attack: " << attackStrength << ", Defense: " << defense << "\n";
    }

    void takeDamage(int damage) {
        int damageTaken = damage > defense ? damage - defense : 0;
        health -= damageTaken;
        std::cout << name << " takes " << damageTaken << " damage. Remaining health: " << health << "\n";
    }
};

// Класс Monster, наследующий от Entity
class Monster : public Entity {
public:
    Monster(const std::string& name, int health, int attackStrength, int defense)
        : Entity(name, health, attackStrength, defense) {}

    void attack(Entity& target) override {
        std::cout << name << " attacks " << target.getName() << " with a monstrous roar! Damage dealt: " << attackStrength << "\n";
        target.takeDamage(attackStrength);
    }

    void displayInfo() const override {
        std::cout << "Monster: " << name << ", Health: " << health << ", Attack: " << attackStrength << ", Defense: " << defense << "\n";
    }

    void takeDamage(int damage) {
        int damageTaken = damage > defense ? damage - defense : 0;
        health -= damageTaken;
        std::cout << name << " takes " << damageTaken << " damage. Remaining health: " << health << "\n";
    }
};

// Класс Boss, наследующий от Monster
class Boss : public Monster {
public:
    Boss(const std::string& name, int health, int attackStrength, int defense)
        : Monster(name, health, attackStrength, defense) {}

    void attack(Entity& target) override {
        std::cout << name << " unleashes a fiery strike on " << target.getName() << "! Damage dealt: " << attackStrength * 3 << "\n";
        target.takeDamage(attackStrength * 3);
    }

    void displayInfo() const override {
        std::cout << "Boss: " << name << ", Health: " << health << ", Attack: " << attackStrength << ", Defense: " << defense << "\n";
    }
};

// Основная функция
int main() {
    // Создание объектов Character, Monster и Boss
    Character hero("Hero", 100, 25, 10);
    Monster goblin("Goblin", 50, 15, 5);
    Boss dragon("Dragon", 200, 30, 20);

    // Массив указателей на Entity
    std::vector<Entity*> entities = { &hero, &goblin, &dragon };

    // Вывод информации и атака для каждого объекта
    for (Entity* entity : entities) {
        entity->displayInfo();
        std::cout << "\n";
    }

    // Демонстрация полиморфного поведения
    hero.attack(goblin);
    goblin.attack(hero);
    dragon.attack(hero);

    // Лечение персонажа
    hero.heal(20);

    return 0;
}