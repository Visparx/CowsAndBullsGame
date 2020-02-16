/* Логика игры и никакого прямого взаимодействия с пользователем
Игра основана на отгадке слов
*/

#pragma once
#include <string>
//чтобы сделать синтаксис более "анрилальным"
using string = std::string;


struct CowsAndBullsCount //изначальные значения коров и быков
{
	int Bulls = 0;
	int Cows = 0;
};

enum class GuessStatus	// все возможные статусы после ввода слова
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Right_Registr,
	NotEnglishLanguage,
};

class CowsAndBullsGame	// КЛАСС
{
public:
	CowsAndBullsGame(); // конструктор

	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	GuessStatus CheckGuessValidity(string) const;

	void Reset();

	CowsAndBullsCount SubmitValidGuess(string);



private:
	// смотри конструктор
	int MyCurrentTry;
	string MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(string) const;
	bool IsLowercase(string) const;
};
