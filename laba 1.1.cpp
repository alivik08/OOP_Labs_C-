#include <iostream>
#include <string>

class Character {
private:
    std::string name;       // Имя персонажа
    int health;             // Уровень здоровья
    int attack;             // Уровень атаки
    int defense;            // Уровень защиты

public:
    // Конструктор
    Character(std::string n, int hp, int att, int def)
        : name(n), health(hp), attack(att), defense(def) {}

    // Метод для получения уровня здоровья
    int getHealth() const {
        return health;
    }

    // Метод для отображения информации о персонаже
    void displayInfo() const {
        std::cout << "Character: " << name << "\n"
                  << "Health: " << health << "\n"
                  << "Attack: " << attack << "\n"
                  << "Defense: " << defense << "\n";
    }

    // Метод для атаки другого персонажа
    void attackEnemy(Character &enemy) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.takeDamage(damage);
            std::cout << name << " attacks " << enemy.name << " for " << damage << " damage!\n";
        } else {
            std::cout << name << "'s attack was too weak to damage " << enemy.name << "!\n";
        }
    }

    // Метод для получения урона
    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
    }

    // Метод для лечения персонажа
    void heal(int amount) {
        health += amount;
        if (health > 100) {
            health = 100; // Максимальное здоровье
        }
    }
};

int main() {
    // Создаем двух персонажей
    Character hero("Hero", 100, 20, 5);
    Character monster("Monster", 80, 15, 10);

    // Отображаем информацию о персонажах
    hero.displayInfo();
    monster.displayInfo();

    // Персонаж атакует монстра
    hero.attackEnemy(monster);
    std::cout << "Monster's health: " << monster.getHealth() << "\n";

    // Монстр восстанавливает здоровье
    monster.heal(10);
    std::cout << "Monster's health after healing: " << monster.getHealth() << "\n";

    // Монстр атакует героя
    monster.attackEnemy(hero);
    std::cout << "Hero's health: " << hero.getHealth() << "\n";

    return 0;
}
