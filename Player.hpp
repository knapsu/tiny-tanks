#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_


#include "SDL/SDL.h"
#include "Controls.hpp"
#include "Tank.hpp"


/**
 * Klasa będąca obiektem reprezentującym gracza.
 */
class CPlayer
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CPlayer(void);

	//~CPlayer(void);

	//bool HandleKeyDown_Menu(int key);

	/**
	 * Metoda obsługująca zdarzenia związane z wciśnięciem klawisza podczas właściwej gry.
	 * @param key parametr typu int zawierający numer wciśniętego klawisza.
	 */
	bool HandleKeyDown_Game(int key);

	/**
	 * Metoda obsługująca zdarzenia związane z puszczeniem klawisza podczas właściwej gry.
	 * @param key parametr typu int zawierający numer puszczonego klawisza.
	 */
	bool HandleKeyUp_Game(int key);

	/**
	 * Metoda pobierająca liczbę punktów.
	 */
	unsigned long GetScore(void);

	/**
	 * Metoda resetująca liczbę punktów.
	 */
	void ResetScore(void);

	/**
	 * Metoda zwiekszająca liczbę punktów.
	 * @param points typu unsigned long przechowujący liczbę punktów o którą należy zwiększyc wynik.
	 */
	void IncreaseScore(unsigned long points);

	/**
	 * Metoda pobierająca liczbę żyć.
	 */
	unsigned short GetLifes(void);

	/**
	 * Metoda resetująca liczbę żyć.
	 * @param _lifes typu unsigned short przechowujący liczbę żyć do której resetujemy.
	 */
	void ResetLifes(unsigned short _lifes = 3);

	/**
	 * Metoda zwiększająca liczbę żyć.
	 */
	void IncreaseLifes(void);

	/**
	 * Metoda zmniejszająca liczbę żyć.
	 */
	void DecreaseLifes(void);


/* składowe */
public:
	CControls controls;
	CTank tank;

private:
	unsigned long score;
	unsigned short lifes;

};


#endif
