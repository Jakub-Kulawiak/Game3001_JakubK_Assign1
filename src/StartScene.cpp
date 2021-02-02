#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color green = { 0, 255, 50, 255 };
	m_pStartLabel = new Label("START SCENE", "vgafix", 48, green, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pNote = new Label("In terms of music I was going for a tech demo feel", "vgafix", 48, green, glm::vec2(400.0f, 560.0f));
	m_pNote->setParent(this);
	addChild(m_pNote);
	
	m_pName = new Label("Jakub Kulawiak", "vgafix", 36, green, glm::vec2(400.0f, 200.0f));
	m_pName->setParent(this);
	addChild(m_pName);

	m_pStuID = new Label("101 251 309", "vgafix", 36, green, glm::vec2(400.0f, 220.0f));
	m_pStuID->setParent(this);
	addChild(m_pStuID);

	m_pCartridge = new Cartridge();
	m_pCartridge->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pCartridge);
	
	//m_pShip = new Ship();
	//m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f); 
	//addChild(m_pShip); 

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

