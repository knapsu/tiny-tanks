#ifndef _GAME_HPP_
#define _GAME_HPP_


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "Player.hpp"
#include "Level.hpp"
#include "Tank.hpp"
#include "Tile.hpp"
#include "Bullet.hpp"
#include "Text.hpp"
#include "Audio.hpp"
#include "Animation.hpp"


/**
 * Klasa reprezentująca grę.
 */
class CGame
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CGame(void);

	/**
	 * Destruktor.
	 */
	~CGame(void);

	/**
	 * Główna pętla programu. Silnik gry.
	 */
	int Run(void);

private:
	/**
	 * Metoda wczytująca ustawienia gry.
	 */
	void LoadSettings(void);

	/**
	 * Metoda zapisująca ustawienia gry.
	 */
	void SaveSettings(void);

	/**
	 * Metoda inicjalizująca wszystkie wymagane podsystemy (biblioteki).
	 */
	int Initialize(void);

	/**
	 * Metoda deinicjalizująca wszystkie użyte podsystemy (biblioteki).
	 */
	void Unitialize(void);

	/**
	 * Metoda wczytująca do pamięci używane przez grę zasoby.
	 */
	int LoadResources(void);

	/**
	 * Metoda zwalniająca wszystkie zasoby wczytane metodą LoadResources()
	 */
	void FreeResources(void);

	/**
	 * Metoda ustawiająca początkowe ustawienia dla gracza oraz wczytująca pierwszy poziom gry.
	 */
	void StartGame(void);

	/**
	 * Metoda wczytująca obramowanie planszy oraz panel.
	 */
	void LoadInterface();

	/**
	 * Metoda wczytująca planszę gry.
	 * @param _level_number parametr typu unsigned short zawierający numer poziomu.
	 */
	void LoadLevel(unsigned short _level_number);

	/**
	 * Metoda wczytująca następny poziom.
	 */
	void NextLevel(void);


/* składowe */
private:
	SDL_Surface* screen;

	int screen_width;
	int screen_height;
	int screen_bpp;

	bool running;

	std::map<std::string, SDL_Surface*> image_list;
	std::map<std::string, TTF_Font*> font_list;

	std::vector<CRenderable*> render_list;
	std::vector<CCollidable*> collision_list;

	CPlayer player_1;
	CPlayer player_2;
	CLevel level;
	CMusic music;

};



#endif
