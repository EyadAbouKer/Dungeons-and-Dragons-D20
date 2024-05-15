#pragma once
#include <cmath>
typedef int scoretype;
class AbilityScores
{
public:
	AbilityScores();

	scoretype get_strength() const;
	scoretype get_dexterity() const;
	scoretype get_constitution() const;
	scoretype get_intelligence() const;
	scoretype get_wisdom() const;
	scoretype get_charisma() const;

	void set_strength(scoretype value);
	void set_dexterity(scoretype value);
	void set_constitution(scoretype value);
	void set_intelligence(scoretype value);
	void set_wisdom(scoretype value);
	void set_charisma(scoretype value);

private:
	scoretype strength;
	scoretype dexterity;
	scoretype constitution;
	scoretype intelligence;
	scoretype wisdom;
	scoretype charisma;

	scoretype adjust_score(const scoretype score);
};