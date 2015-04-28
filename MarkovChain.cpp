#include "MarkovChain.h"
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>
#include <algorithm>
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


double MarkovChain::probabilityOfAppearance(int index, std::vector<NextWord> nextWords)
{
    return (double)nextWords[index].appearanceCount/nextAppearanceSum(nextWords);
}

void MarkovChain::generateFromFile(std::string fileName)
{
    std::ifstream file;
    file.open(fileName.c_str());
    std::string word;
    std::queue<std::string> stringQueue;
    while(file >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
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
                wordEnding == '!' || wordEnding == ':' || wordEnding == ';' || wordEnding == ',')
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
    Word* periodPtr = findWord(".");
    if(periodPtr != NULL)
    {
        int index = findNextWord(".", periodPtr->nextWords);
        if(index != -1)
        {
            periodPtr->nextWords.erase(periodPtr->nextWords.begin()+ index);
        }
    }
}

bool MarkovChain::generateText(std::string seedWord)
{
    std::string currentWordString = seedWord;
    Word* currentWord = findWord(seedWord);
    if(currentWord == NULL)
    {
        return false;
    }
    int maxSentences = nextAppearanceSum(findWord(".")->nextWords)+1;
    int sentences = 0;
    std::ofstream out(currentWordString);
    bool sentenceStart = false;
    bool startOfLine = true;
    srand (time(NULL));
    currentWordString[0] = toupper(currentWordString[0]);
    while(sentences<maxSentences)
    {
        double randNum = (double) rand() / RAND_MAX;
        int tot = nextAppearanceSum(currentWord->nextWords);
        for(int i = 0; i < currentWord->nextWords.size(); i++)
        {
            if(randNum < probabilityOfAppearance(i, currentWord->nextWords))
            {
                //std::string currentWordString = currentWordString;
                if(currentWordString != ".")
                {
                    if(startOfLine == true)
                    {
                        currentWordString[0] = toupper(currentWordString[0]);
                        cout<<currentWordString;
                        out<<currentWordString;
                        startOfLine = false;
                        sentenceStart = false;
                    }/*
                    else if(sentenceStart == true)
                    {
                        temp[0] = toupper(temp[0]);
                        cout<<" "<<temp;
                        out<<" "<<temp;
                        sentenceStart = false;
                    }*/
                    else
                    {
                        cout<<" "<<currentWordString;
                        out<<" "<<currentWordString;
                    }
                }
                else
                {
                    cout<<currentWordString<<endl;
                    out<<currentWordString<<endl;
                    sentences++;
                    sentenceStart = true;
                    startOfLine = true;
                }
                currentWordString = currentWord->nextWords[i].word;
                break;
            }
            randNum -= probabilityOfAppearance(i, currentWord->nextWords);
        }
        currentWord = findWord(currentWordString);
    }
    cout<<endl;
    out.close();
    return true;
}

void MarkovChain::removeFromMap(std::string word)
{
    wordList.erase(word);
}

string MarkovChain::mostUsedNextWord(std::vector<NextWord> nextWords)
{
    int currentMax = 0;
    int totalMax = 0;
    std::string usedWord;
    for(int i = 0; i < nextWords.size(); i++)
    {
        currentMax = nextWords[i].appearanceCount;
        if(currentMax > totalMax)
        {
            totalMax = currentMax;
            usedWord = nextWords[i].word;
        }
    }
    return usedWord;
}


