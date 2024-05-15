#include "abilityscores.h"


AbilityScores::AbilityScores() :
	strength(0), dexterity(0), constitution(0), intelligence(0),
	wisdom(0), charisma(0)
{
}

scoretype AbilityScores::get_strength() const
{
	return strength;
}

scoretype AbilityScores::get_dexterity() const
{
	return dexterity;
}

scoretype AbilityScores::get_constitution() const
{
	return constitution;
}

scoretype AbilityScores::get_intelligence() const
{
	return intelligence;
}

scoretype AbilityScores::get_wisdom() const
{
	return wisdom;
}

scoretype AbilityScores::get_charisma() const
{
	return charisma;
}

void AbilityScores::set_strength(scoretype value)
{
	strength = adjust_score(value);
}

void AbilityScores::set_dexterity(scoretype value)
{
	dexterity = adjust_score(value);
}

void AbilityScores::set_constitution(scoretype value)
{
	constitution = adjust_score(value);
}

void AbilityScores::set_intelligence(scoretype value)
{
	intelligence = adjust_score(value);
}

void AbilityScores::set_wisdom(scoretype value)
{
	wisdom = adjust_score(value);
}

void AbilityScores::set_charisma(scoretype value)
{
	charisma = adjust_score(value);
}

scoretype AbilityScores::adjust_score(const scoretype score)
{
	if (score > 10)
	{
		return 10;
	}

	if (score < 0)
	{
		return 0;
	}

	return score;
}
