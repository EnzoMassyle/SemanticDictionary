#ifndef SEMANTICDESCRIPTOR_H_INCLUDED
#define SEMANTICDESCRIPTOR_H_INCLUDED

//#include <vector> remove we are replacing it with the map container
#include <map>
#include <iostream>
#include <cmath>
#include <fstream>
#include <chrono>
using namespace std;

/*struct ContextWord
{
    string word;
    int count;
};*/

class SemanticDescriptor
{
    private:

        string targetWord;
        map<string, int> contextWords;

    public:
        SemanticDescriptor(string _targetWord) : targetWord(_targetWord) {}
        string getTargetWord() {return targetWord;}
        void processContextWord(string s);
        int operator*(const SemanticDescriptor& desc);
        friend ostream& operator<<(ostream& os, const SemanticDescriptor& desc);
        friend istream& operator>>(istream& is, SemanticDescriptor& desc);
};

#endif // SEMANTICDESCRIPTOR_H_INCLUDED