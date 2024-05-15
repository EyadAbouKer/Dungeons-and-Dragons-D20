//
// Created by Admin on 4/4/2024.
//

#include "builtPlayer.h"

Player *BuiltPlayer::constructPlayer(abstract_character_builder *p, const string &name) {
    p->createNewPlayer();
    p->buildCharacterName(name);
    p->buildAllAttributes();
    return p->getPlayer();
}
