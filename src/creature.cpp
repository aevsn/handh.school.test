#include <stdexcept>
#include "creature.h"
#include "random.h"

Creature::Creature(int _health, int _attack, int _defense,
                   int _min_damage, int _max_damage)
    : health(_health), max_health(_health), dead(false),
      attack(_attack), defense(_defense),
      min_damage(_min_damage), max_damage(_max_damage)
{
    if (_health < 0)
        throw std::runtime_error("Creature health must be 0 or higher");

    if (_attack < 1 || _attack > 30)
        throw std::runtime_error("Creature attack must be between 1 and 30");

    if (_defense < 1 || _defense > 30)
        throw std::runtime_error("Creature defense must be between 1 and 30");

    if (_min_damage <= 0 || _max_damage <= 0)
        throw std::runtime_error("Both minimum and maximum creature damage must be higher than 1");

    if (_max_damage < _min_damage)
        throw std::runtime_error("Maximum creature damage must be higher or equal to minimal");
}

bool Creature::try_attack(Creature& target)
{
    if (target.is_dead()) {
        throw std::runtime_error("Tried to attack a dead creature");
        return false;
    }

    if (!can_attack(target))
        return false;

    do_attack(target);
    return true;
}

void Creature::hurt(int amount)
{
    if (amount < 0) {
        throw std::runtime_error("Tried to deal negative damage to a creature");
        return;
    }

    health -= amount;
    clamp_health();
}

void Creature::clamp_health()
{
    if (health <= 0) {
        health = 0;
        dead = true;
    } else if (health > max_health)
        health = max_health;
}

bool Creature::can_attack(Creature& target)
{
    int attack_mod = attack - target.get_defense() + 1;
    bool success = false;

    for (int i=0; i<attack_mod; i++) {
        int die = random::random(1, 6);
        if (die >= 5) {
            success = true;
            break;
        }
    }

    return success;
}

void Creature::do_attack(Creature& target)
{
    int damage = random::random(min_damage, max_damage);
    target.hurt(damage);
}
