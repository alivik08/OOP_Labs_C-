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
    Weapon(const std::string& n, int d, float w) : name(n), damage(d), weight(w) {
        std::cout << "Weapon " << name << " created!\n";
    }
    
    ~Weapon() {
        std::cout << "Weapon " << name << " destroyed!\n";
    }
    
    void displayInfo() const {
        std::cout << "Weapon: " << name << ", Damage: " << damage 
                  << ", Weight: " << weight << "kg\n";
    }
};

int main() {
    Weapon sword("Sword", 25, 3.5);
    Weapon bow("Bow", 15, 1.2);
    
    sword.displayInfo();
    bow.displayInfo();
    
    return 0;
}
