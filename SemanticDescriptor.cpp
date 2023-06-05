#include "SemanticDescriptor.h"


void SemanticDescriptor::processContextWord(string s) {



    map<string, int>::iterator iter = contextWords.find(s); //here we are finding where the context word is located in the map
    if(iter == contextWords.end()) // if the context word does not exist in the map, we will insert it
    {   
        contextWords.insert(pair<string, int>(s, 1)); // insert the new pair into the map
    }
    else
    {
        iter->second++; //increment the value associated with the key s
    }

/* for(size_t i = 0; i < contextWords.size(); i++)
    {
        if(contextWords.at(i).word == s) 
        {
            contextWords.at(i).count++; // if s is found , then increment its count
            return;
        }
    }
    // if s is not found, then push_back a new Context word object for s with count being 1; //a new word was found   
    contextWords.push_back(ContextWord{s, 1}); // add the new word and its count to the Conext words*/
}

int SemanticDescriptor::operator*(const SemanticDescriptor& desc) {

    int sum = 0;

    for(auto iter = this->contextWords.begin(); iter != this->contextWords.end(); iter++)
    {
        auto currWord = desc.contextWords.find(iter->first); //this is the current word of the semantic descriptor
        if(currWord != desc.contextWords.end()) //this means the word was found
        {
            sum += (currWord->second * iter->second);
        }

    }


    return sum;

}

ostream& operator<<(ostream& os, const SemanticDescriptor& desc)
{
    /*for(size_t i = 0; i < desc.contextWords.size(); i++) WE ARE GOING TO USE ITERATORS INSTEAD
    {
        os << desc.contextWords.at(i).word << ' ' << desc.contextWords.at(i).count << ' '; //added the new line
    }*/

    os << desc.targetWord << " {";

    for(auto iter = desc.contextWords.begin(); iter != desc.contextWords.end(); iter++) //iterate through the map
    {
        os << iter->first << ' ' << iter->second << ' ';
    }

    os << "}" << endl;

    return os;

}

istream& operator>>(istream& is, SemanticDescriptor& desc)
{
    char semanticCharacter;
    //we need to clear the contents of desc to ensure there is no old data in it
    desc.targetWord = "";
    desc.contextWords.clear();

    // extract the target word
    string targetWord;
    is >> targetWord;
    desc.targetWord = targetWord;

    is >> semanticCharacter;

    if(semanticCharacter != '{')
    {
        is.unget();
        is.clear(ios::failbit);
        return is;
    }

    while(!is.fail())
    {
        is >> semanticCharacter;
        if(semanticCharacter == '}') return is;

            is.unget();

            string word;
            int count;
            is >> word >> count;
            desc.contextWords.insert({word, count}); // insert the pair into the semantic descriptor
          /*  ContextWord temp;
            is >> temp.word;
            is >> temp.count;
            desc.contextWords.push_back(temp);*/

    }

    return is;


}