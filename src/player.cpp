#include <stdexcept>
#include "player.h"

Player::Player(int _health, int _attack, int _defense,
               int _damage_min, int _damage_max)
    : Creature(_health, _attack, _defense, _damage_min, _damage_max),
      heals_left(4)
{}

bool Player::try_heal()
{
    if (!can_heal())
        return false;

    do_heal();
    heals_left--;

    return true;
}

bool Player::can_heal()
{
    if (dead) {
        throw std::runtime_error("Tried to heal a dead player");
        return false;
    }

    return heals_left > 0 && health < max_health;
}

void Player::do_heal()
{
    health += max_health * 30 / 100;
    clamp_health();
}
