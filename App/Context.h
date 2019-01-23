//
// Created by Kringla on 26.11.2018.
//

#ifndef KAPPAPRIDE_CONTEXT_H
#define KAPPAPRIDE_CONTEXT_H

#include "../GameObjects/Object.h"

#include "../GameObjects/Spaces/Space.h"
#include "../GameObjects/Spaces/Node.h"
#include "../GameObjects/Spaces/Lane.h"

#include "../GameObjects/Interface/Button.h"
#include "../GameObjects/Interface/Buttons/ButtonUnit.h"
#include "../GameObjects/Interface/Buttons/ButtonTexture.h"
#include "../GameObjects/Interface/Text.h"
#include "../GameObjects/Mouse.h"

#include "../GameObjects/Entities/Entity.h"
#include "../GameObjects/Entities/Unit.h"
#include "../GameObjects/Entities/Building.h"
#include "../GameObjects/Entities/Spell.h"

#include "../GameObjects/Effects/Effect.h"
#include "../GameObjects/Effects/Ability.h"

#include "../Map/Map.h"
#include "../Layer/Layer.h"
#include "../Sprite/Sprite.h"

class Context
{
public:
private:
    int Id;
    static int nextId;
};
#endif //KAPPAPRIDE_CONTEXT_H
