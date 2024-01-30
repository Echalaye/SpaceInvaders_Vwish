#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include <cstdlib>
#include "Player.h"
#include "Missile.h"
#include "Monster.h"
#include "CampementLife.h"
#include "Button.h"
#include "Boss.h"
#include "HealthBarre.h"

class GameManager
{
private:
	int lvl = 0;
	bool gameMenuIsActive;
	bool lvlLose;
	bool gamePlay;
	bool gamePaused;
	bool hidePlayer;
	bool bossFight;
	const int screensizeY = 800;
	const int screensizeX = 1024;
	std::string tabImgMonster [5] = { "Sprites/monster_base.png", "Sprites/monster_lvl2.png", "Sprites/monster_lvl3.png", "Sprites/monster_lvl4.png", "Sprites/monster_lvl5.png" };
	sf::Clock clockMissile;
	sf::Time timeMissile;
	sf::Clock clockMonster;
	sf::Time timeMonster;
	sf::Clock clockShoot;
	sf::Time timeShoot;
	sf::Clock clockmonsterShoot;
	sf::Time timeMonsterShoot;
	std::vector<Missile*> missilePlayerList;
	std::vector<Missile*> missileMonsterList;
	std::vector<Monster*> monsterList;
	std::vector<CampementLife*> campementList;
	Button exitButton;
	Button playButton;
	Button resumeButton;
	Button nextLvlButton;
	Button retryButton;
	Player player;
	HealthBarre healthBarrePlayer;
	HealthBarre healthBarreBoss;
	Boss boss;
	sf::Sprite spriteText;
	sf::Texture textureText;
	
public:
	GameManager();
	void GamePlay();
	void CreateMonsterList();
	void CreateCampementList();
	void EndGame(bool playerWin);
	void ReloadGame();
	void MissileMovement(std::vector<Missile*>& missileList, float speed);
	void DrawFrameGame(sf::RenderWindow& thewindow);
	void ActionGame(sf::RenderWindow& window);
};

