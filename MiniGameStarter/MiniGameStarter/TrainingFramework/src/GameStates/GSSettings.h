#pragma once
#include "GameStateBase.h"
#include "GameButton.h"
#include "SpriteAnimation.h"

class GSSettings :
	public GameStateBase
{
public:
	GSSettings();
	~GSSettings();

	void Init();
	void Exit();

	void Pause() override;
	void Resume() override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void HandleMouseMoveEvents(float x, float y) override;
	void Update(float deltaTime) override;
	void Draw() override;

	void UpdateButtons();

private:
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>	m_listText;
	std::shared_ptr<GameButton> m_backButton;

	// button for background, character and difficulty options
	std::shared_ptr<GameButton> m_charaButton1;
	std::shared_ptr<GameButton> m_charaButton2;

	std::shared_ptr<Text>  m_Text_settings;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

};

