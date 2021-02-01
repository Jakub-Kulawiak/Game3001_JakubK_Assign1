#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Button.h"
#include "Cartridge.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};
	Label* m_pName{};
	Label* m_pStuID{};

	Ship* m_pShip{};
	Cartridge* m_pCartridge;

	Button* m_pStartButton;
};

#endif /* defined (__START_SCENE__) */