#ifndef _GAME_HPP_
#include "Game.hpp"
#endif



CGame::CGame(void)
{
	running = true;
	LoadSettings();


	if(Initialize() < 0)
	{
        running = false;
	}


	if(LoadResources() < 0)
	{
        running = false;
	}
}


CGame::~CGame(void)
{
	//SaveSettings();
	Unitialize();
}



int CGame::Initialize(void)
{
    /* uruchomienie SDL-a */
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return -1;
    }


	SDL_WM_SetCaption("Tiny Tanks", "");

	screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL);
	if (screen == 0)
	{
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return -1;
	}


	/* Uruchomienie obslugi czcionek*/
	if (TTF_Init() < 0)
	{
		std::cerr << "Error: " << TTF_GetError() << std::endl;
	}


	/* uruchomienie muzyki */
    if (Mix_OpenAudio(44100, AUDIO_U16, 2, 4096) < 0)
    {
        std::cerr << "Error: " << Mix_GetError() << std::endl;
    }

	srand((unsigned)time(0));

	return 0;
}


void CGame::Unitialize(void)
{
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}



int CGame::Run(void)
{
	// sprawdzenie czy wszystkie potrzebne podsystemy zostaly zainicjalizowane
	if (running == false)
	{
		return -1;
	}

	SDL_Event event;

	Uint32 tick = SDL_GetTicks();
	Uint32 last_tick = tick;

	StartGame();

	while (running == true)
	{
		// wyzanczanie następnych klatek animacji
		tick = SDL_GetTicks();

		if (tick < last_tick)
		{
			SDL_Delay(last_tick - tick);
		}


		/* sterowanie */
        while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				player_1.HandleKeyDown_Game(int(event.key.keysym.sym));
				//player_2.HandleKeyDown_Game(int(event.key.keysym.sym));
				break;

			case SDL_KEYUP:
				player_1.HandleKeyUp_Game(int(event.key.keysym.sym));
				//player_2.HandleKeyUp_Game(int(event.key.keysym.sym));

				// Obsługa specjalnych klawiszy
				switch (event.key.keysym.sym)
				{
				case SDLK_F9:
					music.Toggle();
					break;
				case SDLK_F12:
					NextLevel();
					break;
				default:
					break;
				}
				break;

			/* obsługa zdarzeń systemowych */
			case SDL_ACTIVEEVENT:
				break;

			case SDL_QUIT:
				running = false;
				break;
			}
		}


		/* silnik fizyczny */
		for (std::vector<CCollidable*>::reverse_iterator i = collision_list.rbegin(); i != collision_list.rend(); ++i)
		{
			if ((*i)->IsMoving() == false)
			{
				continue;
			}

			(*i)->Move();

			// sprawdz czy nie koliduje
			for (std::vector<CCollidable*>::reverse_iterator j = collision_list.rbegin(); j != collision_list.rend(); ++j)
			{
				if ((*i)->IsColliding(*j) == true)
				{
                    (*i)->OnCollisionActive((*j)->flags);
					(*j)->OnCollisionPassive((*i)->flags);

				}
			}
		}


		// niszczenie obiektów
		for (std::vector<CRenderable*>::iterator i = render_list.begin(); i != render_list.end();)
		{
			if ((*i)->ToDestroy() == true)
			{
				render_list.erase(i);
			}
			else
			{
				++i;
			}
		}

		for (std::vector<CCollidable*>::iterator i = collision_list.begin(); i != collision_list.end();)
		{
			if ((*i)->ToDestroy() == true)
			{
                switch ((*i)->OnDestroy())
                {
				case 1:
					// śmierć pierwszego gracza
					player_1.DecreaseLifes();

					{
						CAnimation* new_animation = new CAnimation(image_list["explosion"], player_1.tank.GetX(), player_1.tank.GetY(), 16);
						new_animation->SetFlags(NOT_COLLIDABLE);
						render_list.push_back(new_animation);
					}

					++i;
					if (player_1.GetLifes() == 0)
					{
						break;
					}

					player_1.tank.StopMoving();
					player_1.tank.SetDestroy(false);
					player_1.tank.ResetPosition(level.GetPlayerStartingPointX(1), level.GetPlayerStartingPointY(1));
					player_1.tank.SetArmour(1);
					render_list.push_back(&player_1.tank);

					break;
				case 2:
					// śmierć drugiego gracza
					// ...
					break;
                case 3:
					// śmierć przeciwnika
					--level.enemies_active;

					{
						CAnimation* new_animation = new CAnimation(image_list["explosion"], (*i)->GetX(), (*i)->GetY(), 16);
						new_animation->SetFlags(NOT_COLLIDABLE);
						render_list.push_back(new_animation);
					}

					delete (*i);
					collision_list.erase(i);
					break;
				case 10:
					player_1.ResetLifes(0);

                default:
					// zniszczenie innych obiektów
					delete (*i);
					collision_list.erase(i);
					break;
                }
			}
			else
			{
				++i;
			}
		}


		// procedury strzału
		for (std::vector<CRenderable*>::iterator i = render_list.begin(); i != render_list.end(); ++i)
		{
			if ((*i)->IsShooting() == true)
			{
				if (SDL_GetTicks() >= (*i)->GetShootTimer())
				{
					(*i)->SetShootTimer(SDL_GetTicks() + (*i)->GetShootFrequency());

					CBullet* new_bullet;
					switch ((*i)->GetMovementDirection())
					{
					case UP:
						new_bullet = new CBullet(image_list["bullet"], 10, (*i)->GetX() + 17, (*i)->GetY() - 6, UP);
						break;
					case DOWN:
						new_bullet = new CBullet(image_list["bullet"], 10, (*i)->GetX() + 17, (*i)->GetY() + 40, DOWN);
						break;
					case RIGHT:
						new_bullet = new CBullet(image_list["bullet"], 10, (*i)->GetX() + 40, (*i)->GetY() + 17, RIGHT);
						break;
					case LEFT:
						new_bullet = new CBullet(image_list["bullet"], 10, (*i)->GetX() - 6, (*i)->GetY() + 17, LEFT);
						break;
					}

					if ((*i)->flags & TANK_PLAYER)
					{
						new_bullet->SetFlags(BULLET_PLAYER);
					}
					else if ((*i)->flags & TANK_COMPUTER)
					{
						new_bullet->SetFlags(BULLET_COMPUTER);
					}

					render_list.push_back(new_bullet);
					collision_list.push_back(new_bullet);
				}
			}
		}


		// tworzenie przeciwników
		if ((level.enemies_to_deploy == 0) && (level.enemies_active == 0))
		{
			NextLevel();
		}
		else if ((level.enemies_active < 3) && (level.enemies_to_deploy > 0))
		{
			for (int i = 0; i < level.EnemyStartingPoints(); ++i)
			{
				CCollidable deploy_rectangle;
				deploy_rectangle.SetX(level.GetEnemyStartingPointX(i));
				deploy_rectangle.SetY(level.GetEnemyStartingPointY(i));
				deploy_rectangle.collision_x = deploy_rectangle.GetX();
				deploy_rectangle.collision_y = deploy_rectangle.GetY();
				deploy_rectangle.collision_width = 40;
				deploy_rectangle.collision_height = 40;

				bool can_deploy = true;
				for (std::vector<CCollidable*>::iterator j = collision_list.begin(); j != collision_list.end(); ++j)
				{
					if (deploy_rectangle.IsColliding(*j) == true)
					{
						can_deploy = false;
						break;
					}
				}

				if (can_deploy == true)
				{
					CEnemyTank* new_enemy_tank;
                    new_enemy_tank = new CEnemyTank(image_list["tank_green"], 1, 2, level.GetEnemyStartingPointX(i), level.GetEnemyStartingPointY(i), DOWN);
                    new_enemy_tank->SetFlags(TANK_COMPUTER | NO_MOVE_THROUGH | NO_SHOOT_THROUGH);
                    new_enemy_tank->StartMoving();

                    --level.enemies_to_deploy;

                    render_list.push_back(new_enemy_tank);
                    collision_list.push_back(new_enemy_tank);

                    ++level.enemies_active;
					break;
				}
			}
		}


		/* silnik graficzny */
		for (std::vector<CRenderable*>::iterator i = render_list.begin(); i != render_list.end(); ++i)
		{
			(*i)->Render(screen);
		}
		SDL_Flip(screen);


		// sprawdzenie czy koniec gry
		if (player_1.GetLifes() == 0 )
		 // && (player_2.GetLifes() == 0) || level.base_alive == false)
		{
			music.Stop();
			SDL_Delay(1500);
			music.Play();
			StartGame();
		}


		last_tick = SDL_GetTicks() + 20;
	}

	running = true;


	return 0;
}


void CGame::StartGame(void)
{
	// czyszczenie render_list i collision_list
	for (std::vector<CRenderable*>::iterator i = render_list.begin(); i != render_list.end(); ++i)
    {
		if ((*i)->GetFlags() == player_1.tank.GetFlags())
		{
			continue;
		}

		delete (*i);
	}
	render_list.clear();
	collision_list.clear();


	// ustawienia dla gracza 1
	player_1.ResetLifes();
	player_1.ResetScore();
	player_1.tank.SetImage(image_list["tank_yellow"]);
	player_1.tank.SetFlags(TANK_PLAYER | NO_MOVE_THROUGH | NO_SHOOT_THROUGH);
	player_1.tank.SetMovementSpeed(5);
	player_1.tank.SetShootFrequency(1000);
	player_1.tank.SetArmour(1);


	// ustawienia dla gracza 2
	//player_2.ResetLifes();
	//player_2.tank.SetImage(image_list["tank_yellow"]);
	//player_2.tank.SetFlags(TANK_PLAYER | NO_MOVE_THROUGH | NO_SHOOT_THROUGH);
	//player_2.tank.SetMovementSpeed(5);
	//player_2.tank.SetShootFrequency(1000);
	//player_2.tank.SetArmour(1);


	// wczytanie muzyki
	music.Load("music/music.ogg");
	music.Play();

	//wczytanie mapy oraz pozostałych elementów wyświetlanych na mapie
	level.SetLevelNumber(1);
	level.base_alive = true;
	LoadInterface();
	LoadLevel(level.GetLevelNumber());

}


void CGame::LoadInterface(void)
{
	{
		CTile* new_tile;

		// obramowanie planszy gry
		new_tile = new CTile(image_list["border_horizontal"], 15, 0, NO_MOVE_THROUGH | NO_SHOOT_THROUGH | NOT_DESTRUCTABLE);
		render_list.push_back(new_tile);
		collision_list.push_back(new_tile);
		new_tile = new CTile(image_list["border_horizontal"], 15, 535, NO_MOVE_THROUGH | NO_SHOOT_THROUGH | NOT_DESTRUCTABLE);
		render_list.push_back(new_tile);
		collision_list.push_back(new_tile);
		new_tile = new CTile(image_list["border_vertical"], 0, 15, NO_MOVE_THROUGH | NO_SHOOT_THROUGH | NOT_DESTRUCTABLE);
		render_list.push_back(new_tile);
		collision_list.push_back(new_tile);
		new_tile = new CTile(image_list["border_vertical"], 535, 15, NO_MOVE_THROUGH | NO_SHOOT_THROUGH | NOT_DESTRUCTABLE);
		render_list.push_back(new_tile);
		collision_list.push_back(new_tile);

		new_tile = new CTile(image_list["corner_left_up"], 0, 0, NOT_COLLIDABLE);
		render_list.push_back(new_tile);
		new_tile = new CTile(image_list["corner_right_up"], 535, 0, NOT_COLLIDABLE);
		render_list.push_back(new_tile);
		new_tile = new CTile(image_list["corner_left_down"], 0, 535, NOT_COLLIDABLE);
		render_list.push_back(new_tile);
		new_tile = new CTile(image_list["corner_right_down"], 535, 535, NOT_COLLIDABLE);
		render_list.push_back(new_tile);


		// panel
		new_tile = new CTile(image_list["panel"], 550, 0, NOT_COLLIDABLE);
		render_list.push_back(new_tile);

        CText* new_text;
        std::stringstream ss;

        new_text = new CText(font_list["main_font"],TTF_STYLE_NORMAL, 255, 0, 0, "Poziom:", 565, 30);
        render_list.push_back(new_text);
        ss << level.GetLevelNumber();
        new_text = new CText(font_list["main_font"],TTF_STYLE_NORMAL, 255, 0, 0, ss.str(), 660, 30);
        render_list.push_back(new_text);

        /*new_text = new CText(font_list["main_font"],TTF_STYLE_NORMAL, 255, 0, 0, "Życia:", 565, 70);
        render_list.push_back(new_text);
		ss.str("");
        ss << player_1.GetLifes();
        new_text = new CText(font_list["main_font"],TTF_STYLE_NORMAL, 255, 0, 0, ss.str(), 660, 70);
        render_list.push_back(new_text);*/

        /*new_text = new CText(font_list["main_font"],TTF_STYLE_NORMAL, 255, 0, 0, "Punkty:", 565, 110);
        render_list.push_back(new_text);
        ss.str("");
        ss << player_1.GetScore();
        new_text = new CText(font_list["main_font"],TTF_STYLE_NORMAL, 255, 0, 0, ss.str(), 660, 110);
        render_list.push_back(new_text);*/
	}
}



void CGame::LoadLevel(unsigned short _level_number)
{
	std::stringstream ss;
	ss << "maps/level_";
	ss.width(2);
	ss.fill('0');
	ss << _level_number;
	ss << ".map";

	std::string file_name = ss.str();
	std::ifstream file (file_name.c_str());


	if (file.is_open() == false)
	{
		std::cerr << "Can not open map file \'" << file_name << "\'." << std::endl;
	}

	char tile_type;

	// numer kafelka na osi x i y (pomocne przy wyliczaniu współrzędnych dodawanego obiektu)
	int x_tiles = 0;
	int y_tiles = 0;

	while (file.get(tile_type))
	{
		CTile* new_tile;
		// wczytanie obiektu do render_list
		switch (tile_type)
		{
		case ' ': // pusty
			new_tile = new CTile(image_list["empty"], x_tiles*40 + 15, y_tiles*40 + 15, NOT_COLLIDABLE);
			render_list.push_back(new_tile);
			break;
		case 'm': // mur
			new_tile = new CTile(image_list["empty"], x_tiles*40 + 15, y_tiles*40 + 15, NOT_COLLIDABLE);
			render_list.push_back(new_tile);
			new_tile = new CTile(image_list["wall"], x_tiles*40 + 15, y_tiles*40 + 15, NO_MOVE_THROUGH | NO_SHOOT_THROUGH);
			render_list.push_back(new_tile);
			collision_list.push_back(new_tile);
			break;
		case 'w': // woda
			new_tile = new CTile(image_list["water"], x_tiles*40 + 15, y_tiles*40 + 15, NO_MOVE_THROUGH | SHOOT_THROUGH);
			render_list.push_back(new_tile);
			collision_list.push_back(new_tile);
			break;
		case 's': // stal
			new_tile = new CTile(image_list["steel"], x_tiles*40 + 15, y_tiles*40 + 15, NO_MOVE_THROUGH | NO_SHOOT_THROUGH | NOT_DESTRUCTABLE);
			render_list.push_back(new_tile);
			collision_list.push_back(new_tile);
			break;
		case '0': // punkt startowy komputera
			level.AddEnemyStartingPoint(x_tiles*40 + 15, y_tiles*40 + 15);
			new_tile = new CTile(image_list["empty"], x_tiles*40 + 15, y_tiles*40 + 15, NOT_COLLIDABLE);
			render_list.push_back(new_tile);
			break;
		case '1': // punkt startowy gracza 1
			level.SetPlayerStartingPoint(1, x_tiles*40 + 15, y_tiles*40 + 15);
			new_tile = new CTile(image_list["empty"], x_tiles*40 + 15, y_tiles*40 + 15, NOT_COLLIDABLE);
			render_list.push_back(new_tile);
			break;
		case '2': // punkt startowy gracza 2
			level.SetPlayerStartingPoint(2, x_tiles*40 + 15, y_tiles*40 + 15);
			new_tile = new CTile(image_list["empty"], x_tiles*40 + 15, y_tiles*40 + 15, NOT_COLLIDABLE);
			render_list.push_back(new_tile);
			break;
		case 'b': // baza
			new_tile = new CTile(image_list["empty"], x_tiles*40 + 15, y_tiles*40 + 15, NOT_COLLIDABLE);
			render_list.push_back(new_tile);
			new_tile = new CTile(image_list["base"], x_tiles*40 + 15, y_tiles*40 + 15, NO_MOVE_THROUGH | NO_SHOOT_THROUGH, 1, true);
			render_list.push_back(new_tile);
			collision_list.push_back(new_tile);
			break;
		default:
			break;
		}

		if (x_tiles == 13)
		{
			x_tiles = 0;
			y_tiles += 1;
		}
		else
		{
			x_tiles += 1;
		}
	}

	file.close();


	player_1.tank.SetX(level.GetPlayerStartingPointX(1));
	player_1.tank.SetY(level.GetPlayerStartingPointY(1));
	player_1.tank.SetMovementDirection(UP);
	player_1.tank.StopMoving();
	render_list.push_back(&(player_1.tank));
	collision_list.push_back(&(player_1.tank));

	/*player_2.tank.SetX(level.GetPlayerStartingPointX(2));
	player_2.tank.SetY(level.GetPlayerStartingPointY(2));
	player_2.tank.SetMovementDirection(UP);
	player_2.tank.StopMoving();
	render_list.push_back(&(player_2.tank));
	collision_list.push_back(&(player_2.tank));*/

	level.enemies_active = 0;
	level.enemies_to_deploy = 10;
}



void CGame::NextLevel(void)
{
	// czyszczenie render_list i collision_list
	/*
	  render list musi zostać cały usunięty bo niektóre obiekty są tylko
	  animowane ui nie ma ich w collision list
    */

	for (std::vector<CRenderable*>::iterator i = render_list.begin(); i != render_list.end(); ++i)
    {
		if ((*i)->GetFlags() == player_1.tank.GetFlags())
		{
			continue;
		}

		delete (*i);
	}
	render_list.clear();

	collision_list.clear();


	if (level.GetLevelNumber() == 15)
	{
		level.SetLevelNumber(1);
	}
	else
	{
		level.SetLevelNumber(level.GetLevelNumber() + 1);
	}

	level.RemoveEnemyStartingPoints();
	LoadInterface();
	LoadLevel(level.GetLevelNumber());
}


int CGame::LoadResources(void)
{
	// obrazki
    image_list["tank_yellow"] = IMG_Load("images/tank_yellow.png");
    if(image_list["tank_yellow"] == 0)
    {
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["tank_green"] = IMG_Load("images/tank_green.png");
	if(image_list["tank_green"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
	}

	image_list["empty"] = IMG_Load("images/empty.png");
	if(image_list["empty"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["wall"] = IMG_Load("images/wall.png");
    if(image_list["wall"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
	}

	image_list["water"] = IMG_Load("images/water.png");
	if(image_list["water"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["steel"] = IMG_Load("images/steel.png");
	if(image_list["steel"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

    image_list["base"] = IMG_Load("images/base.png");
	if(image_list["base"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["border_horizontal"] = IMG_Load("images/border_horizontal.png");
	if(image_list["border_horizontal"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["border_vertical"] = IMG_Load("images/border_vertical.png");
	if(image_list["border_vertical"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["corner_left_up"] = IMG_Load("images/corner_left_up.png");
	if(image_list["corner_left_up"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["corner_left_down"] = IMG_Load("images/corner_left_down.png");
	if(image_list["corner_left_down"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["corner_right_up"] = IMG_Load("images/corner_right_up.png");
	if(image_list["corner_right_up"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["corner_right_down"] = IMG_Load("images/corner_right_down.png");
	if(image_list["corner_right_down"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["bullet"] = IMG_Load("images/bullet.png");
	if(image_list["bullet"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }

	image_list["panel"] = IMG_Load("images/panel.png");
	if(image_list["panel"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }


    // animacje
    image_list["explosion"] = IMG_Load("images/explosion.png");
	if(image_list["explosion"] == 0)
	{
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        return -1;
    }


	// czcionki
	font_list["main_font"] = TTF_OpenFont("fonts/ubuntu-font-family/Ubuntu-R.ttf", 24);
	if (font_list["main_font"] == 0)
	{
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		return -1;
	}

	return 0;
}


void CGame::FreeResources(void)
{
	for (std::vector<CRenderable*>::iterator i = render_list.begin(); i != render_list.end(); ++i)
    {
		delete (*i);
	}
	render_list.clear();

	for (std::vector<CCollidable*>::iterator i = collision_list.begin(); i != collision_list.end(); ++i)
    {
		delete (*i);
	}
	collision_list.clear();


	delete image_list["tank_yellow"];
	delete image_list["tank_green"];
	delete image_list["empty"];
	delete image_list["wall"];
	delete image_list["water"];
	delete image_list["steel"];
	delete image_list["base"];
	delete image_list["explosion"];
	delete image_list["border_horizontal"];
	delete image_list["border_vertical"];
	delete image_list["corner_left_up"];
	delete image_list["corner_left_down"];
	delete image_list["corner_right_up"];
	delete image_list["corner_right_down"];
	delete image_list["bullet"];
	delete image_list["panel"];
	image_list.clear();


	TTF_CloseFont(font_list["Vera Sans"]);
	font_list.clear();
}


void CGame::LoadSettings(void)
{
    std::ifstream file ("settings.ini");

    if(file.is_open() == false)
    {
        // jesli plik nie może zostać otwarty to użyte zostaną wartości domyślne
        screen_width = 700;
	    screen_height = 550;
        screen_bpp = 16;
		player_1.controls.SetKeyUp(SDLK_UP);
		player_1.controls.SetKeyDown(SDLK_DOWN);
		player_1.controls.SetKeyRight(SDLK_RIGHT);
		player_1.controls.SetKeyLeft(SDLK_LEFT);
		player_1.controls.SetKeyFire(SDLK_SPACE);
		player_1.controls.SetKeyStart(SDLK_RETURN);
		player_1.controls.SetKeySelect(SDLK_TAB);

        player_2.controls.SetKeyUp(SDLK_w);
        player_2.controls.SetKeyDown(SDLK_s);
        player_2.controls.SetKeyLeft(SDLK_a);
        player_2.controls.SetKeyRight(SDLK_d);
        player_2.controls.SetKeyFire(SDLK_f);
        player_2.controls.SetKeySelect(SDLK_e);
        player_2.controls.SetKeyStart(SDLK_q);

    }
    else
    {
        std::stringstream ss;
        std::string wyraz;
        int liczba;

        // [GENERAL]
        file >> wyraz;

        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss.str(wyraz);
                ss >> liczba;
                screen_width = liczba;
            }
        }

        std::stringstream ss1;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss1.str(wyraz);
                ss1 >> liczba;
                screen_height = liczba;
            }
        }

        std::stringstream ss2;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss2.str(wyraz);
                ss2 >> liczba;
                screen_bpp = liczba;
            }
        }

        // [PLAYER1]
        file >> wyraz;

        std::stringstream ss11;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss11.str(wyraz);
                ss11 >> liczba;
                player_1.controls.SetKeyUp(liczba);
            }
        }

        std::stringstream ss12;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss12.str(wyraz);
                ss12 >> liczba;
                player_1.controls.SetKeyDown(liczba);
            }
        }

        std::stringstream ss13;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss13.str(wyraz);
                ss13 >> liczba;
                player_1.controls.SetKeyLeft(liczba);
            }
        }

        std::stringstream ss14;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss14.str(wyraz);
                ss14 >> liczba;
                player_1.controls.SetKeyRight(liczba);
            }
        }

        std::stringstream ss15;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss15.str(wyraz);
                ss15 >> liczba;
                player_1.controls.SetKeyFire(liczba);
            }
        }

        std::stringstream ss16;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss16.str(wyraz);
                ss16 >> liczba;
                player_1.controls.SetKeyStart(liczba);
            }
        }

        std::stringstream ss17;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss17.str(wyraz);
                ss17 >> liczba;
                player_1.controls.SetKeySelect(liczba);
            }
        }

        // [PLAYER2]
        file >> wyraz;
        std::stringstream ss21;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss21.str(wyraz);
                ss21 >> liczba;
                player_2.controls.SetKeyUp(liczba);
            }
        }

        std::stringstream ss22;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss22.str(wyraz);
                ss22 >> liczba;
                player_2.controls.SetKeyDown(liczba);
            }
        }

        std::stringstream ss23;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss23.str(wyraz);
                ss23 >> liczba;
                player_2.controls.SetKeyLeft(liczba);
            }
        }

        std::stringstream ss24;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss24.str(wyraz);
                ss24 >> liczba;
                player_2.controls.SetKeyRight(liczba);
            }
        }

        std::stringstream ss25;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss25.str(wyraz);
                ss25 >> liczba;
                player_2.controls.SetKeyFire(liczba);
            }
        }

        std::stringstream ss26;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss26.str(wyraz);
                ss26 >> liczba;
                player_2.controls.SetKeyStart(liczba);
            }
        }

        std::stringstream ss27;
        for(int i = 0;i<3;i++)
        {
            file >> wyraz;
            if(i == 2)
            {
                ss27.str(wyraz);
                ss27 >> liczba;
                player_2.controls.SetKeySelect(liczba);
            }
        }

        file.close();
    }
}


void CGame::SaveSettings(void)
{
    std::ofstream file ("settings.ini");

    file << "[GENERAL]" << std::endl;
    file << "width = " << screen_width << std::endl;
    file << "height = " << screen_height << std::endl;
    file << "bpp = " << screen_bpp << std::endl << std::endl;
    file << "[PLAYER1]" << std::endl;
    file << "up = " << player_1.controls.GetKeyUp() << std::endl;
    file << "down = " << player_1.controls.GetKeyDown() << std::endl;
    file << "left = " << player_1.controls.GetKeyLeft() << std::endl;
    file << "right = " << player_1.controls.GetKeyRight() << std::endl;
    file << "fire = " << player_1.controls.GetKeyFire() << std::endl;
    file << "start = " << player_1.controls.GetKeyStart() << std::endl;
    file << "select = " << player_1.controls.GetKeySelect() << std::endl << std::endl;;
    file << "[PLAYER2]" << std::endl;
    file << "up = " << player_2.controls.GetKeyUp() << std::endl;
    file << "down = " << player_2.controls.GetKeyDown() << std::endl;
    file << "left = " << player_2.controls.GetKeyLeft() << std::endl;
    file << "right = " << player_2.controls.GetKeyRight() << std::endl;
    file << "fire = " << player_2.controls.GetKeyFire() << std::endl;
    file << "start = " << player_2.controls.GetKeyStart() << std::endl;
    file << "select = " << player_2.controls.GetKeySelect() << std::endl;
}


