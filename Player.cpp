#include "pch.h"
#include "Player.h"

Player::Player()
{
	m_speed = 0.50f;
	m_playerTexture.loadFromFile("Graphics/Player.png");
	m_player.setTexture(m_playerTexture);
	m_player.setPosition(600, 400);
	m_alive = true;
}

bool Player::PlayerState()
{
	return m_alive;
}

float Player::GetPositionX()
{
	return m_player.getPosition().x;
}

float Player::GetPositionY()
{
	return m_player.getPosition().y;
}

void Player::Move(int direction)
{
	m_player.setPosition(m_player.getPosition().x + m_speed * direction, m_player.getPosition().y);
}

Sprite Player::GetSprite()
{
	return m_player;
}

FloatRect Player::GetCollision()
{
	return m_player.getGlobalBounds();
}

void Player::SetState(bool state)
{
	m_alive = state;
}
