#include <iostream>
#include <string>

class Character {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(std::string name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {
        std::cout << "Character " << name << " created.\n";
    }

    virtual ~Character() {
        std::cout << "Character " << name << " destroyed.\n";
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", Health: " << health 
                  << ", Attack: " << attack << ", Defense: " << defense << "\n";
    }
};

class Monster : public Character {
public:
    Monster(std::string name, int health, int attack, int defense)
        : Character(name, health, attack, defense) {
        std::cout << "Monster " << name << " created.\n";
    }

    ~Monster() override {
        std::cout << "Monster " << name << " destroyed.\n";
    }

    void displayInfo() const override {
        std::cout << "Monster Info: ";
        Character::displayInfo();
    }
};

class Weapon {
private:
    std::string name;
    int damage;
    float weight;

public:
    Weapon(std::string name, int damage, float weight)
        : name(name), damage(damage), weight(weight) {
        std::cout << "Weapon " << name << " created.\n";
    }

    ~Weapon() {
        std::cout << "Weapon " << name << " destroyed.\n";
    }

    void displayInfo() const {
        std::cout << "Weapon Name: " << name << ", Damage: " << damage 
                  << ", Weight: " << weight << "kg\n";
    }
};

int main() {
    // Создание объектов Weapon
    Weapon sword("Sword", 25, 3.5);
    Weapon axe("Axe", 30, 5.0);
    Weapon bow("Bow", 20, 2.0);

    // Демонстрация работы метода displayInfo() для Weapon
    sword.displayInfo();
    axe.displayInfo();
    bow.displayInfo();

    // Создание объектов Character и Monster
    Character* hero = new Character("Hero", 100, 15, 10);
    Monster* goblin = new Monster("Goblin", 50, 10, 5);

    // Вывод информации о персонаже и монстре
    hero->displayInfo();
    goblin->displayInfo();

    // Освобождение памяти
    delete hero;
    delete goblin;

    return 0;
}