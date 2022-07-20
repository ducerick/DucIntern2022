#pragma once
#include "Sprite2D.h"

enum ObstacleType {BRICK, HOTDOG, BANANA, SPIKE};

class Obstacle : public Sprite2D
{
private:
	ObstacleType	m_type;

public:
	Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, ObstacleType type);
	~Obstacle();

	ObstacleType	GetObstacleType() { return m_type; };
	void			SetType(ObstacleType type) { m_type = type; }
	void			SetSpeed(std::shared_ptr<Obstacle> m_obstacle, float speed, float deltaTime);
	void			SwitchType();
};
