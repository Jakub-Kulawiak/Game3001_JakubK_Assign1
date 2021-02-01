#pragma once
#ifndef __TANK__
#define __TANK__

#include "DisplayObject.h"

class Tank final : public DisplayObject
{
public:
	// constructor(s)
	Tank();

	// destructor
	~Tank();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	float getRotation() const;
	void setRotation(float angle);
	float getTurnRate() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);
	int getState();
	void setState(int state);

private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	int m_movementState;

	// private function
	void m_Seek();
	void m_Flee();
	void m_Arrive();
	void m_Avoid();
	void m_State(int state);
};



#endif
