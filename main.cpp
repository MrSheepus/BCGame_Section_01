/* This is console executable, that makes use of BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame Class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//	unreal coding standards
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowgame BCGame; //instance

//entry point
int32 main()

{
	bool bPlayAgain = false;
	do 
	{
		
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // exit the application
}


void PrintIntro() 
{

	// introduction

	std::cout << "Welcome to Bulls and Cows Game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " isogram? \n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won	
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cow << std::endl;

		std::cout << std::endl;
	}

	PrintGameSummary();
	return;
}

// loop till user gives the valid guess
FText GetValidGuess() 
{
	FText Guess = " ";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		// get the guess
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess:";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} 
	while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? Y/N \n";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELLDONE! YOU WIN \n";
	}
	else
	{
		std::cout << "Better luck next time! \n";
	}
}