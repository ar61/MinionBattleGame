#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace minions {

	// To make Mechs modular
	//struct attribute {

	//};

	//static const unordered_map<MechType, void> minion_attributes = {

	//	

	//};

	enum MechType {
		CAR = 0,
		FLYING_CAR,
		TANK,
		COPTER
	};

	enum Type {
		AIR = 0,
		GROUND,
		ALL
	};

}