#include <cctype>
#include <iostream>
#include "player.h"
#include "monster.h"
#include "random.h"

static bool game_loop(Player& p, Monster& m)
{
    std::cout << "Player: " << p.get_health() << "/" << p.get_max_health() << std::endl;
    std::cout << "Monster: " << m.get_health() << "/" << m.get_max_health() << std::endl;
    std::cout << "Heals left: " << p.get_heals_left() << std::endl;

    std::cout << "What shall you do? (A)ttack/(H)eal/(R)un" << std::endl;

    char c;
    std::cin >> c;
    c = std::tolower(c);

    if (c == 'r')
    {
        std::cout << "You ran away scared." << std::endl;
        return false;
    }
    else if (c == 'h')
    {
        if (p.try_heal())
            std::cout << "You healed yourself." << std::endl;
        else {
            std::cout << "You cannot heal yourself!" << std::endl;
            return true;
        }
    }
    else if (c == 'a')
    {
        std::cout << "You attacked the monster. ";
        if (p.try_attack(m))
            std::cout << "Hit!" << std::endl;
        else
            std::cout << "Miss!" << std::endl;
    }
    else
    {
        std::cout << "Unknown command! Try again." << std::endl;
        return true;
    }

    if (m.is_dead()) {
        std::cout << "The monster has perished." << std::endl;
        return true;
    }

    std::cout << "The monster attacked you. ";
    if (m.try_attack(p))
        std::cout << "Hit!" << std::endl;
    else
        std::cout << "Miss!" << std::endl;

    if (p.is_dead()) {
        std::cout << "Oh no! You DIED." << std::endl;
        return false;
    }

    return true;
}

static Monster random_monster()
{
    int health = random::random(1, 100),
        attack = random::random(10, 12),
        defense = random::random(8, 10),
        min_damage = random::random(1, 10),
        max_damage = min_damage + random::random(0, 15);

    return Monster(health, attack, defense, min_damage, max_damage);
}

int main()
{
    try {
        random::seed();

        int monsters_vanquished = 0;

        Player p(100, 10, 10, 10, 20);
        Monster m = random_monster();

        std::cout << "You have encountered a monster!" << std::endl << std::endl;
        while (game_loop(p, m))
        {
            if (m.is_dead()) {
                monsters_vanquished++;
                m = random_monster();
            }

            std::cout << std::endl;
        }
        std::cout << "Vanquished " << monsters_vanquished << " monsters.";
        return 0;
    } catch (std::exception& e) {
        std::cout << "Error! " << e.what();
        return 1;
    }
}
