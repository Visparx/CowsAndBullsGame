#include "CAB.h"
#include <map>
#define TMap std::map



CowsAndBullsGame::CowsAndBullsGame() { Reset(); } //конструктор по умолчанию

int CowsAndBullsGame::GetCurrentTry() const { return MyCurrentTry; }
int CowsAndBullsGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool CowsAndBullsGame::IsGameWon() const { return bGameIsWon; }

int CowsAndBullsGame::GetMaxTries() const {
	TMap<int, int> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void CowsAndBullsGame::Reset()
{
	const string HIDDEN_WORD = "parket";		//								!!!!!!!!!!!!!!!!!!!!Ё“ќ ќ“√јƒџ¬ј≈ћќ≈ —Ћќ¬ќ!!!!!!!!!!!!!!!!!!!!!
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

GuessStatus CowsAndBullsGame::CheckGuessValidity(string Guess) const
{
	if (!IsIsogram(Guess))		//проверка на правильность ввода отгадки
	{
		return GuessStatus::Not_Isogram;
	}
	else  if (!IsLowercase(Guess))
	{
		return GuessStatus::Not_Right_Registr;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return GuessStatus::Wrong_Length;
	}
	else
	{
		return GuessStatus::OK;
	}
}

CowsAndBullsCount CowsAndBullsGame::SubmitValidGuess(string Guess)			//увеличение попытки
{
	MyCurrentTry++;
	CowsAndBullsCount CABCount;


	int WordLength = MyHiddenWord.length();
	for (int MHWChar = 0; MHWChar < WordLength; MHWChar++)		//вывод коров и быков
	{

		for (int GChar = 0; GChar < WordLength; GChar++)
		{

			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)		//быки
				{
					CABCount.Bulls++;
				}
				else
				{
					CABCount.Cows++;		//коровы
				}
			}
		}
	}
	if (CABCount.Bulls == WordLength) {		//засчитывание победы, если отгадка верна
		bGameIsWon = true;
	}
	else                    //и незасчитывание победы
	{
		bGameIsWon = false;		
	}
	return CABCount;			//вывод коров и быков
}

bool CowsAndBullsGame::IsIsogram(string Word) const		//проверка, €вл€етс€ ли вводимое слово изограммой
{
	if (Word.length() <= 1) { return true; }
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}return true;
}

bool CowsAndBullsGame::IsLowercase(string Word) const	//проверка нижнего регистра дл€ вводимого слова
{
	for (auto Letter : Word) {
		if (!islower(Letter))
		{
			return false;
		}
		else { return true; }
	}return false;
}
