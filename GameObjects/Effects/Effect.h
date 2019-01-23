//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_EFFECTS_H
#define KAPPAPRIDE_EFFECTS_H

#include "../Object.h"

class Object;
class Effect: public Object{
public:
    Effect();
    explicit Effect(Map& map);
    virtual obj_Type Type()const{return obj_Type::EFFECT;}

protected:
    int cost;
    int Effect_Id;
    static int nextE_Id;
};


#endif //KAPPAPRIDE_EFFECTS_H
