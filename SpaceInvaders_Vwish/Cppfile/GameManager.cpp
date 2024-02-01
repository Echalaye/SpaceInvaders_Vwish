// GameManager.cpp est le script qui définie le fonctionnement de la classe GameManager.
// C'est aussi le script qui gère le déroulement du jeu. 
// Il contient les fonction suivante:
//	- GameManager: le constructeur de la classe qui va s'occupé d'instantié les images des boutons et des barres de vie ainsi que d'afficher le menu.
//	- CreateMonsterList : cette fonction permet de créer la liste de monstre stocker dans la variable monsterList. 
//	- CreateCampementListe : de la même manière que la fonction précédente cette fonction permet de créer et de stocker la liste des campements dans une variable campementList
//	- GamePlay : cette fonction est une fonction corps du jeu. C'est elle qui crée la boucle de jeu et la fenêtre de jeu
//	  C'est aussi elle qui gère tout les évènements input joueur et enfin c'est elle qui appelle les fonction suivante pour afficher a l'écran et faire bouger les objets
//	- MissileMovement : cette fonction s'occupe de faire bouger tout les missiles dans la liste de missiles qu'on lui envoie en paramètre. 
//	  Ainsi, elle fait bouger les missiles du joueur et des ennemies en simultané.
//  - ActionGame : cette fonction s'occupe de faire jouer toute les actions de notre frame. Elle bouge a temps régulier nos ennemies (ou le boss), notre joueur, les missiles
//    et vérifie qui prend ou non des degats.
//	- DrawFrameGame : cette fonction s'occupe de dessiner a l'écran tout les objets qu'elles doit dessiner
//	- EndGame : cette fonction est appellé lorsque le joueur a gagner ou perdu le niveau. Elle gère texte et les boutons a afficher en fonction d'une défaites ou d'une victoire.
//  - ReloadGame : Cette fonction est appelé uniquement quand le bouton retry ou next level est utilisé. 
//    Elle permet de lancer le niveau suivant ou bien de recommencer la partie depuis le début.



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


void GameManager::CreateMonsterList()
{
	//On commence par créer deux tableau de position différent pour que l'écart entre chaque monstre soit optimal
	int tabPosMonsterX[6] = { 80,240, 400,570,720,880 };
	int tabPosMonsterY[4] = { 50, 90, 130, 170 };

	//On fait une boucle imbriqué pour parcourir nos deux tableau
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 6; j++) {
			//On crée un nouveau monstre, on lui donne sa position X Y en fonction de nos deux tableau et on l'ajoute dans notre monsterList
			Monster* monster = new Monster(tabImgMonster[lvl]);
			monster->sprite.setPosition(tabPosMonsterX[j], tabPosMonsterY[i]);
			monsterList.push_back(monster);
		}
	}
}

void GameManager::CreateCampementList()
{
	//Pareil que pour notre MonsterList, on crée un tableau de position
	int tabPosCampement[4] = { 75, 335,595,855 };

	//On itère dans notre tableau de position
	for (size_t i = 0; i < 4; i++) {
		//On crée un nouveau CampementLife on lui set sa position et on l'ajoute dans notre campementList
		CampementLife* campement = new CampementLife();
		campement->sprite.setPosition(tabPosCampement[i], screensizeY - 200.f);
		campementList.push_back(campement);

	}
}


void GameManager::GamePlay()
{
	//On utilise srand((unsigned)time(NULL)); pour créer du random qui nous permettra de choisir une position aléatoire d'ou les monstre tirerons un missile 
	srand((unsigned)time(NULL));

	//On crée une fenêtre de jeu et on lui set ses FPS a 60 pour que le jeu soit plus optimum
	sf::RenderWindow window(sf::VideoMode(screensizeX, screensizeY), "Simple 2D Game");
	window.setFramerateLimit(60);

	//On défini la position de base du player et celle des barres de vie du joueur et du boss
	player.sprite.setPosition(screensizeX / 2, screensizeY - 100.f);
	healthBarrePlayer.spriteFront.setPosition(0.f, 0.f);
	healthBarrePlayer.spriteBck.setPosition(0.f, 0.f);
	healthBarreBoss.spriteFront.setPosition(screensizeX / 2, 0.f);
	healthBarreBoss.spriteBck.setPosition(screensizeX /2, 0.f);

	//On appelle nos fonctions pour crée notre liste de monstre et notre list de campement
	CreateMonsterList();
	CreateCampementList();

	//On set la position de chaqu'un de nos bouton
	exitButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2);
	playButton.sprite.setPosition( screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);
	resumeButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);
	retryButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);
	nextLvlButton.sprite.setPosition(screensizeX / 2 - 100.f, screensizeY / 2 - 100.f);

	//On démare la boucle de jeu qui tourne tant que notre fenêtre est ouverte
	while (window.isOpen())
	{
		//On commence par clear notre écran a chaque frame pour pouvoir redessiner sur une page blanche a chaque fois 
		window.clear();

		//On crée une variable d'évènement qui permettra de récupérer tout nos event/input utilisateur
		sf::Event event;

		//On fait une boucle while pour regarder si il y a un event
		while (window.pollEvent(event))
		{
			//On regarde si la fenêtre se fait fermer ou si le joueur clique sur echape et dans ce cas on ferme la fenêtre du jeu
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

			//On regarde le cas ou le joueur clique avec sa sourit a l'écran et que notre jeu n'est pas entrain de jouer donc un menu est affiché a l'écran
			else if (event.type == sf::Event::MouseButtonReleased && !gamePlay)
			{
				//Si on clique sur le boutton exit on ferme la page
				if (exitButton.CheckButton(event.mouseButton)&& exitButton.GetIsActive())
				{
					window.close();
				}
				//si on clique sur le bouton play alors on lance le début du jeu, on passe a false tout nos bouton 
				// et on les set is active a false pour qu'ils ne soit plus cliquable
				if (playButton.CheckButton(event.mouseButton) && playButton.GetIsActive()) 
				{
					exitButton.SetIsActive(false);
					playButton.SetIsActive(false);
					gamePlay = true;
					gamePaused = false;
					gameMenuIsActive = false;
				}
				// De même si on clique sur le bouton resume alors on reprend le jeu on passe a false tout nos bouton 
				// et on les set is active a false pour qu'ils ne soit plus cliquable
				if (resumeButton.CheckButton(event.mouseButton) && resumeButton.GetIsActive()) {
					exitButton.SetIsActive(false);
					resumeButton.SetIsActive(false);
					gamePlay = true;
					gamePaused = false;
				}
				//si on clique sur le bouton retry alors on repasse le nombre de lvl réussi a 0 et la variable bossfight a false et on appelle la fonction reload
				if (retryButton.CheckButton(event.mouseButton)&& retryButton.GetIsActive()) {
					lvl = 0;
					bossFight = false;
					ReloadGame();
				}
				//si on clique sur le bouton nextLvl on regarde si le nombre de niveau est >= 5 et a ce moment la on lance le combat de boss en passant bossFight a true
				//enfin on appelle la fonction reloadGame pour relancer le niveau suivant
				if (nextLvlButton.CheckButton(event.mouseButton) && nextLvlButton.GetIsActive()) {
					lvl += 1;
					if (lvl >= 5) {
						bossFight = true;
					}
					ReloadGame();
				}
			}
			// On regarde si le jeu est en route ou si il est en pause et si le joueur appuie sur la touche P dans ce cas le jeu passe de pause a play et inversement
			if (event.type == sf::Event::KeyReleased && (gamePlay || gamePaused)) {
				if (event.key.scancode == sf::Keyboard::Scan::P) {
					gamePlay = !gamePlay;
					gamePaused = !gamePaused;
				}
			}

			//On regarde si le joueur va a droite ou a gauche et dans ce cas on appelle la variable move du player en lui passant les bon paramètre de mouvement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& gamePlay)
			{

				player.sprite.move(player.GetMovementDirection(0, player.sprite, screensizeX), 0.f);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)&&gamePlay)
			{
				player.sprite.move(player.GetMovementDirection(1, player.sprite, screensizeX), 0.f);
			}

			//On regarde si le joueur a appuie sur la barre espace et si le temps avant son prochain tir est >= 0.75secondes 
			if (event.type == sf::Event::KeyReleased && gamePlay)
			{
				timeShoot = clockShoot.getElapsedTime();
				if (event.key.scancode == sf::Keyboard::Scan::Space && timeShoot.asSeconds() >= 0.75f) {
					//Dans ce cas on crée un nouveau missile on lui set sa position, on l'ajoute a la liste de missile du player et on reset les timer de shoot et de missile
					Missile* missilePlayer = new Missile();
					missilePlayer->sprite.setPosition(player.sprite.getPosition().x + 31.5f, player.sprite.getPosition().y);
					missilePlayerList.push_back(missilePlayer);
					clockMissile.restart();
					clockShoot.restart();
				}

			}
		}

		//On regarde si le jeu n'est pas das un menu ou en pause et dans ce cas on appelle la fonction ActionGame
		if (gamePlay) {
			ActionGame(window);
		}

		//On appelle la fonction pour dessiner a l'écran tout nos sprit
		DrawFrameGame(window);

		//On fait s'afficher a l'écran toute les choses que l'on a dessiné
		window.display();
	}

}




void GameManager::MissileMovement(std::vector<Missile*>& missileList, float speed)
{
	//On parcours la liste de tout nos missile et pour chaque missile on les fait bouger sur l'axe Y en fonction de leur vitesse
	for (size_t i = 0; i < missileList.size(); i++) {
		missileList[i]->sprite.move(0.f, speed);
		//On regarde si le missile depasse de l'écran dans ce cas on détruit notre missile on passe son pointeur a nullptr et on l'efface de la liste de Missile
		if (missileList[i]->sprite.getPosition().y < -10 || missileList[i]->sprite.getPosition().y > screensizeY + 5) {
			delete missileList[i];
			missileList[i] = nullptr;
			missileList.erase(missileList.begin() + i);
		}
	}

}

void GameManager::ActionGame(sf::RenderWindow& window) {

	//On regarde si le jeu est actuellement en phase de bossFight Si c'est pas le cas alors on vérifie si le joueur a gagner ou perdu dans ce cas on appelle la fonction EndGame
	if (!bossFight) {
		//Le joueur gagne si la liste de monstre est vide
		if (monsterList.size() == 0) {
			EndGame(true);
			window.clear();
		}
		//Le joueur perd si ses points de vie sont a 0, si il n'a plus de campement ou si les ennemies sont a la hauteur des campements
		else if (campementList.size() == 0 || player.GetLife() <= 0 || campementList[0]->sprite.getPosition().y - 10 <= monsterList[monsterList.size() - 1]->sprite.getPosition().y) {
			EndGame(false);
			window.clear();
		}
	}

	//On regarde si le timer du tir des monstre est >= 1.5 seconde et que la liste de monstre n'est pas vide et que le joueur n'est pas en boss fight
	timeMonsterShoot = clockmonsterShoot.getElapsedTime();
	if (timeMonsterShoot.asSeconds() >= 1.5f && monsterList.size() != 0 && !bossFight) {
		//Dans ce cas on trouve un nombre aléatoire corespondant a un monstre de la liste
		int random = rand() % monsterList.size();
		//On récupère la position Y de notre monstre
		float Ypos = monsterList[random]->sprite.getPosition().y;
		//On regarde parmit tout les monstre de la même colomne que notre monstre si il y en a un en dessous de lui ou non
		for (size_t i = 0; i < monsterList.size(); i++) {
			if (monsterList[i]->sprite.getPosition().x == monsterList[random]->sprite.getPosition().x && monsterList[i]->sprite.getPosition().y > Ypos) {
				//Si oui alors on passe cette nouvelle position comme point de tire 
				Ypos = monsterList[i]->sprite.getPosition().y;
			}
		}

		//On crée un nouveau missile, on lui set sa position a celle du monstre et on l'ajoute dans notre liste de missile monster avant de reset le timer de shoot
		Missile* missileMonster = new Missile();
		missileMonster->sprite.setPosition(monsterList[random]->sprite.getPosition().x + 31.5f, Ypos + 10.f);
		missileMonsterList.push_back(missileMonster);
		clockmonsterShoot.restart();
	}

	//On regarde si le timer de moovement des missiles est >= 0.01 secondes dans ce cas on appelle la fonction MissileMovement
	//On lui passe la bonne speed en fonction de la liste de missile du joueur ou du monstre
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


	//On regarde si le timer de mouvement de nos monstre est >= 0.5 seconds
	timeMonster = clockMonster.getElapsedTime();
	if (timeMonster.asSeconds() >= 0.5f && !bossFight) {
		//Si oui on parcours le tableau et on bouge tout les monstres un a un en fonction de leur vitesse
		for (size_t i = 0; i < monsterList.size(); i++) {
			monsterList[i]->sprite.move(monsterList[i]->getSpeed(), 0.f);

		}
		//Enfin on parcours notre tableau de monstre et on vérifie si ils sont au bord ou non, 
		//si oui alors on les descend d'un cran puis on inverse leur speed pour qu'ils aillent de l'autre sens
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

		//On reset notre timer de mouvement
		clockMonster.restart();
	}

	//Si jamais on est en combat
	if (bossFight) {
		//On vérifie si la vie de notre boss est a 0 dans ce cas le joueur gagne les conditions de défaite son les même pour le combat contre les monstres et contre le boss
		if (boss.GetLife() <= 0) {
			EndGame(true);
			window.clear();
		}
		else if (campementList.size() == 0 || player.GetLife() <= 0 || campementList[0]->sprite.getPosition().y - 10 <= boss.sprite.getPosition().y) {
			EndGame(false);
			window.clear();
		}

		//On bouger notre boss de la même manière que nos monstre sauf que lui bougera toute les 0.25 secondes
		timeMonster = clockMonster.getElapsedTime();
		if (timeMonster.asSeconds() >= 0.25f) {
			boss.sprite.move(boss.GetSpeed(), 0.f);
			if (boss.sprite.getPosition().x >= screensizeX - 20 - (boss.sprite.getGlobalBounds().width) || boss.sprite.getPosition().x <= 20) {
				boss.sprite.move(0.f, 40);
				boss.SetSpeed(-(boss.GetSpeed()));

			}
			clockMonster.restart();
		}

		//On regarde si notre timer de tir est >= 1 secondes et dans ce cas notre boss tire trois missiles avant de reset le timer
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

	
	//On parcours la liste de nos missiles
	for (size_t i = 0; i < missilePlayerList.size(); i++) {
		//Si le missile n'est pas un pointeur nul alors on regarde si on est en boss fight ou non
		if (missilePlayerList[i] != nullptr) {
			if (!bossFight) {
				//Dans le cas ou on est pas en boss fight, on parcours la liste de monstre et on regarde si notre missile intersect un monstre
				for (size_t j = 0; j < monsterList.size(); j++) {
					if (missilePlayerList[i]->sprite.getGlobalBounds().intersects(monsterList[j]->sprite.getGlobalBounds())) {
						//si il y a intersection, on inflige des domages au monstres on regarde si sa vie est a 0 et on supprime le missile
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
				//Dans le cas du boss on regarde si le missile intersect le boss et si oui alors on inflige des dommages au boss puis on détruit le missile
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


	//On fait la même chose dans le cas de la liste des missiles des monstres sauf qu'on regarde si on touche un campement ou le joueur
	//Dans les deux cas on inflige des dégats et si on touche un campement alors on le suprime quand ça vie est >= 0
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

void GameManager::DrawFrameGame(sf::RenderWindow& thewindow) {
	//On commence par regarde si le jeu affiché un HUD ou non
	if (gamePlay && !gamePaused && !gameMenuIsActive) {
		//Si ce n'est pas le cas alors on affiche en premier les missiles
		for (size_t i = 0; i < missilePlayerList.size(); i++) {
			if (missilePlayerList[i] != nullptr) {
				thewindow.draw(missilePlayerList[i]->sprite);
			}
		}
		for (size_t i = 0; i < missileMonsterList.size(); i++) {
			if (missileMonsterList[i] != nullptr) {
				thewindow.draw(missileMonsterList[i]->sprite);
			}
		}

		//On affiche ensuite la liste de monstre
		for (size_t i = 0; i < monsterList.size(); i++) {
			thewindow.draw(monsterList[i]->sprite);
		}

		//Puis on affiche la liste de campement
		for (size_t i = 0; i < campementList.size(); i++) {
			thewindow.draw(campementList[i]->sprite);
		}

		//On vérifie si l'ont doit cacher notre player dans le cas contraire on affiche le player et sa barre de vie
		if (!hidePlayer) {

			thewindow.draw(player.sprite);

			thewindow.draw(healthBarrePlayer.spriteBck);
			thewindow.draw(healthBarrePlayer.spriteFront);
		}

		//On vérifie si l'ont doit cacher notre Boss dans le cas contraire on affiche le boss et sa barre de vie
		if (bossFight) {
			thewindow.draw(boss.sprite);
			thewindow.draw(healthBarreBoss.spriteBck);
			thewindow.draw(healthBarreBoss.spriteFront);
		}
	}

	//On regarde si l'on est au début du jeu si oui on affiche le menu de base (bouton exit et play)
	else if (!gamePlay && gameMenuIsActive) {
		exitButton.SetIsActive(true);
		playButton.SetIsActive(true);
		thewindow.draw(exitButton.sprite);
		thewindow.draw(playButton.sprite);
		thewindow.draw(spriteText);
	}

	//On regarde si l'on a fini le niveau et gagner dans ce cas on affiche le menu de victoire (bouton next level et Exit) 
	//On affiche le bouton next Level seulement si on a pas encore fait le boss fight sinon on affiche seulement le bouton Exit après avoir battu le boss
	else if (!gamePlay && !gamePaused && !lvlLose && !gameMenuIsActive) {
		exitButton.SetIsActive(true);
		if (!bossFight) {
			nextLvlButton.SetIsActive(true);
			thewindow.draw(nextLvlButton.sprite);
		}
		thewindow.draw(exitButton.sprite);
		thewindow.draw(spriteText);
	}

	//On regarde si l'on a fini le niveau et perdu dans ce cas on affiche un bouton retry et exit
	else if (!gamePlay && !gamePaused && lvlLose && !gameMenuIsActive) {
		exitButton.SetIsActive(true);
		retryButton.SetIsActive(true);
		thewindow.draw(exitButton.sprite);
		thewindow.draw(retryButton.sprite);
		thewindow.draw(spriteText);
	}
	
	//Enfin on regarde si l'on a mis le niveau en pause dans ce cas on affiche les boutons resume et exit 
	//ainsi que le joueur, les campement, le player et la liste de monstre (seulement le player et les campement lor du combat de boss)
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


void GameManager::EndGame(bool playerWin)
{
	//On détruit tout les éléments de chaque liste puis on les clear
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

	//On cache notre joueur 
	hidePlayer = true;

	//On fait un switch pour selectionner le text que l'on va afficher en fonction de si l'on a gagner ou perdu
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
	//On passe la variable du jeu a false pour dire qu'on affiche un HUD
	gamePlay = false;
}


void GameManager::ReloadGame()
{
	//On set tout les boutons a non actif
	exitButton.SetIsActive(false);
	resumeButton.SetIsActive(false);
	playButton.SetIsActive(false);
	nextLvlButton.SetIsActive(false);
	retryButton.SetIsActive(false);

	//On reset la life de notre player
	player.SetLife(player.GetMaxLife());

	//Si on est pas en boss fight alors on crée notre liste de monstre
	if (!bossFight) {
		CreateMonsterList();
	}
	//Sinon on place notre boss au milieu de l'écran pour le combat
	else {
		boss.sprite.setPosition(screensizeX / 2 - 50.f, 100.f);
	}

	//On créer notre liste de campement
	CreateCampementList();

	//On passe la variable qui cache le player a false et la variable de gamePlay a true
	hidePlayer = false;
	gamePlay = true;

	//On reset la barre de vie du joueur au maximum
	healthBarrePlayer.SetHealthBarre(player.GetLife(), player.GetMaxLife());
}