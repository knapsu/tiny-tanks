#ifndef _CONTROLS_HPP_
#define _CONTROLS_HPP_


#include "SDL/SDL.h"


/**
 * Klasa przechowująca ustawienia klawiszy sterujących.
 */
class CControls
{
/* metody */
public:
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za ruch w góre.
	 */
	int GetKeyUp();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za ruch w góre.
	 * @param _key_up parametr typu int który jest numerem klawisza
	 */
	void SetKeyUp(int _key_up);
	
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za ruch w dół.
	 */
	int GetKeyDown();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za ruch w dół.
	 * @param _key_down parametr typu int który jest numerem klawisza
	 */
	void SetKeyDown(int _key_down);
	
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za ruch w prawo.
	 */
	int GetKeyRight();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za ruch w prawo.
	 * @param _key_right parametr typu int który jest numerem klawisza
	 */
	void SetKeyRight(int _key_right);
	
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za ruch w lewo.
	 */
	int GetKeyLeft();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za ruch w lewo.
	 * @param _key_left parametr typu int który jest numerem klawisza
	 */
	void SetKeyLeft(int _key_left);
	
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za strzał.
	 */
	int GetKeyFire();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za strzał.
	 * @param _key_fire parametr typu int który jest numerem klawisza
	 */
	void SetKeyFire(int _key_fire);
	
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za start.
	 */
	int GetKeyStart();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za start.
	 * @param _key_start parametr typu int który jest numerem klawisza
	 */
	void SetKeyStart(int _key_start);
	
	/**
	 * Metoda pobierająca klawisz odpowiedzialny za wybór.
	 */
	int GetKeySelect();
	
	/**
	 * Metoda ustawiająca klawisz odpowiedzialny za wybór.
	 * @param _key_select parametr typu int który jest numerem klawisza
	 */
	void SetKeySelect(int _key_select);
	

/* składowe */
private:

	/* Uwaga:
	Klawisze są typu int. Pozwala to na przechowywanie (po wcześniejszym
	rzutowaniu) wartości dla klawiszy z klawiatury jak i dla przycisków na
	dzojstiku.
	 */
	 
	int key_up;
	int key_down;
	int key_right;
	int key_left;
	int key_fire;
	int key_start;
	int key_select;
	
};


#endif
