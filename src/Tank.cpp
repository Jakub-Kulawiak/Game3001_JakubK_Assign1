#include "Tank.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"


Tank::Tank()
{
	TextureManager::Instance()->load("../Assets/textures/tank.png", "tank");

	auto size = TextureManager::Instance()->getTextureSize("tank");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	this->m_movementState = 0;
	
	setType(TANK);
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
	
}

Tank::~Tank() = default;

void Tank::draw()
{
	TextureManager::Instance()->draw("tank",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + getOrientation() * 60.0f));
}

void Tank::update()
{
	m_State(getState());
}

void Tank::clean()
{
}

void Tank::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void Tank::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 Tank::getOrientation() const
{
	return m_orientation;
}

void Tank::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float Tank::getRotation() const
{
	return m_rotationAngle;
}

void Tank::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = 0;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float Tank::getDistance(glm::vec2 obj1, glm::vec2 obj2)
{
	return sqrt(pow((obj2.y - obj1.y), 2) + pow((obj2.x - obj1.x), 2));
}

float Tank::getTurnRate() const
{
	return m_turnRate;
}

void Tank::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float Tank::getAccelerationRate() const
{
	return m_accelerationRate;
}

void Tank::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

int Tank::getState()
{
	return m_movementState;
}
void Tank::setState(int state)
{
	m_movementState = state;
}

void Tank::m_Seek()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using the formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void Tank::m_Flee()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = getTransform()->position - m_destination;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using the formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void Tank::m_Arrive()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;
	
	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	if (getDistance(m_destination, getTransform()->position) > 100.0f)
	{
		
		// using the formula pf = pi + vi*t + 0.5ai*t^2
		getRigidBody()->velocity += getOrientation() * (deltaTime)+
			0.5f * getRigidBody()->acceleration * (deltaTime);
	}
	
	else if (getDistance(m_destination, getTransform()->position) <= 10.0f)
	{
		getRigidBody()->velocity = getOrientation() * (0.0f)-
			0.0f * getRigidBody()->acceleration * (0.0f);
	}


	
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void Tank::m_Avoid()
{
}

void Tank::m_State(int state) // a simplified state manager that goes in update in place of the original m_Move function
{
	if(state == 0)
	{
		m_Seek();
	}
	else if(state == 1)
	{
		m_Flee();
	}
	else if(state == 2)
	{
		m_Arrive();
	}
	else if (state == 3)
	{
		m_Avoid();
	}
	
}
