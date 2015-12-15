#ifndef _AUDIO_HPP_
#define _AUDIO_HPP_


#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>


/**
 * Klasa obslugująca odtwarzanie muzyki.
 */
class CMusic
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CMusic(void);
	
	//~CMusic(void);
	
	/**
	 * Metoda wczytująca muzykę z pliku.
	 * @param file_name parametr typu string zawierający nazwę pliku z którego będzie odtwarzana muzyka.
	 */
	int Load(std::string file_name);
	
	
	/**
	 * Metoda rozpoczynająca odtwarzanie muzyki.
	 */
	void Play(void);
	
	/**
	 * Metoda zatrzymująca odtwarzanie muzyki.
	 */
	void Pause(void);
	
	/**
	 * Metoda wznawiająca odtwarzanie muzyki.
	 */
	void Resume(void);
	
	/**
	 * Metoda zatrzymująca odtwarzanie muzyki.
	 */
	void Toggle(void);
	
	/**
	 * Metoda kończąca odtwarzanie muzyki.
	 */
	void Stop(void);
	

/* składowe */
private:
	Mix_Music* music;
	
};



#endif
