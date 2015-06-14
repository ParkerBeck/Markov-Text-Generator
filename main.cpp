#include <iostream>
#include <string>
#include "MarkovChain.h"
using namespace std;

enum MenuStage { MAIN, FILE_SELECTION, FILE_USERINPUT, SEED_INPUT, GENERATED, PROGRAM_TERMINATED};

void printMenu(MenuStage currentStage)
{
	if (currentStage == MAIN)
	{
		std::cout << "Would you like to generate from a predetermined file or use your own?" << std::endl;
		std::cout << "1. Select from a predetermined list of texts" << std::endl;
		std::cout << "2. Use your own input" << std::endl;
		std::cout << "3. Quit" << std::endl;
	}
	else if (currentStage == FILE_SELECTION)
	{
		std::cout << "Great! Choose one of the following texts." << std::endl;
		std::cout << "1. Harry Potter" << std::endl;
		std::cout << "2. Wikipedia Article: Banana" << std::endl;
		std::cout << "3. The Lorax" << std::endl;
		std::cout << "4. What Teachers Make" << std::endl;
		std::cout << "5. The Great Dictator Speech" << std::endl;
		std::cout << "6. Back to Main Menu" << std::endl;
	}
	else if (currentStage == FILE_USERINPUT)
	{
		std::cout << "Enter the name of the file, leave it blank to go back to main menu" << std::endl;
	}
	else if (currentStage == SEED_INPUT)
	{
		std::cout << "What word would you like to generate the text from? Enter ? for a list of the most common words." << std::endl;
	}
	else if (currentStage == GENERATED)
	{
		std::cout << "The file has been generated, find it under the Output folder" << std::endl;
		std::cout << "1. Back to Main Menu" << std::endl;
		std::cout << "2. Quit" << std::endl;
	}
}

MenuStage processInput(MarkovChain *mc, MenuStage currentStage, std::string userInput)
{
	if (currentStage == MAIN)
	{
		if (userInput == "1")
		{
			return FILE_SELECTION;
		}
		else if (userInput == "2")
		{
			return FILE_USERINPUT;
		}
		else if (userInput == "3")
		{
			return PROGRAM_TERMINATED;
		}
	}
	else if (currentStage == FILE_SELECTION)
	{
		if (userInput == "1")
		{
			mc->generateFromFile("testFile1.txt");
		}
		else if (userInput == "2")
		{
			mc->generateFromFile("testFile2.txt");
		}
		else if (userInput == "3")
		{
			mc->generateFromFile("testFile3.txt");
		}
		else if (userInput == "4")
		{
			mc->generateFromFile("testFile4.txt");
		}
		else if (userInput == "5")
		{
			mc->generateFromFile("testFile5.txt");
		}
		else if (userInput == "6")
		{
			return MAIN;
		}
		if (!mc->isEmpty())
		{
			return SEED_INPUT;
		}
	}
	else if (currentStage == FILE_USERINPUT)
	{
		if (userInput == "")
		{
			return MAIN;
		}
		mc->generateFromFile(userInput);
		if (!mc->isEmpty())
		{
			return SEED_INPUT;
		}
	}
	else if (currentStage == SEED_INPUT)
	{
		if (userInput == "?")
		{
			mc->printMostCommon(10);
			return SEED_INPUT;
		}
		else
		{
			if (mc->generateText(userInput))
			{
				return GENERATED;
			}
			else
			{
				std::cout << "It looks like that word doesn't appear in the file, please try a different one!" << std::endl;
				return SEED_INPUT;
			}
		}
	}
	else if (currentStage == GENERATED)
	{
		if (userInput == "1")
		{
			mc->clearWordList();
			return MAIN;
		}
		if (userInput == "2")
		{
			return PROGRAM_TERMINATED;
		}
	}

	std::cout << "Invalid input please try again!" << std::endl << std::endl;
	return currentStage;

}

int main()
{
	MenuStage currentStage = MAIN;

	MarkovChain *mc = new MarkovChain;
    std::string userInput;

	while(currentStage != PROGRAM_TERMINATED)
    {
		printMenu(currentStage);

		getline(cin, userInput);

		currentStage = processInput(mc, currentStage, userInput);

    }
    return 0;
}
