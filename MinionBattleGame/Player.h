#pragma once

#include "Army.h"
#include <queue>
#include <vector>

namespace minions {

	class Player {
	private:
		vector<Mech*> m_currentMechs;
		// player stats
		string m_thisRoundMechMurdered;
		unsigned int m_currentAttackingMechIdx{ 0 };
		Mech GetOutstandingMech();
	public:
		
		Player();
		~Player();

		void CreateArmy(vector<MechType> order, int count);
		void PrintStatus();

		Mech GetFrontMech();
		int Attack(Type type, int enemyHp);
		void TakeDamage(int damage);
		string CurrentMechDead();
		unsigned int TotalMechsLeft();
		void NextMech();
	};
}