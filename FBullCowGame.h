/* The game logic	(no view code or direct user interaction)
The game is simple guess the word game
*/

#pragma once
#include <string>

//	unreal coding standards
using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cow = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowgame
{
public:
	FBullCowgame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};

