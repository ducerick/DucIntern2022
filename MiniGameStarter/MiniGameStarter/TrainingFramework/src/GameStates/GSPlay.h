#pragma once
#include "GameStateBase.h"
#include "Player.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;
class Player;
class Obstacle;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_KeyPress;
	bool m_mousePress;
	bool m_intro = true;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_background2;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listIntro;
	std::list<std::shared_ptr<Obstacle>>	m_listObstacle;
	std::shared_ptr<Player> m_larva;
	std::shared_ptr<Player> m_introTmp;

};
