#ifndef _BULLET_HPP_
#define _BULLET_HPP_


#include "SDL/SDL.h"
#include "Tank.hpp"


/**
 * Klasa reprezentująca pocisk. Dziedziczy z CRenderable.
 * @see CRenderable
 */
class CBullet :
	public CRenderable
{
/* metody */
public:
	/**
	 * Konstruktor.
	 * @param _image parametr typu SDL_Surface* ustawiający grafikę obiektu pocisku.
	 * @param _movement_speed parametr typu Uint8 ustawiający prędkość lotu pocisku.
	 * @param _x parametr typu int ustawijacy współrzedną x położenia pocisku.
	 * @param _y parametr typu int ustawijacy współrzedną y położenia pocisku.
	 * @param _movement_direction parametr typu Direction ustawiający kierunek poruszania się pocisku.
	 */
	CBullet(SDL_Surface* _image, Uint8 _movement_speed, int _x, int _y, Direction _movement_direction);
	
	//~CBullet(void);
	
	/**
	 * Metoda wyświetlająca obiekt pocisku.
	 * @param destination parametr typu SDL_Surface* określający miejsce wyswietlenia pocisku.
	 */
	void Render(SDL_Surface* destination);
	
	/**
	 * Metoda obsługująca kolizję aktywną (obiekt pocisku spowodował kolizję).
	 * @param collision_flags parametr typu Uint8 służący do ustalenia sposobu obsługi kolizji.
	 */
	void OnCollisionActive(Uint8& collision_flags);
	
	/**
	 * Metoda obsługująca kolizję pasywną (inny obiekt spowodował kolizję).
	 * @param collision_flags parametr typu Uint8 służący do ustalenia sposobu obsługi kolizji.
	 */
	void OnCollisionPassive(Uint8& collision_flags);
	
	/**
	 * Metoda obsługująca niszczenie obiektu.
	 */
	int OnDestroy(void);
	
	/**
	 * Metoda przesuwająca obiekt.
	 */
	void Move(void);
	

/* składowe */
private:
	SDL_Surface* image;
	
	unsigned short movement_speed;
	Direction movement_direction;
	
};


#endif
