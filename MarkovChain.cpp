#include "MarkovChain.h"
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;

MarkovChain::MarkovChain()
{
    //ctor
}

MarkovChain::~MarkovChain()
{
    //dtor
}

void MarkovChain::addWord(std::string wordString)
{
    wordList[wordString] = Word();
}

void MarkovChain::incNextWord(std::string wordString, std::string nextWordString)
{
    Word* word = findWord(wordString);
    if(word != NULL)
    {
        int index = findNextWord(nextWordString, word->nextWords);
        if(index == -1)
        {
            NextWord nW;
            nW.word = nextWordString;
            nW.appearanceCount = 1;
            word->nextWords.push_back(nW);
        }
        else
        {
            word->nextWords[index].appearanceCount++;
        }
    }
    else
    {
        std::cout << "Error: Word does not exist" << std::endl;
    }
}

Word* MarkovChain::findWord(std::string word)
{
    //If the word exists in wordList return the pointer to it
    if(wordList.count(word))
    {
        return &wordList[word];
    }
    else
    {
        return NULL;
    }
}

int MarkovChain::findNextWord(std::string nextWord, std::vector<NextWord> nextWords)
{
    for(int i = 0; i < nextWords.size(); i++)
    {
        if(nextWords[i].word == nextWord)
        {
            return i;
        }
    }
    return -1;
}

int MarkovChain::nextAppearanceSum(std::vector<NextWord> nextWords)
{
    int sum = 0;
    for(int i = 0; i < nextWords.size(); i++)
    {
        sum += nextWords[i].appearanceCount;
    }
    return sum;
}

void MarkovChain::generateFromFile(std::string fileName)
{
    std::ifstream file;
    file.open(fileName.c_str());
    std::string word;
    std::queue<std::string> stringQueue;
    while(file >> word)
    {
        char wordStart = word[0];
        char wordEnding = word[word.size() -1];
        if(wordStart == '"' || wordStart == '(')
        {
            if(word[word.size() -1] == '"' || word[word.size() -1] == '(')
            {
                word.erase(0,1);
                word.erase(word.size()-1);
                if(word.size() > 0)
                {
                    stringQueue.push(word);
                }
                stringQueue.push(".");
            }
            else
            {
                stringQueue.push(".");
                word.erase(0,1);
                stringQueue.push(word);
            }

        }
        else if(wordEnding == '.' || wordEnding == '"' || wordEnding == '?' || wordEnding == ')' ||
                wordEnding == '!' || wordEnding == ':' || wordEnding == ';')
        {
            if(word[word.size()-2] == '.' || word[word.size()-2] == ',' ||
                    word[word.size()-2] == '!' || word[word.size()-2] == '?')
            {
                word.erase(word.size()-1);
            }
            std::string wordEndingString;
            /*
            std::stringstream ss;
            ss <<wordEnding;
            ss >> wordEndingString;
            */
            //Replace this with commmented out section to add any stops
            wordEndingString = ".";
            word.erase(word.size()-1);
            stringQueue.push(word);
            stringQueue.push(wordEndingString);
        }
        else
        {
            stringQueue.push(word);
        }

    }
    while(!stringQueue.empty())
    {
        word = stringQueue.front();
        stringQueue.pop();
        if(!stringQueue.empty())
        {
            std::string nextWord = stringQueue.front();
            Word* wordPtr = findWord(word);
            if(wordPtr == NULL)
            {
                addWord(word);
            }
            incNextWord(word, nextWord);
        }
    }
}
