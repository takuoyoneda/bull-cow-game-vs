#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset();}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4},{ 4, 7 },{ 5, 10 },{ 6, 16 },{ 7, 20 },{ 8, 30 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;

}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receive a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
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
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; 
		} else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}
