#include "FBullCowGame.h"
#include <map>
#define TMap std::map


// to make syntax unreal friendly
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() // default constructor
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLenght() const{ return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLenghtToMaxTries{ {3,4},{4,7} ,{5,10},{6,15},{7,20} };
	return WordLenghtToMaxTries[MyHiddenWord.length()]; 
}


void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bGameIsWon = false;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowercase(Guess)) //if the guess is not all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLenght()!=Guess.length())//if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else//otherwise 
	{
		return EGuessStatus::OK;
	}
	
}

//receives a valid guess, increaments turns, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length();// assuming same lenght as guess

	//loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) 
	{
		//compare letters against the guess word
		for (int32 GChar = 0; GChar < WordLenght; GChar++) 
		{
			//if they match then
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				if (MHWChar == GChar) // if they are in the same place
					BullCowCount.Bulls++; //increment bull

				else
					BullCowCount.Cows++; //increment cow
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as an isogram
	if (Word.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)//for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed cases
		if (LetterSeen[Letter])// if the letter is in the map
		{
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter 
		{
			return false;
		}
	}
	return true;
}
