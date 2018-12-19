#include "pch.h"
#include "Enemy.h"



Enemy::Enemy()
{
	float m_enemySpeed = 0.0f;
	bool m_activeEnemy = false;
	m_enemyTexture.loadFromFile("Graphics/Enemy.png");
	m_enemySprite.setTexture(m_enemyTexture);
	m_enemySprite.setRotation(180);
}

void EnemySpawn() 
{

}
void Enemy::EnemyReset(int iteration)
{
	int iterationplus = iteration + 5;
	srand((int)time(0) * 10 + iterationplus);
	float height = (rand() % 100*iterationplus - 800);
	float length = (rand() % 500) + 430;
	m_enemySprite.setPosition(length, height);
	m_activeEnemy = (true);
}

float Enemy::GetEnemyPositionX()
{
	return m_enemySprite.getPosition().x;
}
float Enemy::GetEnemyPositionY()
{
	return m_enemySprite.getPosition().y;
}

Sprite Enemy::EnemyGetSprite() 
{
	return m_enemySprite;
}

bool Enemy::EnemyGetActive()
{
	return m_activeEnemy;
}

float Enemy::EnemyGetSpeed()
{
	return m_enemySpeed;
}

void Enemy::EnemyMove(float dt)
{
	m_enemySprite.setPosition(m_enemySprite.getPosition().x, (m_enemySprite.getPosition().y + (600*dt)));
}

void Enemy::EnemySetActive(bool state)
{
	m_activeEnemy = state;
}

FloatRect Enemy::GetCollision()
{
	return m_enemySprite.getGlobalBounds();
}
