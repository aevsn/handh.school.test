#pragma once

#include "creature.h"

class Player : public Creature
{
public:
    Player(int _health, int _attack, int _defense,
           int _damage_min, int _damage_max);

    bool try_heal();

    int get_heals_left() const { return heals_left; }

private:
    int heals_left;

    bool can_heal();
    void do_heal();
};
