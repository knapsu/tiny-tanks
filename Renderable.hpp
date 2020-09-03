#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_


#include "SDL/SDL.h"
#include "Collidable.hpp"


/**
 * Klasa reprezentująca obiekt, który może być wyświetlony na ekranie. Klasa abstrakcyjna. DZiedziczy z CCollidable.
 */
class CRenderable :
	public CCollidable
{
/* metody */
public:
	/**
	 * Metoda wyświetlająca obiekt.
	 * @param destination parametr typu SDL_Surface* określający miejsce wyswietlenia obiektu.
	 */
	virtual void Render(SDL_Surface* destination) = 0;

};


#endif
