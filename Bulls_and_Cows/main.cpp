/*This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is  responsible for all
user interaction. For game logics see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//instantiate a new game

//the entry point for our application
int main()
{
	bool bPlayAgain ;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain=AskToPlayAgain();
	} while (bPlayAgain);

	return 0;// exit the application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game\n";

	std::cout << " ____        _ _                          _    _____                  \n";
	std::cout << "|  _ \\      | | |         /\\             | |  / ____|                 \n";
	std::cout << "| |_) |_   _| | |___     /  \\   _ __   __| | | |     _____      _____ \n";
	std::cout << "|  _ <| | | | | / __|   / /\\ \\ | '_ \\ / _` | | |    / _ \\ \\ /\\ / / __|\n";
	std::cout << "| |_) | |_| | | \\__ \\  / ____ \\| | | | (_| | | |___| (_) \\ V  V /\\__ \\\n";
	std::cout << "|____/ \\__,_|_|_|___/ /_/    \\_\\_| |_|\\__,_|  \\_____\\___/ \\_/\\_/ |___/\n";
	std::cout << "\n";

	std::cout << "\\|/          (__)    \n";
	std::cout << "     `\\------(oo)\n";
	std::cout << "       ||    (__)\n";
	std::cout << "       ||w--||     \\|/\n";
	std::cout << "  \\|/\n";


	std::cout << "Can you guess " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries=BCGame.GetMaxTries();
	
	//loop for the number of turns asking for guesses
	// is not won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		//sumbit valid guess to the game,and receives counts
		FBullCowCount BullCowCount= BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << "Cows=  " << BullCowCount.Cows << "\n\n";
	}

	std::cout << std::endl;

	PrintGameSummary();
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		
		//check status and give feedback
		Status=BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << " Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
			
		}
	
	} while (Status!=EGuessStatus::OK); // Keep looping until we get no errors.
	
	return Guess;
	
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?(y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	
	return (Response[0]=='y')||(Response[0]=='Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done you win!!\n\n";
	}
	else
	{
		std::cout << "Better luck next time :)\n\n";
	}
}

