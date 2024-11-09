#ifndef WORDLIST_H
#define WORDLIST_H

#include <iostream>
#include <string>
#include <vector>

class WordList
{
    
    public:
        WordList(std::vector<std::string> wordList) : words(wordList)
        {
        }

        void add(std::string word)
        {
            words.push_back(word);
        }

        std::string remove(std::string word)
        {
            for(int i = 0; i < words.size(); ++i)
            {
                if(words[i] == word)
                {
                    std::string w = words[i];
                    words.erase(words.begin() + i);
                    return w;
                }
            }
        }

        void printWords()
        {
            for(std::string w : words)
                std::cout << w << " ";

            std::cout << "\n";
        }
    private:
        std::vector<std::string> words;
};

#endif