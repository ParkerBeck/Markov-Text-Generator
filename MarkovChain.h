#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include <map>
#include <vector>
#include <string>
struct Word;

struct NextWord
{
    std::string word;
    int appearanceCount;
};

struct Word
{
    //std::string word;
    std::vector<NextWord> nextWords;
};
//TODO: Stop on : ; . ? ! ( )""

class MarkovChain
{
public:
    MarkovChain();
    virtual ~MarkovChain();
    /*
    Function prototype:
        void addWord(string)
    Function description:
        This function adds a word(string) to the graph.
    Example:
        MarkovChain *mc = new MarkovChain();
        addWord("Turtle")
    Precondition:
        a empty map "wordList"
        generateFromFile already been called

    Postcondition:
        words added to the map "wordList"

    */
    void addWord(std::string word);
    /*
    Function prototype:
        void incNextWord(string, string)
    Function description:
        after the fist word has been added, find and add next word. if next word does
        not exist we create a new word as next word. and add them to the "wordList"

    Example:
        MarkovChain *mc = new MarkovChain();
        mc->incNextWord("title", "the");

    Precondition:
        generateFromFile already been called and
        the word is exist
    Postcondition:
        get and add next word,
    */
    void incNextWord(std::string word, std::string nextWord);
    /*
    Function prototype:
        Word* findWord(string)
    Function description:
        finds the word in the word list
    Example:
        MarkovChain *mc = new MarkovChain();
        mc->findWord("the")
    Precondition:
        generateFromFile already been called
    Postcondition:
        return the point to the string word you give
    */
    Word* findWord(std::string word);
    /*
    Function prototype:
        int findNextWord(string, vector)
    Function description:
        finds a word in another words "next word" list
    Example:
        MarkovChain *mc = new MarkovChain();
        int mc->findNextWord("the", nextWords)
    Precondition:
        generateFromFile already been called

    Postcondition:
        return next word structure associate with the next word vector
    */
    int findNextWord(std::string word, std::vector<NextWord> nextWords);
    /*
    Function prototype:
        int nextAppearanceSum(vector)
    Function description:
        finds the total amount of words after another word.
    Example:
        MarkovChain *mc = new MarkovChain();
        int mc->findNextWord("word", word)
    Precondition:
        generateFromFile already been called and a vector nextWords are given
    Postcondition:
        returns a integer
    */
    int nextAppearanceSum(std::vector<NextWord> nextWords);
    /*
    Function prototype:
        bool generateText(string)
    Function description:
        The function generates all of the next from the original text by randomly selecting another word to follow the current word.
    Example:
        MarkovChain *mc = new MarkovChain();
        mc->generateText(userInput)
    Precondition:
        the word (a string) giving by user is exist in file
        words already been get from the file

    Postcondition:
        take all the words and make a output file
    */
    bool generateText(std::string seedWord);
    /*
    Function prototype:
        void generateFromFile(string);
    Function description:
        by giving the file and file's name, get words from file.
    Example:
        MarkovChain *mc = new MarkovChain();
        mc-> generateFromFile("file.txt")
    Precondition:
        file exist with right users input of choosing files.
        file opens correctly

    Postcondition:
        finding and getting (string) words from the file
    */
    void generateFromFile(std::string fileName);
    /*
    Function prototype:
        void removeFromMap(string)
    Function description:
        remove a giving string from map "wordList"
    Example:
        MarkovChain *mc = new MarkovChain();
        mc->removeFromMap("the")
    Precondition: the word already exist in the map

    Postcondition: deleting a string from map

    */
    void removeFromMap(std::string word);
    /*
    Function prototype:
        double probabilityOfAppearance(int, vector)
    Function description:
        calculate the probability of appearance of a word
    Example:
        MarkovChain *mc = new MarkovChain();
        double mc-> probabilityOfAppearance(2, nextWords)
    Precondition: a existing nextWord

    Postcondition:
        return a double index

    */
    double probabilityOfAppearance(int index, std::vector<NextWord> nextWords);
    /*
    Function prototype:
        string mostUsedNextWord(vector)
    Function description:
        finding the most used next word
    Example:
        MarkovChain *mc = new MarkovChain();
        mc->mostUsedNextWord(nextWords)
    Precondition:a existing nextWord

    Postcondition: return a string

    */
    std::string mostUsedNextWord(std::vector<NextWord> nextwords);

    void printMostCommon(int number);

	void clearWordList();

	bool isEmpty();

protected:
private:
    std::map<std::string, Word> wordList;

};

#endif // MARKOVCHAIN_H
