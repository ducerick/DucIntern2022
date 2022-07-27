#pragma once

#include "GameStateBase.h"
#include "GameButton.h"
#include "Collision.h"

class GSGameOver :
	public GameStateBase
{
public:
	GSGameOver();
	~GSGameOver();

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
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Player> m_Animation;
	std::shared_ptr<Text>  m_Text_GameOver;
	std::shared_ptr<Text>  m_Text_Score;
	std::shared_ptr<Text>  m_Text_highScore;

};

