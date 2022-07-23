#pragma once
#include "Singleton.h"
#include "Obstacle.h"
#include "Player.h"
//class Obstacle;
//class Player;

class Collision : public CSingleton<Collision>
{
private:
	int m_score;
	Vector2		m_collision;
public:
	
	bool		CheckCollision(std::shared_ptr<Obstacle> m_obstacle, std::shared_ptr<Player> m_larva);
	bool		CheckCollision(std::shared_ptr<Player> m_obj, std::shared_ptr<Player> m_larva);
	void		SetCollision(std::shared_ptr<Player> m_larva);
	Vector2		GetCollision();
	void		SetScore(int score) { m_score = score; };
	int			GetScore() { return m_score; };
};