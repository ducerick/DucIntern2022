#pragma once

#include "GameStateBase.h"
#include "GameButton.h"
#include "Collision.h"

class GSHelp :
	public GameStateBase
{
public:
	GSHelp();
	~GSHelp();

	void Init() override;
	void Exit() override;

	void Pause() override;
	void Resume() override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void HandleMouseMoveEvents(float x, float y) override;
	void Update(float deltaTime) override;
	void Draw() override;

private:
	std::shared_ptr<GameButton>	m_backButton;
	std::shared_ptr<Sprite2D> m_brick;
	std::shared_ptr<Sprite2D>  m_candy;
	std::shared_ptr<Sprite2D>  m_sausage;
	std::shared_ptr<Sprite2D>  m_pear;
	std::shared_ptr<Sprite2D>  m_apple;
	std::list<std::shared_ptr<Sprite2D>>	m_listFood;
	std::shared_ptr<Player>  m_monster1;
	std::shared_ptr<Player>  m_monster2;
	std::list<std::shared_ptr<Player>>	m_listMonster;
	std::shared_ptr<Text>  m_Text_Help;
	std::shared_ptr<Text>  m_Text_Brick;
	std::shared_ptr<Text>  m_Text_Food;
	std::shared_ptr<Text>  m_Text_Monster;
	std::shared_ptr<Text>  m_Text_Credit;
	std::shared_ptr<Text>  m_Text_Name;
	std::shared_ptr<Text>  m_Text_Thankyou;
	std::list<std::shared_ptr<Text>>	m_listText;



};

