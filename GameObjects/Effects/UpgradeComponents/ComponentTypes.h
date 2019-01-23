//
// Created by Kringla on 15.12.2018.
//

#ifndef KAPPAPRIDE_COMPONENTTYPES_H
#define KAPPAPRIDE_COMPONENTTYPES_H
namespace comp
{
    struct component
    {
        component() = default;
        int Id;
    };
    struct income: component
    {
        income() = default;
        explicit income(float i)
        {
            Id = 0;
            add = i;
        }
        float add;
    };
    struct Health: component
    {
        Health() = default;
        explicit Health(float i)
        {
            Id = 1;
            add = i;
        }
        float add;
    };
    struct Size: component
    {
        Size() = default;
        explicit Size(float i)
        {
            Id = 2;
            add = i;
        }
        float add;
    };
    struct Attack: component
    {
        Attack() = default;
        explicit Attack(float i)
        {
            Id = 3;
            add = i;
        }
        float add;
    };
    struct Defence: component
    {
        Defence() = default;
        explicit Defence(float i)
        {
            Id = 4;
            add = i;
        }
        float add;
    };
    struct Attacks: component
    {
        Attacks() = default;
        explicit Attacks(float i)
        {
            Id = 5;
            add = i;
        }
        float add;
    };
    struct Ability: component
    {
        Ability() = default;
        explicit Ability(float i)
        {
            Id = 6;
            add = i;
        }
        float add;
    };
}

#endif //KAPPAPRIDE_COMPONENTTYPES_H
