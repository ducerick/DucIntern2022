#pragma once

#include "GameStateBase.h"
#include "GameButton.h"
#include "Collision.h"

class GSPause :
	public GameStateBase
{
public:
	GSPause();
	~GSPause();

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
	std::shared_ptr<Text>  m_Text_Score;
};

