#pragma once
#ifndef __CARTRIDGE__
#define __CARTRIDGE__

#include "DisplayObject.h"
#include "TextureManager.h"

class Cartridge final : public DisplayObject
{
public:
	Cartridge();
	~Cartridge();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

private:
	float m_currentHeading;

};
#endif
