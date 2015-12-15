#ifndef _TEXT_HPP_
#define _TEXT_HPP_


#include "SDL/SDL_ttf.h"
#include <string>
#include "Renderable.hpp"


/**
 * Klasa reprezentujaca napis. Dziedziczy z klasy CRenderable.
 * @see CRenderable
 */
class CText : 
	public CRenderable
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CText(void);
	
	/**
	 * Konstruktor.
	 * @param font parametr typu TTF_Font* ustawiają czcionke, która jest używana. 
	 * @param style parametr typu int ustawia styl kroju czcionki.
	 * @param r parametr typu Uint8 przechowujący składową red koloru (RGB).
	 * @param g parametr typu Uint8 przechowujący składową green koloru (RGB).
	 * @param b parametr typu Uint8 przechowujący składową blue koloru (RGB).
	 * @param _text parametr typu string przechowujący tekst przeznaczony do wyświetlenia.
	 * @param _x parametr typu int przechowujący współrzedną x tekstu.
	 * @param _y parametr typu int przechowujący współrzedną y tekstu.
	 */
	CText(TTF_Font* font, int style, Uint8 r, Uint8 g, Uint8 b, std::string _text, int _x, int _y);
	
	//~CText(void);
	
	/**
	 * Metoda wyświetlająca sformatowany tekst.
	 * @param destination parametr typu SDL_Surface* zawierajacy miejsce wyswietlenia tekstu.
	 */
	void Render(SDL_Surface* destination);
	
	/**
	 * Metoda ustawiająca napis do wyświetlenia.
	 * @param font parametr typu TTF_Font* ustawiający czcionkę.
	 * @param _text parametr typu string przechowujący tekst przeznaczony do wyświetlenia.
	 * @param _x parametr typu int przechowujący współrzedną x wyświetlanego tekstu.
	 * @param _y parametr typu int przechowujący współrzedną y wyświetlanego tekstu.
	 */
	void SetInscription(TTF_Font* font, std::string _text, int _x, int _y);
	
	/**
	 * Metoda ustawiająca styl dla danej czcionki.
	 * @param font parametr typu TTF_Font* ustawiający czcionkę.
	 * @param style parametr typu int ustawiający styl czcionki.
	 */
	void SetStyle(TTF_Font* font, int style);
	

/* składowe */
private:
	SDL_Surface* text;
	SDL_Color color;
	
};


#endif
