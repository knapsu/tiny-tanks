#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_


#include "SDL/SDL.h"
#include "Renderable.hpp"


/**
 * Klasa obsługująca animacje wybuchów. Dziedziczy z klasy CRenderable.
 * @see CRenderable
 */
class CAnimation :
	public CRenderable
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CAnimation(void);
	
	/**
	 * Konstruktor.
	 * @param _image parametr typu SDL_Surface* zawierający animowaną grafikę.
	 * @param _x parametr typu int przechowujący współrzędną x wyświetlanej animacji.
	 * @param _y parametr typu int przechowujący współrzędną y wyświetlanej animacji.
	 * @param _number_of_frames parametr typu unsigned short przechowujący liczę klatek animacji.
	 */
	CAnimation(SDL_Surface* _image, int _x, int _y, unsigned short _number_of_frames, bool _render_loop = false);
	
	//~CAnimation(void);
	
	/**
	 * Metoda ustawiająca obrazek z animacją.
	 * @param _image parametr typu SDL_Surface* przechowujący obraz.
	 */
	void SetImage(SDL_Surface* _image);
	
	/**
	 * Metoda wyświetlająca animowany obiekt.
	 * @param destination parametr typu SDL_Surface* określający miejsce wyswietlenia animacji.
	 */
	void Render(SDL_Surface* destination);
	

/* składowe */
private:
	SDL_Surface* image;
	
	unsigned short frame;
	unsigned short number_of_frames;
	bool render_loop;
	
};


#endif
