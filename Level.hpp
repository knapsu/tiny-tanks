#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_


#include <vector>


/**
 * Klasa pomocnicza określająca współrzedne punktu na płaszczyźnie dwuwymiarowej.
 */
class CPoint
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CPoint(void);
	
	/**
	 * Konstruktor.
	 * @param _x parametr typu int przechowujący współrzędną x.
	 * @param _y parametr typu int przechowujący współrzędną y.
	 */
	CPoint(int _x, int _y);
	
	//~CPoint(void);
	

/* składowe */
public:
	int x;
	int y;
	
};


/**
 * Klasa reprezentujaca poziom w grze oraz informacje o nim. 
 */
class CLevel
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CLevel(void);
	
	//~CLevel(void);
	
	/**
	 * Metoda ustawiająca punkt startowy gracza.
	 * @param player_number parametr typu unsigned short, określający numer gracza.
	 * @param _x parametr typy int określający współrzedną x.
	 * @param _y parametr typy int określający współrzedną y.
	 */
	void SetPlayerStartingPoint(unsigned short player_number, int _x, int _y);
	
	/**
	 * Metoda pobierająca startową współrzedną x gracza.
	 * @param player_number parametr typu unsigned short przechowujący numer gracza.
	 */
	int GetPlayerStartingPointX(unsigned short player_number);
	
	/**
	 * Metoda pobierająca startową współrzedną y gracza.
	 * @param player_number parametr typu unsigned short przechowujący numer gracza.
	 */
	int GetPlayerStartingPointY(unsigned short player_number);
	
	/**
	 * Metoda dodająca punkt startowy przeciwnika do wektora enemy_starting_points.
	 * @param _x parametr typy int określający współrzedną x.
	 * @param _y parametr typy int określający współrzedną y.
	 */
	void AddEnemyStartingPoint(int _x, int _y);
	
	/**
	 * Metoda usuwająca wszystkie punkty satrowe przeciwnika z wektora enemy_starting_points.
	 */
	void RemoveEnemyStartingPoints(void);
	
	/**
	 * Metoda pobierająca startową współrzedną x przeciwnika.
	 * @param position parametr typu unsigned int zawierający numer punktu startowego.
	 */
	int GetEnemyStartingPointX(unsigned int position);
	
	/**
	 * Metoda pobierająca startową współrzedną y przeciwnika.
	 * @param position parametr typu unsigned int zawierający numer punktu startowego.
	 */
	int GetEnemyStartingPointY(unsigned int position);
	
	/**
	 * Metoda zwracająca liczbę punktów startowych przeciwnika.
	 */
	int EnemyStartingPoints(void);
	
	/**
	 * Metoda pobierająca numer planszy.
	 */
	unsigned short GetLevelNumber(void);
	
	/**
	 * Metoda ustawiająca numer planszy.
	 * @param _level_number parametr typu unsigned short bedący numerem planszy.
	 */
	void SetLevelNumber(unsigned short _level_number);
	

/* składowe */
public:
	bool base_alive;
	
	unsigned short enemies_active;
	unsigned short enemies_to_deploy;
	
	
private:
	unsigned short level_number;
	
	CPoint player_1_starting_point;
	CPoint player_2_starting_point;
	
	std::vector<CPoint*> enemy_starting_points;
	
};


#endif
