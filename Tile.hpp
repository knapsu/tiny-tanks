#ifndef _TILE_HPP_
#define _TILE_HPP_


#include "SDL/SDL.h"
#include "Renderable.hpp"


/**
 * Klasa przechowująca elementy planszy oraz interfejsu. Dziedziczy z CRendrable.
 * @see Crendreable
 */
class CTile :
	public CRenderable
{
/* metody */
public:
	/**
	 * Konstruktor.
	 * @param _image parametr typu SDL_Surface* przechowujący obraz.
	 * @param _x parametr typu int przechowujący współrzędną x obiektu.
	 * @param _y parametr typu int przechowujący współrzędną y obiektu
	 * @param _flags parametr typu Uint8 opisujący właściwości obiektu.
	 * @param _duration parametr typu int opisujący wytrzymałość obiektu.
	 */
	CTile(SDL_Surface* _image, int _x, int _y, Uint8 _flags, int _duration = 2, bool _base = false);

	//~CTile(void);

	//void OnCollisionActive(Uint8& collision_flags);

	/**
	 * Metoda obsługująca kolizję pasywną (inny obiekt spowodował kolizję).
	 * @param collision_flags parametr typu Uint8 służący do ustalenia sposobu obsługi kolizji.
	 */
	void OnCollisionPassive(Uint8& collision_flags);

	/**
	 * Metoda wyświetlająca obiekt.
	 * @param destination parametr typu SDL_Surface* określający miejsce wyswietlenia obiektu.
	 */
	void Render(SDL_Surface* destination);

	/**
	 * Metoda pobierająca wskaźnik do obrazu.
	 */
	SDL_Surface* GetImage(void);

	/**
	 * Metoda ustawiająca obrazek.
	 * @param _image parametr typu SDL_Surface* przechowujący obraz.
	 */
	void SetImage(SDL_Surface* _image);

	/**
	 * Metoda obsługująca niszczenie obiektu.
	 */
	int OnDestroy(void);

	bool IsBase(void);


/* składowe */
private:
	SDL_Surface* image;
	int duration;

	bool base;
};



#endif
