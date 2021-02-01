#include "Cartridge.h"

Cartridge::Cartridge()
{
	TextureManager::Instance()->load("../Assets/textures/16bit.png", "cartridge");

	auto size = TextureManager::Instance()->getTextureSize("cartridge");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->isColliding = false;
	m_currentHeading = 0.0f; // current facing angle
	setType(CARTRIDGE);
}

Cartridge::~Cartridge()
{
}

void Cartridge::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("cartridge", x, y, m_currentHeading, 255, true);
}

void Cartridge::update()
{
}

void Cartridge::clean()
{
}
