#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>


template <typename T>
class Logger {
private:
    std::ofstream logFile;
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл журнала");
        }
    }
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    void log(const T& message) {
        logFile << message << std::endl;
    }
};


class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), level(1), experience(0) {}

    void attackEnemy(Character& enemy, Logger<std::string>& logger) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.takeDamage(damage, logger);
            logger.log(name + " атакует " + enemy.name + " и наносит " + std::to_string(damage) + " урона!");
            std::cout << name << " атакует " << enemy.name << " и наносит " << damage << " урона!" << std::endl;
        } else {
            logger.log(name + " атакует " + enemy.name + ", но это неэффективно!");
            std::cout << name << " атакует " << enemy.name << ", но это неэффективно!" << std::endl;
        }
    }

    void takeDamage(int damage, Logger<std::string>& logger) {
        health -= damage;
        if (health < 0) {
            health = 0;
            logger.log(name + " был побежден!");
            throw std::runtime_error(name + " здоровье упало ниже нуля!");
        }
    }

    void heal(int amount, Logger<std::string>& logger) {
        health += amount;
        if (health > 100) health = 100;
        logger.log(name + " восстанавливает " + std::to_string(amount) + " HP!");
        std::cout << name << " восстанавливает " << amount << " HP!" << std::endl;
    }

    void gainExperience(int exp, Logger<std::string>& logger) {
        experience += exp;
        if (experience >= 100) {
            level++;
            experience -= 100;
            logger.log(name + " повысил уровень до " + std::to_string(level) + "!");
            std::cout << name << " повысил уровень до " << level << "!" << std::endl;
        }
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", HP: " << health
                  << ", Атака: " << attack << ", Защита: " << defense
                  << ", Уровень: " << level << ", Опыт: " << experience << std::endl;
    }

    std::string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    int getAttack() const {
        return attack;
    }

    int getDefense() const {
        return defense;
    }

    int getLevel() const {
        return level;
    }

    int getExperience() const {
        return experience;
    }

    void setHealth(int h) {
        if (h < 0) {
            throw std::invalid_argument("Здоровье не может быть отрицательным!");
        }
        health = h;
    }
};


class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    virtual ~Monster() {}

    virtual void attackEnemy(Character& enemy, Logger<std::string>& logger) {
        int damage = attack - enemy.getDefense();
        if (damage > 0) {
            enemy.setHealth(enemy.getHealth() - damage);
            logger.log(name + " атакует " + enemy.getName() + " и наносит " + std::to_string(damage) + " урона!");
            std::cout << name << " атакует " << enemy.getName() << " и наносит " << damage << " урона!" << std::endl;
        } else {
            logger.log(name + " атакует " + enemy.getName() + ", но это неэффективно!");
            std::cout << name << " атакует " << enemy.getName() << ", но это неэффективно!" << std::endl;
        }
    }

    virtual void displayInfo() const {
        std::cout << "Монстр: " << name << ", HP: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }

    std::string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void setHealth(int h) {
        if (h < 0) {
            throw std::invalid_argument("Здоровье не может быть отрицательным!");
        }
        health = h;
    }

    int getAttack() const {
        return attack;
    }

    int getDefense() const {
        return defense;
    }
};


class Chubaka : public Monster {
public:
    Chubaka() : Monster("Чубака", 30, 10, 5) {}
};

class Dynozavr : public Monster {
public:
    Dynozavr() : Monster("Динозавр", 100, 25, 15) {}
};

class Ork : public Monster {
public:
    Ork() : Monster("Орк", 50, 15, 10) {}
};


class Inventory {
private:
    std::vector<std::string> items;

public:
    void addItem(const std::string& item) {
        items.push_back(item);
        std::cout << item << " добавлен в инвентарь." << std::endl;
    }

    void removeItem(const std::string& item) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (*it == item) {
                items.erase(it);
                std::cout << item << " удален из инвентаря." << std::endl;
                return;
            }
        }
        std::cout << item << " не найден в инвентаре." << std::endl;
    }

    void displayInventory() const {
        std::cout << "Инвентарь:" << std::endl;
        for (const auto& item : items) {
            std::cout << "- " << item << std::endl;
        }
    }
};


class Game {
private:
    Character player;
    Inventory inventory;
    Logger<std::string> logger;

public:
    Game(const std::string& playerName)
        : player(playerName, 100, 20, 10), logger("game_log.txt") {}

    void start() {
        std::cout << "Добро пожаловать в RPG игру, " << player.getName() << "!" << std::endl;
        player.displayInfo();
        inventory.displayInventory();
    }

    void battle(Monster& monster) {
        std::cout << "Дикий " << monster.getName() << " появился!" << std::endl;
        monster.displayInfo();

        while (player.getHealth() > 0 && monster.getHealth() > 0) {
            try {
                int damage = player.getAttack() - monster.getDefense();
                if (damage > 0) {
                    monster.setHealth(monster.getHealth() - damage);
                    logger.log(player.getName() + " атакует " + monster.getName() + " и наносит " + std::to_string(damage) + " урона!");
                    std::cout << player.getName() << " атакует " << monster.getName() << " и наносит " << damage << " урона!" << std::endl;
                } else {
                    logger.log(player.getName() + " атакует " + monster.getName() + ", но это неэффективно!");
                    std::cout << player.getName() << " атакует " << monster.getName() << ", но это неэффективно!" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                break;
            }

            if (monster.getHealth() <= 0) {
                std::cout << monster.getName() << " побежден!" << std::endl;
                player.gainExperience(50, logger);
                break;
            }

            try {
                monster.attackEnemy(player, logger);
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                break;
            }

            if (player.getHealth() <= 0) {
                std::cout << player.getName() << " был побежден! Игра окончена." << std::endl;
                break;
            }
        }
    }

    void saveGame(const std::string& filename) {
        std::ofstream saveFile(filename);
        if (!saveFile) {
            std::cout << "Не удалось открыть файл сохранения." << std::endl;
            return;
        }
        saveFile << player.getName() << std::endl;
        saveFile << player.getHealth() << std::endl;
        saveFile << player.getAttack() << std::endl;
        saveFile << player.getDefense() << std::endl;
        saveFile << player.getLevel() << std::endl;
        saveFile << player.getExperience() << std::endl;
        std::cout << "Игра сохранена в " << filename << std::endl;
    }

    void loadGame(const std::string& filename) {
        std::ifstream loadFile(filename);
        if (!loadFile) {
            std::cout << "Не удалось открыть файл сохранения." << std::endl;
            return;
        }
        std::string name;
        int health, attack, defense, level, experience;
        loadFile >> name >> health >> attack >> defense >> level >> experience;
        player = Character(name, health, attack, defense);
        try {
            player.setHealth(health);
        } catch (const std::exception& e) {
            std::cout << "Ошибка при установке здоровья: " << e.what() << std::endl;
        }
        std::cout << "Загружен уровень игрока: " << level << ", опыт: " << experience << std::endl;
        std::cout << "Игра загружена из " << filename << std::endl;
    }

    void showInventory() const {
        inventory.displayInventory();
    }

    void addItemToInventory(const std::string& item) {
        inventory.addItem(item);
    }

    void removeItemFromInventory(const std::string& item) {
        inventory.removeItem(item);
    }

    std::string getPlayerName() const {
        return player.getName();
    }

    int getPlayerHealth() const {
        return player.getHealth();
    }
};

int main() {
    try {
        Game game("Герой");
        game.start();

        bool running = true;
        while (running) {
            std::cout << "\nВыберите действие:\n";
            std::cout << "1. Сразиться с Чубакой\n";
            std::cout << "2. Сразиться с Динозавром\n";
            std::cout << "3. Сразиться с Орком\n";
            std::cout << "4. Показать инвентарь\n";
            std::cout << "5. Добавить предмет в инвентарь\n";
            std::cout << "6. Удалить предмет из инвентаря\n";
            std::cout << "7. Сохранить игру\n";
            std::cout << "8. Загрузить игру\n";
            std::cout << "9. Выйти\n";
            std::cout << "Введите выбор: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    Chubaka chubaka;
                    game.battle(chubaka);
                    break;
                }
                case 2: {
                    Dynozavr dynozavr;
                    game.battle(dynozavr);
                    break;
                }
                case 3: {
                    Ork ork;
                    game.battle(ork);
                    break;
                }
                case 4: {
                    game.showInventory();
                    break;
                }
                case 5: {
                    std::cout << "Введите предмет для добавления: ";
                    std::string item;
                    std::cin.ignore();
                    std::getline(std::cin, item);
                    game.addItemToInventory(item);
                    break;
                }
                case 6: {
                    std::cout << "Введите предмет для удаления: ";
                    std::string item;
                    std::cin.ignore();
                    std::getline(std::cin, item);
                    game.removeItemFromInventory(item);
                    break;
                }
                case 7: {
                    std::cout << "Введите имя файла для сохранения игры: ";
                    std::string filename;
                    std::cin >> filename;
                    game.saveGame(filename);
                    break;
                }
                case 8: {
                    std::cout << "Введите имя файла для загрузки игры: ";
                    std::string filename;
                    std::cin >> filename;
                    game.loadGame(filename);
                    break;
                }
                case 9: {
                    running = false;
                    std::cout << "Выход из игры. До свидания!" << std::endl;
                    break;
                }
                default: {
                    std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
