#pragma once
#include "Singleton.h"
#include "Obstacle.h"
#include "Player.h"
//class Obstacle;
//class Player;

class Collision : public CSingleton<Collision>
{
private:
	
	Vector2		m_collision;
public:
	
	bool		CheckCollision(std::shared_ptr<Obstacle> m_obstacle, std::shared_ptr<Player> m_larva);
	void		SetCollision(std::shared_ptr<Player> m_larva);
	Vector2		GetCollision();
};