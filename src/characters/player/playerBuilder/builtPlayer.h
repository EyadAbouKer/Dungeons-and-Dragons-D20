//
// Created by Admin on 4/4/2024.
//

#ifndef D20_BUILTPLAYER_H
#define D20_BUILTPLAYER_H
#include "characters/player/players/abstract_character_builder.h"

class BuiltPlayer {
//private:
//    abstract_character_builder* player;
//public:
//    void setCharacterBuilder(abstract_character_builder* f);
//    Fighter* getFighter();
//    void constructFighter(int level, std::string name);
public:
 static Player* constructPlayer(abstract_character_builder *p, const std::string& name);

//private:
//    abstract_character_builder* player;



};


#endif //D20_BUILTPLAYER_H
