cmake_minimum_required(VERSION 3.27)
project(D20)

set(CMAKE_CXX_STANDARD 26)

include_directories(
        include
        src
)

add_executable(D20
        src/main.cpp
        src/stats/hp/hp.cpp
        src/stats/hp/hp.h
        src/characters/character/character.cpp
        src/characters/character/character.h
        src/stats/levelsystem/levelsystem.cpp
        src/stats/levelsystem/levelsystem.h
        src/maps/map/map.h
        src/maps/map/map.cpp
        src/controllers/gameController/gameController.h
        src/renderEngine/gameView/gameView.h
        src/renderEngine/gameView/gameView.cpp
        src/characters/player/player.h
        src/characters/player/player.cpp
        src/characters/enemy/enemy.h
        src/characters/enemy/enemy.cpp
        src/controllers/gameController/gameController.cpp
        src/characters/character/characterObserverPattern/CharacterObserver.cpp
        src/characters/character/characterObserverPattern/CharacterObserver.h
        src/characters/character/characterObserverPattern/CharacterObserver.h
        src/stats/abilityscores/abilityscores.h
        src/stats/abilityscores/abilityscores.cpp
        src/items/item/item.h
        src/items/item/item.cpp
        src/items/equipment/equipment.h
        src/items/equipment/equipment.cpp
        src/characters/character/itemcontainer.h
        src/characters/character/itemcontainer.cpp
        src/maps/campaign/campaign.cpp
        src/maps/campaign/campaign.h
        src/characters/character/itemcontainer.cpp
        src/asciitable.h "src/arena/combatarena/combatarena.h" "src/arena/combatarena/combatarena.cpp"
        src/stats/abilityscores/abilityscores.h
        src/stats/abilityscores/abilityscores.cpp
        src/items/item/item.h
        src/items/item/item.cpp
        src/characters/character/itemcontainer.h
        src/characters/character/itemcontainer.cpp
        src/characters/player/players/abstract_character_builder.cpp
        src/characters/player/players/abstract_character_builder.h
        src/dice/dice.cpp
        src/dice/dice.h
        src/characters/player/players/bloodSeeker/bloodSeeker.cpp
        src/characters/player/players/bloodSeeker/bloodSeeker.h
        src/characters/player/players/assasin/assasin.cpp
        src/characters/player/players/assasin/assasin.h
        src/characters/player/players/axe/axe.cpp
        src/characters/player/players/axe/axe.h
        src/characters/player/players/spiritBreaker/spiritBreaker.cpp
        src/characters/player/players/spiritBreaker/spiritBreaker.h
        src/characters/player/playerBuilder/builtPlayer.cpp
        src/characters/player/playerBuilder/builtPlayer.h
        src/donut.cpp "src/characters/character/friend.h" "src/characters/character/friend.cpp"
        src/arena/friendarena/friendarena.h
        src/arena/friendarena/friendarena.cpp
        src/characters/enemy/enemieBuilder/creeps/creeps.h
        src/characters/enemy/enemieBuilder/titan/titan.h
        src/characters/enemy/enemieBuilder/titan/titan.cpp
        src/characters/enemy/enemieBuilder/creeps/creeps.cpp
        src/logs/logWriter.h
        src/logs/logWriter.cpp
        )

# SFML
#target_link_libraries(D20
#        ${CMAKE_SOURCE_DIR}/lib/SFML/sfml-audio.lib
#        ${CMAKE_SOURCE_DIR}/lib/SFML/sfml-graphics.lib
#        ${CMAKE_SOURCE_DIR}/lib/SFML/sfml-network.lib
#        ${CMAKE_SOURCE_DIR}/lib/SFML/sfml-system.lib
#        ${CMAKE_SOURCE_DIR}/lib/SFML/sfml-window.lib
#)

# Link winmm library
target_link_libraries(D20 winmm)
# Windows stuff
target_link_libraries(D20 -static)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# Output location
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)