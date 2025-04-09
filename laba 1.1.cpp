#include <iostream>
#include <string>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    const int maxHealth = 100;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    int getHealth() const { return health; }

    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health 
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    void attackEnemy(Character& enemy) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            std::cout << name << " attacks " << enemy.name << " for " << damage << " damage!" << std::endl;
        } else {
            std::cout << name << " attacks " << enemy.name << ", but it has no effect!" << std::endl;
        }
    }

    // Добавленные методы
    void heal(int amount) {
        health = (health + amount > maxHealth) ? maxHealth : health + amount;
        std::cout << name << " healed for " << amount << " HP!" << std::endl;
    }

    void takeDamage(int amount) {
        health = (health - amount < 0) ? 0 : health - amount;
        std::cout << name << " took " << amount << " damage!" << std::endl;
    }
};

int main() {
    Character hero("Hero", 100, 20, 10);
    Character monster("Goblin", 50, 15, 5);

    hero.displayInfo();
    monster.displayInfo();
    
    hero.attackEnemy(monster);
    monster.displayInfo();
    
    monster.takeDamage(10);
    hero.heal(20);
    
    return 0;
}
