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
        void addWord(std::string word);
        void addNextWord(std::string word, std::string nextWord);
        Word* findWord(std::string word);
        int findNextWord(std::string word, std::vector<NextWord> nextWords);
        int nextAppearanceSum(std::vector<NextWord> nextWords);
        void generateText(std::string seedWord);

    protected:
    private:
        std::map<std::string, Word> wordList;

};

#endif // MARKOVCHAIN_H
