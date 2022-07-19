#include "Player.h"

Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime) {}

Player::~Player() {}

bool Player::HandleTouchEvents(float x, float y, bool IsPressed, std::shared_ptr<Player> m_larva) {
	if (IsPressed) {
		if ((x >= Get2DPosition(m_larva).x - GetScale().x / 2 && x <= Get2DPosition(m_larva).x + GetScale().x / 2) && (y >= Get2DPosition(m_larva).y - GetScale().y / 2 && y <= Get2DPosition(m_larva).y + GetScale().y / 2)) {
			return true;
		}
	}
	return false;
}