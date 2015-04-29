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
            This function adds a word to the graph.
        Example:
            addWord("Turtle")
        Precondition:

        Postcondition:

        */
        void addWord(std::string word);
        /*
        Function prototype:
            void incNextWord(string, string)
        Function description:

        Example:

        Precondition:

        Postcondition:

        */
        void incNextWord(std::string word, std::string nextWord);
        /*
        Function prototype:
            Word* findWord(string)
        Function description:
            finds the word in the word list
        Example:

        Precondition:

        Postcondition:

        */
        Word* findWord(std::string word);
        /*
        Function prototype:
            int findNextWord(string, vector)
        Function description:
            finds a word in another words "next word" list
        Example:

        Precondition:

        Postcondition:

        */
        int findNextWord(std::string word, std::vector<NextWord> nextWords);
        /*
        Function prototype:
            int nextAppearanceSum(vector)
        Function description:
            finds the total amount of words after another word.
        Example:

        Precondition:

        Postcondition:

        */
        int nextAppearanceSum(std::vector<NextWord> nextWords);
        /*
        Function prototype:
            bool generateText(string)
        Function description:
            The function generates all of the next from the original text by randomly selecting another word to follow the current word.
        Example:

        Precondition:

        Postcondition:

        */
        bool generateText(std::string seedWord);
        /*
        Function prototype:
            void generateFromFile(string);
        Function description:

        Example:

        Precondition:

        Postcondition:

        */
        void generateFromFile(std::string fileName);
        /*
        Function prototype:
            void removeFromMap(string)
        Function description:

        Example:

        Precondition:

        Postcondition:

        */
        void removeFromMap(std::string word);
        /*
        Function prototype:
            double probabilityOfAppearance(int, vector)
        Function description:

        Example:

        Precondition:

        Postcondition:

        */
        double probabilityOfAppearance(int index, std::vector<NextWord> nextWords);
        /*
        Function prototype:
            string mostUsedNextWord(vector)
        Function description:

        Example:

        Precondition:

        Postcondition:

        */
        std::string mostUsedNextWord(std::vector<NextWord> nextwords);
    protected:
    private:
        std::map<std::string, Word> wordList;

};

#endif // MARKOVCHAIN_H
