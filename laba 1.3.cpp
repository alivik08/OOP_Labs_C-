#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

class Entity {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Entity(const std::string& n, int h, int a, int d) : name(n), health(h), attack(a), defense(d) {}
    
    virtual void attackTarget(Entity& target) {
        int damage = attack - target.defense;
        if (damage > 0) {
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }
    
    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health 
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
    
    virtual void heal(int amount) {
        health += amount;
        if (health > 100) health = 100;
        std::cout << name << " healed for " << amount << " HP!\n";
    }
    
    virtual ~Entity() {}
};

class Character : public Entity {
public:
    Character(const std::string& n, int h, int a, int d) : Entity(n, h, a, d) {}
    
    void attackTarget(Entity& target) override {
        int damage = attack - target.defense;
        if (damage > 0) {
            if (rand() % 100 < 20) { // 20% chance for critical hit
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }
};

class Monster : public Entity {
public:
    Monster(const std::string& n, int h, int a, int d) : Entity(n, h, a, d) {}
    
    void attackTarget(Entity& target) override {
        int damage = attack - target.defense;
        if (damage > 0) {
            if (rand() % 100 < 30) { // 30% chance for poison
                damage += 5;
                std::cout << "Poisonous attack! ";
            }
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }
};

class Boss : public Monster {
public:
    Boss(const std::string& n, int h, int a, int d) : Monster(n, h, a, d) {}
    
    void attackTarget(Entity& target) override {
        int damage = attack - target.defense;
        if (damage > 0) {
            if (rand() % 100 < 40) { // 40% chance for fire attack
                damage += 10;
                std::cout << "Fire attack! ";
            }
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }
};

int main() {
    srand(time(0));
    
    Character hero("Hero", 100, 20, 10);
    Monster goblin("Goblin", 50, 15, 5);
    Boss dragon("Dragon", 200, 30, 20);
    
    std::vector<Entity*> entities = {&hero, &goblin, &dragon};
    
    for (auto entity : entities) {
        entity->displayInfo();
    }
    
    hero.attackTarget(goblin);
    dragon.attackTarget(hero);
    hero.heal(30);
    
    return 0;
}
