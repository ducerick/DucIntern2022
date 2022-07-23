#pragma once
#pragma once
#include "SpriteAnimation.h"


class Player : public SpriteAnimation
{
private:


public:
	Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~Player();

	bool HandleTouchEvents(float x, float y, bool bIsPressed, std::shared_ptr<Player> m_larva);

	void SetSpeed(std::shared_ptr<Player> m_obj, float speed, float deltaTime);

};