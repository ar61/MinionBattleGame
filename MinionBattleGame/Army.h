#pragma once

#include "CommonDefines.h"

namespace minions {

	class Mech {
	protected:
		int m_hp{ 0 };
		int m_damage{ 0 };
		Type m_type;
		Type m_preferredTarget;
		string m_name{ std::string() };
		int m_damageDealt{ 0 };

	public:
		Mech() {};
		virtual ~Mech() {};
		Mech(const Mech& other);
		Mech& operator=(const Mech& other);

		void ReduceHP(int value);
		void AddDamageDealt(int value);
		int GetHp() const;
		int GetDamage() const;
		Type GetType() const;
		Type GetPreferredTarget() const;
		string GetName() const;
		int GetDamageDealt() const;
		void ResetValues();
	};

	class Car : public Mech {
	public:
		Car();
		~Car();
	};

	class Flying_Car : public Car {
	public:
		Flying_Car();
		~Flying_Car();
	};

	class Tank : public Mech {
	public:
		Tank();
		~Tank();
	};

	class Copter : public Mech {
	public:
		Copter();
		~Copter();
	};
}