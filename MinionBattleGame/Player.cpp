#include <iostream>
#include "Player.h"

namespace minions {
	
	Player::Player()
	{
	}
	// cleanup remaining troops
	Player::~Player()
	{
		if (m_currentMechs.size() > 0)
		{
			for (auto it = m_currentMechs.begin(); it != m_currentMechs.end(); ++it) {
				if (*it != nullptr)
				{
					delete (*it);
				}
			}
			m_currentMechs.clear();
		}
	}

	// Populate army
	void Player::CreateArmy(vector<MechType> order, int count)
	{
		for (int i = 0, j = 0; i < count; ++i, ++j)
		{
			// reset order when end reached
			if (j == order.size()) {
				j = 0;
			}
			switch (order[j])
			{
			case MechType::CAR:
				cout << i + 1 << " Car" << endl;
				m_currentMechs.push_back(new Car());
				break;
			case MechType::FLYING_CAR:
				cout << i + 1 << " Flying_Car" << endl;
				m_currentMechs.push_back(new Flying_Car());
				break;
			case MechType::TANK:
				cout << i + 1 << " Tank" << endl;
				m_currentMechs.push_back(new Tank());
				break;
			case MechType::COPTER:
				cout << i + 1 << " Copter" << endl;
				m_currentMechs.push_back(new Copter());
				break;
			default:
				cout << "Error: Wrong Mech Type" << endl;
				break;
			}
		}
	}

	void Player::PrintStatus()
	{
		for (unsigned int i = 0; i < m_currentMechs.size(); ++i) {
			cout << i + 1 << " " << m_currentMechs[i]->GetName() << " health=" << m_currentMechs[i]->GetHp()
				<< " totalDamage=" << m_currentMechs[i]->GetDamageDealt() << endl;
		}
		cout << "The most outstanding Mech is:" << endl;
		Mech &t = GetOutstandingMech();
		cout << t.GetName() << " health=" << t.GetHp() << " totalDamage=" << t.GetDamageDealt() << endl;
	}

	Mech Player::GetFrontMech()
	{
		return *(m_currentMechs[m_currentAttackingMechIdx]);
	}

	int Player::Attack(Type type, int enemyHp)
	{
		int attackPower = 0;
		// same type, full attack power, else half
		if (m_currentMechs[m_currentAttackingMechIdx]->GetType() == type) {
			attackPower = m_currentMechs[m_currentAttackingMechIdx]->GetDamage();
		} else {
			attackPower = m_currentMechs[m_currentAttackingMechIdx]->GetDamage() / 2;
		}
		if (enemyHp - attackPower <= 0) {
			m_currentMechs[m_currentAttackingMechIdx]->AddDamageDealt(enemyHp);
		} else {
			m_currentMechs[m_currentAttackingMechIdx]->AddDamageDealt(attackPower);
		}
		return attackPower;
	}

	void Player::TakeDamage(int damage)
	{
		m_currentMechs[m_currentAttackingMechIdx]->ReduceHP(damage);
		// if HP = 0, kill target, remove from m_currentMechs
		if (m_currentMechs[m_currentAttackingMechIdx]->GetHp() == 0) {
			m_thisRoundMechMurdered = m_currentMechs[m_currentAttackingMechIdx]->GetName();
			auto it = m_currentMechs.begin() + m_currentAttackingMechIdx;
			delete (*it);
			m_currentMechs.erase(m_currentMechs.begin() + m_currentAttackingMechIdx);
			m_currentMechs.shrink_to_fit();
			// loop back to the first troop if index overflows
			if (m_currentAttackingMechIdx > m_currentMechs.size() - 1) {
				m_currentAttackingMechIdx = 0;
			}
		}
		else {
			m_thisRoundMechMurdered.clear();
		}
	}

	string Player::CurrentMechDead()
	{
		return m_thisRoundMechMurdered;
	}

	unsigned int Player::TotalMechsLeft()
	{
		return (int)m_currentMechs.size();
	}

	void Player::NextMech()
	{
		if (m_thisRoundMechMurdered.empty()) {
			++m_currentAttackingMechIdx;
		}
		if (m_currentAttackingMechIdx == m_currentMechs.size()) {
			m_currentAttackingMechIdx = 0;
		}
	}

	int GetConseq1sinBinary(int val) {
		string s("");
		while (val != 0) {
			if (val % 2 == 0)
				s.push_back('0');
			else
				s.push_back('1');
			val = val / 2;
		}
		// we can avoid reversing the string 's' to get actual binary
		//, we just need the longest 1st in sequence
		int count1seq = 0, total = 0;
		for (auto &i : s) {
			if (i == '1') {
				++count1seq;
			}
			else {
				if (total < count1seq) {
					total = count1seq;
				}
				count1seq = 0;
			}
		}
		if (total < count1seq) {
			total = count1seq;
		}
		return total;
	}

	// To optimize
	Mech Player::GetOutstandingMech()
	{
		pair<int, int> p = make_pair(0,0);
		Mech t = *(m_currentMechs[0]);
		for (auto &i : m_currentMechs) {
			if (GetConseq1sinBinary(i->GetDamageDealt()) > GetConseq1sinBinary(t.GetDamageDealt())) {
				t = *i;
			}
		}
		return t;
	}
	
}