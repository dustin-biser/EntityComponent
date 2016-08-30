//
// ClockScript.hpp
//
#pragma once

#include "Script/Script.hpp"

class ClockScript : public Script {
public:

	virtual void init();

	virtual void update();


private:
	GameObject * m_clock;
	GameObject * m_hourHand;
	GameObject * m_minuteHand;
	GameObject * m_secondHand;
};
