#include "GameManager.h"

GameManager::GameManager() : 
	exitButton("Sprites/exit_button.png"), 
	playButton("Sprites/play_button.png"), 
	resumeButton("Sprites/resume_button.png"),
	retryButton("Sprites/retry_button.png"),
	nextLvlButton("Sprites/next_lvl_button.png"),
	healthBarrePlayer("Sprites/health_bar_background.png", "Sprites/health_bar_full.png"), 
	healthBarreBoss("Sprites/boss_health_bar_background.png", "Sprites/boss_health_bar_full.png")
{
	gameMenuIsActive = true;

}

void GameManager::ReloadGame()
{
	exitButton.SetIsActive(false);
	resumeButton.SetIsActive(false);
	playButton.SetIsActive(false);
	nextLvlButton.SetIsActive(false);
	retryButton.SetIsActive(false);
	player.SetLife(player.GetMaxLife());
	if (!bossFight) {
		CreateMonsterList();
	}
	else {
		boss.sprite.setPosition(screensizeX / 2 - 50.f , 100.f);
	}
	CreateCampementList();
	hidePlayer = false;
	gamePlay = true;
	healthBarrePlayer.SetHealthBarre(player.GetLife(), player.GetMaxLife());
}

void GameManager::MissileMovement(std::vector<Missile*>& missileList, float speed)
{

		for (size_t i = 0; i < missileList.size(); i++) {
			missileList[i]->sprite.move(0.f,speed);
			if (missileList[i]->sprite.getPosition().y < -10) {
				delete missileList[i];
				missileList[i] = nullptr;
				missileList.erase(missileList.begin() + i);
			}
		}

}

void GameManager::GamePlay()
{
	srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(screensizeX, screensizeY), "Simple 2D Game");
	window.setFramerateLimit(60);


	player.sprite.setPosition(screensizeX / 2, screensizeY - 100.f);

	healthBarrePlayer.spriteFront.setPosition(0.f, 0.f);
	healthBarrePlayer.spriteBck.setPosition(0.f, 0.f);

	healthBarreBoss.spriteFront.setPosition(screensizeX / 2, 0.f);
	healthBarreBoss.spriteBck.setPosition(screensizeX /2, 0.f);

	CreateMonsterList();
	CreateCampementList();

	exitButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2);

	playButton.sprite.setPosition( screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);
	resumeButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);
	retryButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);
	nextLvlButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);


	while (window.isOpen())
	{
		window.clear();
		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed )
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased && !gamePlay)
			{
			
				if (exitButton.CheckButton(event.mouseButton)&& exitButton.GetIsActive())
				{
					window.close();
				}
				if (playButton.CheckButton(event.mouseButton) && playButton.GetIsActive()) 
				{
					exitButton.SetIsActive(false);
					playButton.SetIsActive(false);
					gamePlay = true;
					gamePaused = false;
					gameMenuIsActive = false;
				}
				if (resumeButton.CheckButton(event.mouseButton) && resumeButton.GetIsActive()) {
					exitButton.SetIsActive(false);
					resumeButton.SetIsActive(false);
					gamePlay = true;
					gamePaused = false;
				}
				if (retryButton.CheckButton(event.mouseButton)&& retryButton.GetIsActive()) {
					lvl = 0;
					bossFight = false;
					ReloadGame();
				}
				if (nextLvlButton.CheckButton(event.mouseButton) && nextLvlButton.GetIsActive()) {
					lvl += 1;
					if (lvl >= 5) {
						bossFight = true;
					}
					ReloadGame();
				}
			}
			if (event.type == sf::Event::KeyReleased && (gamePlay || gamePaused)) {
				if (event.key.scancode == sf::Keyboard::Scan::P) {
					gamePlay = !gamePlay;
					gamePaused = !gamePaused;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& gamePlay)
			{

				player.sprite.move(player.GetMovementDirection(0, player.sprite, screensizeX), 0.f);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)&&gamePlay)
			{
				player.sprite.move(player.GetMovementDirection(1, player.sprite, screensizeX), 0.f);
			}

			if (event.type == sf::Event::KeyReleased && gamePlay)
			{
				timeShoot = clockShoot.getElapsedTime();
				if (event.key.scancode == sf::Keyboard::Scan::Space && timeShoot.asSeconds() >= 0.75f) {
					Missile* missilePlayer = new Missile();
					missilePlayer->sprite.setPosition(player.sprite.getPosition().x + 31.5f, player.sprite.getPosition().y);
					missilePlayerList.push_back(missilePlayer);
					clockMissile.restart();
					clockShoot.restart();
				}

			}
		}

		if (gamePlay) {
			ActionGame(window);
		}

		
		DrawFrameGame(window);

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
		// Update here
	}

}

void GameManager::CreateMonsterList()
{
	int tabPosMonsterX [6] = {80,240, 400,570,720,880};
	int tabPosMonsterY [4] = {50, 90, 130, 170};
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 6; j++) {
			Monster* monster = new Monster(tabImgMonster[lvl]);
			monster->sprite.setPosition(tabPosMonsterX[j], tabPosMonsterY[i]);
			monsterList.push_back(monster);
		}
	}
}

void GameManager::CreateCampementList()
{
	int tabPosCampement[4] = { 75, 335,595,855};
	for (size_t i = 0; i < 4; i++) {
		CampementLife* campement = new CampementLife();
		campement->sprite.setPosition(tabPosCampement[i], screensizeY - 200.f);
		campementList.push_back(campement);

	}
}

void GameManager::EndGame(bool playerWin)
{
	for (size_t j = 0; j < campementList.size(); j++) {
		delete campementList[j];
	}
	campementList.clear();

	for (size_t j = 0; j < monsterList.size(); j++) {
		delete monsterList[j];
	}
	monsterList.clear();

	for (size_t j = 0; j < missileMonsterList.size(); j++) {
		delete missileMonsterList[j];
		
	}
	missileMonsterList.clear();

	for (size_t j = 0; j < missilePlayerList.size(); j++) {
		delete missilePlayerList[j];
		
	}
	missilePlayerList.clear();
	hidePlayer = true;


	switch (playerWin)
	{
		case true:
			if (!textureText.loadFromFile("Sprites/win_text.png"))
			{
				std::cout << "Fail to load" << std::endl;
			}
			spriteText.setTexture(textureText);
			spriteText.setScale(3.f, 3.f);
			spriteText.setPosition(screensizeX / 2 - 200.f, screensizeY / 2 - 300.f);

			lvlLose = false;
			break;
		case false:
			if (!textureText.loadFromFile("Sprites/loose_text.png"))
			{
				std::cout << "Fail to load" << std::endl;
			}
			
			spriteText.setTexture(textureText, true);
			spriteText.setScale(3.f, 3.f);
			spriteText.setPosition(screensizeX / 2 - 200.f, screensizeY / 2 - 300.f);

			lvlLose = true;
			break;
		default:
			break;
			
	}
	gamePlay = false;
}

void GameManager::DrawFrameGame(sf::RenderWindow& thewindow) {
	if (gamePlay && !gamePaused && !gameMenuIsActive) {
		for (size_t i = 0; i < monsterList.size(); i++) {
			thewindow.draw(monsterList[i]->sprite);
		}

		for (size_t i = 0; i < campementList.size(); i++) {
			thewindow.draw(campementList[i]->sprite);
		}

		if (!hidePlayer) {

			thewindow.draw(player.sprite);

			thewindow.draw(healthBarrePlayer.spriteBck);
			thewindow.draw(healthBarrePlayer.spriteFront);
		}

		if (bossFight) {
			thewindow.draw(boss.sprite);
			thewindow.draw(healthBarreBoss.spriteBck);
			thewindow.draw(healthBarreBoss.spriteFront);
		}
	}
	else if (!gamePlay && gameMenuIsActive) {
		exitButton.SetIsActive(true);
		playButton.SetIsActive(true);
		thewindow.draw(exitButton.sprite);
		thewindow.draw(playButton.sprite);
		thewindow.draw(spriteText);
	}
	else if (!gamePlay && !gamePaused && !lvlLose && !gameMenuIsActive) {
		exitButton.SetIsActive(true);
		if (!bossFight) {
			nextLvlButton.SetIsActive(true);
			thewindow.draw(nextLvlButton.sprite);
		}
		thewindow.draw(exitButton.sprite);
		thewindow.draw(spriteText);
	}
	else if (!gamePlay && !gamePaused && lvlLose && !gameMenuIsActive) {
		exitButton.SetIsActive(true);
		retryButton.SetIsActive(true);
		thewindow.draw(exitButton.sprite);
		thewindow.draw(retryButton.sprite);
		thewindow.draw(spriteText);
	}
	else if (!gamePlay && gamePaused && !gameMenuIsActive) {
		for (size_t i = 0; i < monsterList.size(); i++) {
			thewindow.draw(monsterList[i]->sprite);
		}

		for (size_t i = 0; i < campementList.size(); i++) {
			thewindow.draw(campementList[i]->sprite);
		}

		if (!hidePlayer) {
			thewindow.draw(player.sprite);
		}
		exitButton.SetIsActive(true);
		resumeButton.SetIsActive(true);
		thewindow.draw(exitButton.sprite);
		thewindow.draw(resumeButton.sprite);
	}
}


void GameManager::ActionGame(sf::RenderWindow& window) {

	if (!bossFight) {
		if (monsterList.size() == 0) {
			EndGame(true);
			window.clear();
		}
		else if (campementList.size() == 0 || player.GetLife() <= 0 || campementList[0]->sprite.getPosition().y - 10 <= monsterList[monsterList.size() - 1]->sprite.getPosition().y) {
			EndGame(false);
			window.clear();
		}
	}
	timeMonsterShoot = clockmonsterShoot.getElapsedTime();
	if (timeMonsterShoot.asSeconds() >= 1.5f && monsterList.size() != 0 && !bossFight) {
		int random = rand() % monsterList.size();
		float Ypos = monsterList[random]->sprite.getPosition().y;
		for (size_t i = 0; i < monsterList.size(); i++) {
			if (monsterList[i]->sprite.getPosition().x == monsterList[random]->sprite.getPosition().x && monsterList[i]->sprite.getPosition().y > Ypos) {
				Ypos = monsterList[i]->sprite.getPosition().y;
			}
		}

		Missile* missileMonster = new Missile();
		missileMonster->sprite.setPosition(monsterList[random]->sprite.getPosition().x + 31.5f, Ypos + 10.f);
		missileMonsterList.push_back(missileMonster);
		clockmonsterShoot.restart();
	}


	timeMissile = clockMissile.getElapsedTime();
	if (timeMissile.asSeconds() >= 0.01f) {
		if (missilePlayerList.size() != 0) {
			MissileMovement(missilePlayerList, -missilePlayerList[0]->GetSpeed());
		}
		if (missileMonsterList.size() != 0) {
			MissileMovement(missileMonsterList, missileMonsterList[0]->GetSpeed());
		}
		clockMissile.restart();
	}



	timeMonster = clockMonster.getElapsedTime();
	if (timeMonster.asSeconds() >= 0.5f && !bossFight) {
		for (size_t i = 0; i < monsterList.size(); i++) {
			monsterList[i]->sprite.move(monsterList[i]->getSpeed(), 0.f);

		}
		for (size_t j = 0; j < monsterList.size(); j++) {
			if (monsterList[j]->sprite.getPosition().x >= screensizeX - 80 || monsterList[j]->sprite.getPosition().x <= 20) {
				for (size_t i = 0; i < monsterList.size(); i++) {
					monsterList[i]->sprite.move(0.f, 40);
					monsterList[i]->setSpeed(-(monsterList[i]->getSpeed()));
					if (monsterList[i]->getSpeed() > 0) {
						monsterList[i]->setSpeed((monsterList[i]->getSpeed() + monsterList[i]->GetSpeedBoost()));
					}
					else {
						monsterList[i]->setSpeed((monsterList[i]->getSpeed() - monsterList[i]->GetSpeedBoost()));
					}
				}
				break;
			}
		}


		clockMonster.restart();
	}

	if (bossFight) {
		if (boss.GetLife() <= 0) {
			EndGame(true);
			window.clear();
		}
		else if (campementList.size() == 0 || player.GetLife() <= 0 || campementList[0]->sprite.getPosition().y - 10 <= boss.sprite.getPosition().y) {
			EndGame(false);
			window.clear();
		}

		timeMonster = clockMonster.getElapsedTime();
		if (timeMonster.asSeconds() >= 0.25f) {
			boss.sprite.move(boss.GetSpeed(), 0.f);
			if (boss.sprite.getPosition().x >= screensizeX - 20 - (boss.sprite.getGlobalBounds().width) || boss.sprite.getPosition().x <= 20) {
				boss.sprite.move(0.f, 40);
				boss.SetSpeed(-(boss.GetSpeed()));

			}
			clockMonster.restart();
		}

		timeMonsterShoot = clockmonsterShoot.getElapsedTime();
		if (timeMonsterShoot.asSeconds() >= 1.f) {

			for (size_t i = 0; i < 3; i++) {
				Missile* missileMonster = new Missile();
				switch (i)
				{
				case 0:
					missileMonster->sprite.setPosition(boss.sprite.getPosition().x + boss.sprite.getGlobalBounds().width / 2, boss.sprite.getPosition().y + 10.f);
					missileMonsterList.push_back(missileMonster);
					break;
				case 1:
					missileMonster->sprite.setPosition(boss.sprite.getPosition().x, boss.sprite.getPosition().y + 10.f);
					missileMonsterList.push_back(missileMonster);
					break;
				case 2:
					missileMonster->sprite.setPosition(boss.sprite.getPosition().x + boss.sprite.getGlobalBounds().width, boss.sprite.getPosition().y + 10.f);
					missileMonsterList.push_back(missileMonster);
					break;

				}

			}
			clockmonsterShoot.restart();
		}

	}

	for (size_t i = 0; i < missilePlayerList.size(); i++) {
		if (missilePlayerList[i] != nullptr) {
			window.draw(missilePlayerList[i]->sprite);
		}
	}
	for (size_t i = 0; i < missilePlayerList.size(); i++) {
		if (missilePlayerList[i] != nullptr) {
			if (!bossFight) {
				for (size_t j = 0; j < monsterList.size(); j++) {
					if (missilePlayerList[i]->sprite.getGlobalBounds().intersects(monsterList[j]->sprite.getGlobalBounds())) {
						monsterList[j]->setLife(missilePlayerList[i]->getDamage());
						if (monsterList[j]->getLife() <= 0) {
							delete monsterList[j];
							monsterList[j] = nullptr;
							monsterList.erase(monsterList.begin() + j);
						}
						delete missilePlayerList[i];
						missilePlayerList[i] = nullptr;
						missilePlayerList.erase(missilePlayerList.begin() + i);
						break;
					}
				}
			}
			else {
				if (missilePlayerList[i]->sprite.getGlobalBounds().intersects(boss.sprite.getGlobalBounds())) {
					boss.SetLife(boss.GetLife() - missilePlayerList[i]->getDamage());
					delete missilePlayerList[i];
					missilePlayerList[i] = nullptr;
					missilePlayerList.erase(missilePlayerList.begin() + i);
					healthBarreBoss.SetHealthBarre(boss.GetLife(), boss.GetMaxLife());
					break;
				}
			}
		}
	}


	if (missileMonsterList.size() != 0) {

		for (size_t i = 0; i < missileMonsterList.size(); i++) {
			if (missileMonsterList[i] != nullptr) {
				window.draw(missileMonsterList[i]->sprite);
			}
		}
		for (size_t i = 0; i < missileMonsterList.size(); i++) {
			if (missileMonsterList[i] != nullptr) {
				for (size_t j = 0; j < campementList.size(); j++) {
					if (missileMonsterList[i]->sprite.getGlobalBounds().intersects(campementList[j]->sprite.getGlobalBounds())) {
						campementList[j]->SetLife(missileMonsterList[i]->getDamage());
						if (campementList[j]->GetLife() <= 0) {
							delete campementList[j];
							campementList[j] = nullptr;
							campementList.erase(campementList.begin() + j);
						}
						delete missileMonsterList[i];
						missileMonsterList[i] = nullptr;
						missileMonsterList.erase(missileMonsterList.begin() + i);
						break;
					}
					if (missileMonsterList[i]->sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
						player.SetLife(player.GetLife() - missileMonsterList[i]->getDamage());
						delete missileMonsterList[i];
						missileMonsterList[i] = nullptr;
						missileMonsterList.erase(missileMonsterList.begin() + i);
						healthBarrePlayer.SetHealthBarre(player.GetLife(), player.GetMaxLife());
						break;
					}
				}
			}
		}
	}
}

