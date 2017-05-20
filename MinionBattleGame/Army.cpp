#include "Army.h"

namespace minions {

	Mech::Mech(const Mech & other)
	{
		m_name = other.GetName();
		m_hp = other.GetHp();
		m_type = other.GetType();
		m_damage = other.GetDamage();
		m_preferredTarget = other.GetPreferredTarget();
		m_damageDealt = other.GetDamageDealt();
	}

	Mech & Mech::operator=(const Mech & other)
	{
		if (this != &other)
		{
			m_name = other.GetName();
			m_hp = other.GetHp();
			m_type = other.GetType();
			m_damage = other.GetDamage();
			m_preferredTarget = other.GetPreferredTarget();
			m_damageDealt = other.GetDamageDealt();
		}
		return *this;
	}

	void Mech::ReduceHP(int value)
	{
		m_hp -= value;
		if (m_hp < 0) {
			m_hp = 0;
		}
	}

	void Mech::AddDamageDealt(int value)
	{
		m_damageDealt += value;
	}

	int Mech::GetHp() const
	{
		return m_hp;
	}

	int Mech::GetDamage() const
	{
		return m_damage;
	}

	Type Mech::GetType() const
	{
		return m_type;
	}

	Type Mech::GetPreferredTarget() const
	{
		return m_preferredTarget;
	}

	string Mech::GetName() const
	{
		return m_name;
	}

	int Mech::GetDamageDealt() const
	{
		return m_damageDealt;
	}

	void Mech::ResetValues()
	{
		m_name.clear();
		m_hp = 0;
		m_damage = 0;
		m_damageDealt = 0;
	}

	Car::Car()
	{
		m_name = "Car";
		m_type = Type::GROUND;
		m_damage = 6;
		m_hp = 50;
		m_preferredTarget = Type::GROUND;
	}

	Car::~Car()
	{
	}

	Flying_Car::Flying_Car() : Car()
	{
		m_name = "Flying_Car";
		m_type = Type::AIR;
		m_preferredTarget = Type::AIR;
	}

	Flying_Car::~Flying_Car()
	{
	}

	Tank::Tank()
	{
		m_name = "Tank";
		m_type = Type::GROUND;
		m_damage = 5;
		m_hp = 50;
		m_preferredTarget = Type::ALL;
	}

	Tank::~Tank()
	{
	}

	Copter::Copter()
	{
		m_name = "Copter";
		m_type = Type::AIR;
		m_damage = 7;
		m_hp = 40;
		m_preferredTarget = Type::GROUND;
	}

	Copter::~Copter()
	{
	}
}