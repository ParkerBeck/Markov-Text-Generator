#include "MarkovChain.h"
#include <map>
#include <vector>
#include <iostream>
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

void MarkovChain::addNextWord(std::string wordString, std::string nextWordString)
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
