#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
#include <stdexcept>
#include <algorithm>


std::string convertToLowerCase(std::string s)
{
    for(char& c : s)
    {
        c = std::tolower(c);
    }

    return s;
}

bool comp(std::pair<std::string, int>& a, std::pair<std::string, int>& b) {
    return a.second < b.second;
}


int main()
{
    //the multimap is for storing the word and the number of times the word has appeared
    std::map<std::string, int> words;
    std::string filename;
    std::string s;
    char delim[] = " \n,.\r\t[]\\/!@#$%^&*();-—";
    char *token;

    // Open file
    std::cout << "Please Enter the file name: ";
    std::cin >> filename;

    std::ifstream ist{filename};
    if(!ist)
    {
        throw std::runtime_error{"can't open this file"};
    }


    // Get each line and tokenize
    char temp[1000];
    while(std::getline(ist, s))
    {
        token = strtok(s.data(), delim);
        while(token != nullptr)
        {
            strcpy(temp, token);
            std::string word(temp);
            word = convertToLowerCase(word);

            auto it = words.find(word);
            if(it != words.end())
            {
                it->second = (it->second) + 1;
            }
            else
            {
                words.insert({word, 1});
            }
                        
            token = strtok(nullptr, delim);
        }
    }

    
    std::vector<std::pair<std::string, int>> v(words.begin(), words.end());

    std::sort(v.begin(), v.end(), comp);

    //get the first 10 elements in the sorted words
    int count = 0;
    for(auto it = v.rbegin(); it != v.rend() && count < 10; ++it)
    {
        std::cout << "'"<< (*it).first << "'" << " has appeared "<< (*it).second << " times" <<std::endl;
        count++;
    }


}