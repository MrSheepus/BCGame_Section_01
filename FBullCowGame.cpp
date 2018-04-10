#pragma once
#include "FBullCowGame.h"
#include <map>

//	unreal coding standards
#define TMap std::map
using int32 = int;

FBullCowgame::FBullCowgame() { Reset(); } // default constructor	

int32 FBullCowgame::GetCurrentTry() const	{	return MyCurrentTry;	}
int32 FBullCowgame::GetHiddenWordLength() const	{	return MyHiddenWord.length();	}
bool FBullCowgame::IsGameWon() const	{	return bGameIsWon;	}


int32 FBullCowgame::GetMaxTries() const	{	
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,5}, {5,7}, {6,10}, {7,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowgame::Reset()
{
	const FString HIDDEN_WORD = "planet";	// this must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


 EGuessStatus FBullCowgame::CheckGuessValidity(FString Guess) const
{
	 if (!IsIsogram(Guess)) // if he guess isn't an isogram
	 {
		 return EGuessStatus::Not_Isogram; // return an error	
	 }
	 else if (!IsLowercase(Guess))	// if the guess isn't all lowercase
	 {
		 return EGuessStatus::Not_Lowercase; // return error	
	 }
	 else if (Guess.length() != GetHiddenWordLength())	// if the guess length is wrong
	 {
		 return EGuessStatus::Wrong_Length; // return error	 
	 }
	 else // otherwise
	 {
		 return EGuessStatus::OK; // return OK
	 }
	
}

// recieved a VALID guess, increments turn and returns count
FBullCowCount FBullCowgame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();	// assuming same length as guess

	// loop through all letters in the guess
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) // if they're in same place
				{
					BullCowCount.Bulls++; // increment bulls if they are in the same place
				}
				else
				{
					BullCowCount.Cow++; // increment cows if not
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



bool FBullCowgame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)	// for all letters of the word
	{
		Letter = tolower(Letter);	// handle mixed case
		if (LetterSeen[Letter])		// if the letter is in the map	
		{					
			return false; // we do NOT have isogram
		}
		else
		{
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}
			
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowgame::IsLowercase(FString Word) const
{
	for (auto letter : Word)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}
