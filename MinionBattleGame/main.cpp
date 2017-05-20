#include <iostream>
#include "Player.h"

using namespace minions;

int main()
{
	Player p1;
	Player p2;

	cout << "Army 1 - Initial Mechs: " << endl;
	p1.CreateArmy({ MechType::FLYING_CAR, MechType::COPTER, MechType::TANK, MechType::CAR }, 20);
	cout << endl;
	cout << "Army 2 - Initial Mechs: " << endl;
	
	p2.CreateArmy({ MechType::CAR, MechType::FLYING_CAR, MechType::COPTER, MechType::TANK }, 20);
	int rounds = 1;
	int damage = 0;
	cout << endl;
	cout << "BATTLE" << endl;
	// Loop while each player has atleast 1 troop to play with
	while (p1.TotalMechsLeft() > 0 && p2.TotalMechsLeft() > 0) {

		cout << "Round " << rounds++
			<< " Player 1 " << p1.GetFrontMech().GetName() << "( health="
			<< p1.GetFrontMech().GetHp() << ", totalDamage=" << p1.GetFrontMech().GetDamageDealt() << ") vs "
			<< " Player 2 " << p2.GetFrontMech().GetName() << "( health="
			<< p2.GetFrontMech().GetHp() << ", totalDamage=" << p2.GetFrontMech().GetDamageDealt() << ")" << endl;

		damage = p1.Attack(p2.GetFrontMech().GetType(), p2.GetFrontMech().GetHp());

		p2.TakeDamage( damage );

		// Game over check
		// after player 1 finished attacking we need to check if anymore of troops exist for player 2
		if (p2.TotalMechsLeft() == 0) {
			break;
		}

		damage = p2.Attack(p1.GetFrontMech().GetType(), p1.GetFrontMech().GetHp());

		p1.TakeDamage( damage );

		if (!p1.CurrentMechDead().empty()) {
			cout << " Player 1 " << p1.CurrentMechDead() << " was killed" << endl;
		}
		if (!p2.CurrentMechDead().empty()) {
			cout << " Player 2 " << p2.CurrentMechDead() << " was killed" << endl;
		}
		// advance the next troop
		p1.NextMech();
		p2.NextMech();
	}
	cout << endl;
	if (p1.TotalMechsLeft() > 0) {
		cout << "Army 1 is Winner. Remaining Mechs:" << endl;
		p1.PrintStatus();
	} else {
		cout << "Army 2 is Winner. Remaining Mechs:" << endl;
		p2.PrintStatus();
	}

	getchar();

	return 0;
}