#ifndef _COLLIDABLE_HPP_
#define _COLLIDABLE_HPP_


#include "SDL/SDL.h"


typedef enum {
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
} Direction;


enum {
	MOVE_THROUGH = 1,
	NO_MOVE_THROUGH = 2,
	SHOOT_THROUGH = 4,
	NO_SHOOT_THROUGH = 8,
	TANK_PLAYER = 16,
	TANK_COMPUTER = 32,
	BULLET_PLAYER = 64,
	BULLET_COMPUTER = 128,

	// oznaczenia specjalne
	NOT_COLLIDABLE = 0,
	NOT_DESTRUCTABLE = 48,
};


/**
 * Klasa służąca do wyznaczania kolizji oraz ich obsługi.
 */
class CCollidable
{
/* metody */
public:
	/**
	 * Konstruktor domyślny.
	 */
	CCollidable(void);

	//~CCollidable(void);

	/**
	 * Metoda sprawdzająca czy dwa obiekty ze sobą kolidują.
	 * @param object jest obiektem typu CColidable* z którym jest sprawdzana kolizja.
	 */
	virtual bool IsColliding(CCollidable* object);

	/**
	 * Metoda obsługująca kolizję aktywną (obiekt spowodował kolizję).
	 * @param collision_flags parametr typu Uint8 służący do ustalenia sposobu obsługi kolizji.
	 */
	virtual void OnCollisionActive(Uint8& collision_flags);

	/**
	 * Metoda obsługująca kolizję aktywną (inny obiekt spowodował kolizję).
	 * @param collision_flags parametr typu Uint8 służący do ustalenia sposobu obsługi kolizji.
	 */
	virtual void OnCollisionPassive(Uint8& collision_flags);

	/**
	 * Metoda sprawdzająca czy obiekt jest w ruchu.
	 */
	virtual bool IsMoving(void);

	/**
	 * Metoda przesuwająca obiek.
	 */
	virtual void Move(void);

	/**
	 * Metoda sprawdzająca czy obiekt ma zostać zniszczony.
	 */
	bool ToDestroy(void);

	/**
	 * Metoda ustawiająca flage decydującą o zniszczeniu obiektu.
	 * @param _destroy parametr typu bool.
	 */
	void SetDestroy(bool _destroy);

	/**
	 * Metoda obsługująca niszczenie obiektu.
	 */
	virtual int OnDestroy(void);

	/**
	 * Metoda ustawiająca flagi, które charakteryzują obiekt.
	 * @param _flags parametr typu Uint8 przechowujący flagi charakteryzujące obiekt.
	 */
	void SetFlags(Uint8 _flags);

	/**
	 * Metoda zwraca flagi, które charakteryzują obiekt.
	 */
	Uint8 GetFlags(void);

	/**
	 * Metoda pobierająca współrzedną x.
	 */
	int GetX(void);

	/**
	 * Metoda pobierająca współrzedną y.
	 */
	int GetY(void);

	/**
	 * Metoda ustawiająca współrzedną x.
	 */
	void SetX(int _x);

	/**
	 * Metoda ustawiająca współrzedną y.
	 */
	void SetY(int _y);

	/**
	 * Metoda sprawdzająca czy obiekt strzela.
	 */
	virtual bool IsShooting(void);

	/**
	 * Metoda zwracająca wartość licznika czasu strzału.
	 */
	virtual Uint32 GetShootTimer(void);

	/**
	 * Metoda ustawiająca wartość licznika czasu strzału.
	 * @param _shoot_timer  parametr typu Uint32 przechowujący czas w milisekundach.
	 */
	virtual void SetShootTimer(Uint32 _shoot_timer);

	/**
	 * Metoda zwracająca ilość milisekund jaka musi minąć pomiędzy kolejnymi strzałami.
	 */
	virtual Uint32 GetShootFrequency(void);

	/**
	 * Metoda zwracająca aktualny kierunek obiektu.
	 */
	virtual Direction GetMovementDirection(void);


/* składowe */
public:
	int collision_x;
	int collision_y;
	short collision_width;
	short collision_height;

	Uint8 flags;

protected:
	int x;
	int y;

	bool moving;
	//bool shooting;
	bool destroy;
};


#endif
