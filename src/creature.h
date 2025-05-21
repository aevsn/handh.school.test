#pragma once

class Creature
{
public:
    Creature(int _health, int _attack, int _defense,
                     int _damage_min, int _damage_max);

    bool try_attack(Creature& target);

    void hurt(int amount);

    int get_health() const { return health; }
    int get_max_health() const { return max_health; }
    int get_defense() const { return defense; }
    bool is_dead() const { return dead; }

protected:
    int health, max_health;
    bool dead;

    void clamp_health();

    bool can_attack(Creature& target);
    void do_attack(Creature& target);

private:
    int attack, defense;
    int min_damage, max_damage;
};
