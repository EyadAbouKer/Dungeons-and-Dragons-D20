# Game Demo:
![Dungeons And Dragons D20](https://www.youtube.com/watch?v=DZtvYKIUk3Q)
[![YouTube Video Preview](https://github.com/EyadAbouKer/Dungeons-and-Dragons-D20/assets/126291554/690294e5-36bb-4a1a-a20f-589b654e0cdf)](https://www.youtube.com/watch?v=DZtvYKIUk3)






# GAME SUMMARY:

in an arena where players engage in battles and adventures.
It begins with the main function, where a game session is initiated.
The player is prompted to choose a character from a list including an Axe-wielder, an Assassin, a Blood Seeker, or a Spirit Breaker.
After selecting a character, the game initializes and the chosen player is prepared for battle.
A campaign is loaded, offering a series of challenges for the player to overcome.
The player navigates through maps, encountering enemies, chests with loot, friendly characters, and doors leading to new areas.
The player's movements are controlled using WASD keys, with 'q' to quit the game.
Upon encountering enemies, the player engages in combat within a combat arena, with outcomes determining whether the player progresses or faces defeat.
Loot found in chests can be added to the player's inventory.
If the player successfully navigates through a map and accesses a door, they proceed to the next stage of the campaign.
The game continues until the player decides to quit.


# SYSTEM DESIGN USED: 
1. Builder Pattern (Simplify building game Characters by splitting the constructions into packages)
2. Factory Pattern (used along with Builder pattern to finalize Character and map creation)
3. Observer Pattern (it was essential for the players to know about each other's states, and it was important to notify the map of changes happening to Enemites, players, and everything else on the map,
                     so I had to connect everything using Observer pattern)

# Other Design Choices:
1. OOP:  Inheritance, Multi-Inheritance, Friendly Access, Polymorphism
   ![image](https://github.com/EyadAbouKer/Dungeons-and-Dragons-D20/assets/126291554/19b0ecc5-c12b-4754-9954-f1998b632441)

# Game Engine:
  1. The game Engine is designed to render and refresh The Map, Characters, Enemies, Chest, and Friends in the terminal
  2. Navigate between Maps



