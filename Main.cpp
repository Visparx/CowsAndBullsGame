/* ��� ����������� ����.
��� �������� �� �� �������������� � �������������.
��� ������� ������ ������ ���� CowsAndBullsGame.
*/
#pragma once

#include <iostream>
#include <string>	
#include "CAB.h"


using Text = std::string;


int main();
//����� ��� ������, ����� �������� � ���������
void PrintIntro();
void PlayGame();
void PrintGameSummary();
Text GetValidGuess();
bool AskToPlayAgain();

CowsAndBullsGame CABGame; // ������ ����� ����, ������� �������� ������������ �� ����� ����

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a funny word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << CABGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
//����������� ���� ���� �� ���������
void PlayGame()
{
	CABGame.Reset();
	int MaxTries = CABGame.GetMaxTries();
	//�������� ����, ���������� �������, ���� �� �������� ���� � ���� �������� �������
	while (!CABGame.IsGameWon() && CABGame.GetCurrentTry() <= MaxTries)
	{
		Text Guess = GetValidGuess();
		CowsAndBullsCount CABCount = CABGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << CABCount.Bulls;
		std::cout << ". Cows = " << CABCount.Cows << "\n\n";
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}
// ���������� ����, ���� ������������ �� ���� ������ �������
Text GetValidGuess()
{
	Text Guess = "";
	GuessStatus Status = GuessStatus::Invalid_Status;
	do {
		// ��������� ������� �� ������
		int CurrentTry = CABGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << CABGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = CABGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case GuessStatus::Wrong_Length:
			std::cout << "Please enter a " << CABGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case GuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case GuessStatus::Not_Right_Registr:
			std::cout << "Please enter with a low registr.\n";
			break;
		default:
			//�������������, ��� �������� ������ �������
			break;
		}
	} while (Status != GuessStatus::OK); //���������� ��������� ���� �� ��� ���, ���� �� ����� ��������� ��������
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again with the same hidden word (y/n)? ";
	Text Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary()
{
	if (CABGame.IsGameWon()) { std::cout << "CONGRATULATIONS, YOU WON\n"; }
	else { std::cout << "Oops, try again\n"; }
}

