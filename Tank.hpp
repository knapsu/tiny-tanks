#ifndef _TANK_HPP_
#define _TANK_HPP_


#include <cstdlib>
#include "SDL/SDL.h"
#include "Renderable.hpp"


/**
 * Klasa czołgu. Dziedziczy z CRenderable.
 * @see CRenderable
 */
class CTank :
	public CRenderable
{
public:
	/**
	 * Konstruktor domyślny.
	 */
	CTank(void);
	
	/**
	 * Konstruktor.
	 * @param _image parametr typu SDL_Surface* ustawiający grafikę czołgu.
	 * @param _armour parametr typu Uint8 opisujący wytrzymałość pancerza czołgu.
	 * @param _movement_speed parametr typu Uint8 przechowujący predkość poruszania się czolgu.
	 * @param _x parametr typu int przechowujący współrzedną x położenia pocisku.
	 * @param _y parametr typu int przechowujący współrzedną y położenia pocisku.
	 * @param _movement_direction parametr typu Direction zawierający kierunek poruszania się czołgu.
	 */
	CTank(SDL_Surface* _image, short _armour, Uint8 _movement_speed, int _x = 0, int _y = 0, Direction _movement_direction = UP);
	
	//~CTank(void);
	
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
	 * Metoda wyświetlająca obiekt czołgu.
	 * @param destination parametr typu SDL_Surface* określający miejsce wyswietlenia czołgu.
	 */
	virtual void Render(SDL_Surface* destination);
	
	/**
	 * Metoda obsługująca niszczenie obiektu.
	 */
	virtual int OnDestroy(void);
	
	/**
	 * Metoda ustawiająca grafikę czołgu.
	 * @param _image parametr typu SDL_Surface* przechowujący grafikę.
	 */
	void SetImage(SDL_Surface* _image);
	
	/**
	 * Metoda pobierająca wskaźnik do obrazu.
	 */
	SDL_Surface* GetImage(void);
	
	/**
	 * Metoda pobierająca szybkość poruszania się czołgu.
	 */
	Uint8 GetMovementSpeed(void);
	
	/**
	 * Metoda ustwiająca szybkość poruszania sie.
	 * @param _movement_speed parametr typu Uint8 określający prędkość czołgu.
	 */
	void SetMovementSpeed(Uint8 _movement_speed);
	
	/**
	 * Metoda zwracająca aktualny kierunek ruchu.
	 */
	Direction GetMovementDirection(void);
	
	/**Metoda ustwiająca kierunek poruszania się.
	* @param  _movement_direction parametr typu Direction przechowuje kierunek ruchu czołgu.
	*/
	void SetMovementDirection(Direction _movement_direction);
	
	/**
	 * Metoda resetująca połozenie czołgu na planszy.
	 * @param _x parametr typu int przechowujący współrzedną x położenia pocisku.
	 * @param _y parametr typu int przechowujący współrzedną y położenia pocisku.
	 * @param _movement_direction parametr typu Direction przechowujący kierunek ruchu czołgu.
	 */
	void ResetPosition(int _x = 0, int _y = 0, Direction _movement_direction = UP);
	
	/**
	 * Metoda rozpoczynająca ruch czołgu.
	 */
	void StartMoving(void);
	
	/**
	 * Metoda zatrzymująca ruch czołgu.
	 */
	void StopMoving(void);
	
	/**
	 * Metoda przesuwająca obiekt na planszy.
	 */
	void Move(void);
	
	/**
	 * Metoda cofająca ostatnie przesunięcie czołgu.
	 */
	void MoveBack(void);
	
	/**
	 * Metoda sprawdzająca czy czołg strzela.
	 */
	bool IsShooting(void);
	
	/**
	 * Metoda ustawiająca czy czołg strzela.
	 * @param _shooting parametr typu bool przechowujący flage ustawiającą czołg na strzelający.
	 */
	void SetShooting(bool _shooting);
	
	/**
	 * Metoda resetująca licznik czasu strzału.
	 */
	void ResetShootTimer(void);
	
	/**
	 * Metoda pobierajaca licznik czasu strzału.
	 */
	Uint32 GetShootTimer(void);
	
	/**
	 * Metoda ustawiająca licznik czasu strzału.
	 * @param _shoot_timer parametr typu Uint32 przechowujący ilość milisekund.
	 */
	void SetShootTimer(Uint32 _shoot_timer);
	
	/**
	 * Metoda zwracająca ilość milisekund jaka musi minąć pomiędzy kolejnymi strzałami.
	 */
	Uint32 GetShootFrequency(void);
	
	/**Metoda ustawiająca ilość milisekund jaka musi minąć pomiędzy kolejnymi strzałami. 
	*@param _frequency parametr typu Uint32 przechowujący ilość milisekund.
	*/
	void SetShootFrequency(Uint32 _frequency);
	
	/**
	 * Metoda zwracająca siłę pancerza czołgu.
	 */
	short GetArmour(void);
	
	/**
	 * Metoda ustawiająca pancerz czołgu.
	 * @param _armour parametr typu short przechowujący wartość pancerza.
	 */
	void SetArmour(short _armour);
	

/* składowe */
protected:
	SDL_Surface* image;
	short armour;
	Uint8 movement_speed;
	Uint8 movement_timer;
	Uint8 shoot_speed;
	
	Uint32 shoot_timer;
	Uint32 shoot_frequency;
	
	Direction movement_direction;
	bool shooting;
	
};


/**
 * Klasa reprezentująca czołg przeciwnika. Dziedziczy z CTank.
 * @see CTank
 */
class CEnemyTank :
	public CTank
{
public:
	/**
	 *Konstruktor domyślny.
	 */
	CEnemyTank(void);
	
	/**
	 * Konstruktor.
	 * @param _image parametr typu SDL_Surface* ustawiający grafikę czołgu.
	 * @param _armour parametr typu Uint8 opisujący wytrzymałość pancerza czołgu.
	 * @param _movement_speed parametr typu Uint8 przechowujący predkość poruszania się czolgu.
	 * @param _x parametr typu int przechowujący współrzedną x położenia pocisku.
	 * @param _y parametr typu int przechowujący współrzedną y położenia pocisku.
	 * @param _movement_direction parametr typu Direction zawierający kierunek poruszania się czołgu.
	 */
	CEnemyTank(SDL_Surface* _image, short _armour, Uint8 _movement_speed, int _x = 0, int _y = 0, Direction _movement_direction = UP);
	
	//~CEnemyTank(void);
	
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
	 * Metoda odpowiedzialna za sztuczną inteligencję (decyzje o ruchu przeciwnika).
	 * @param colliding parametr typu bool przechowujący informację czy czołg koliduje z innym obiektem.
	 */
	void Think(bool colliding = false);
	
	/**
	 * Metoda przesuwająca obiekt na planszy.
	 */
	void Move();
	
	/**
	 * Metoda obsługująca niszczenie obiektu.
	 */
	int OnDestroy();
	
};


#endif
