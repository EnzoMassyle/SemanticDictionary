#include "SemanticDictionary.h"

bool isStopWord(string s)
{

    if(stopWords.find(s) == stopWords.end()) return false; // s is not a stop word
    return true;
}
vector<vector<string>> getSentenceLists(string text)
{
    vector<vector<string>> sentenceLists;
    vector<string> sentenceList;
    string word = "";

    for(size_t i = 0; i < text.size(); i++)
    {
        ///if the ith char is alphabetical, concatenate it onto word
        char c = text[i];
        if(isalpha(c)) word += tolower(c); 

        else //when we get to this point, we will have acquired a word since the character was not part of the alphabet
        {
            if(word.size() > 0)
            {
                if(!isStopWord(word)) sentenceList.push_back(word); // add word to the sentence only if it is not a stop word
                word = "";
            }
            if((c == '?' || c == '.' || c == '!') && sentenceList.size() > 0)// at this point we will have reached the end of the sentence
            { 
                sentenceLists.push_back(sentenceList); // push the sentence back into the 2d vector sentenceLists
                sentenceList.clear();
            }
        }
    }
    // checking for leftover incase the user did not enter a space or punctuation
    if(word.size() > 0)
    {
        sentenceList.push_back(word);
        word = "";
    }

    if(sentenceList.size() > 0)
    {
        sentenceLists.push_back(sentenceList);
    }

    return sentenceLists;
}

ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists)
{
    os << "Sentence Lists:" << endl;

    os << "[" << endl;

    // going to use a nested for loop to iterate through each sentence (row) and go through each word (column in the row)
    for(size_t i = 0; i < sentenceLists.size(); i++)
    {
        os << "[ ";
        for(size_t j = 0; j < sentenceLists.at(i).size(); j++) 
        {
            os << sentenceLists[i][j] << ' ';
        }
        os << ']' << endl;
    }


    return os;
}

ostream& operator<<(ostream& os, const SemanticDictionary& d)
{
    os << "Semantic Descriptors" << endl << "{" << endl;

    for(auto iter = d.semanticDescriptors.begin(); iter != d.semanticDescriptors.end(); iter++)
    {
        os << iter->second << endl; // this will go to the outer output stream fucntion we wrote
    }

    os << "}" << endl;
    return os;
}

istream& operator>>(istream& is, SemanticDictionary& d)
{
    // Clear the vector of SemanticDescriptors to ensure there is no old data in it
    d.semanticDescriptors.clear();

    //Construct a semantic descriptor with an empty string for its targetWord parameter
    SemanticDescriptor descriptor{""};


    // extract one char at a time until you reach '{' this will read past the text at the top of the file ans past the first '{'

    char c;

    while (is >> c)
    {
        if(c == '{') break;
    }

    if(is.fail()) return is;
    // Use the semantiDescroptor extraction operator >> as defined in our other object file, insid the loop, push_back the SemantiDescriptor into d
    is >> descriptor;
    while(!is.fail())
    {
        d.semanticDescriptors.insert({descriptor.getTargetWord(), descriptor});
        //d.semanticDescriptors.push_back(descriptor);
        is >> descriptor;
    }

    is.clear();
    is >> c;
    if(c != '}') is.clear(ios::failbit);
    return is;


}



void SemanticDictionary::processTargetWord(string targetWord, vector<string> sentenceList)
{

    auto it = semanticDescriptors.find(targetWord);
    if(it == semanticDescriptors.end())
    {
        it = (semanticDescriptors.insert({targetWord, SemanticDescriptor{targetWord}})).first; //new target word
        
    }

    for(size_t i = 0; i < sentenceList.size(); i++)
    {
        if(sentenceList.at(i) != targetWord) 
        {
            it->second.processContextWord(sentenceList.at(i));
        }
    }

}

double SemanticDictionary::getSimilarity(string targetWord1, string targetWord2) {


    auto iter1 = semanticDescriptors.find(targetWord1);
    auto iter2 = semanticDescriptors.find(targetWord2);
    
    if(iter1 == semanticDescriptors.end() || iter2 == semanticDescriptors.end()) throw runtime_error("Target word(s) unkonwn");


    SemanticDescriptor u = iter1->second;
    SemanticDescriptor v = iter2->second;

    double cosineSimilarity = ((u * v) * 1.0) / (sqrt(u * u)*sqrt(v * v));

    return cosineSimilarity;
    
}

string SemanticDictionary::mostSimilarWord(string word, vector<string> choices) {

    double highestSimilarity = getSimilarity(word, choices.at(0));
    double similarity;
    string bestWord= choices.at(0);
    for(size_t i = 1; i < choices.size(); i++) 
    {
        similarity = getSimilarity(word, choices.at(i));
        if(similarity > highestSimilarity) 
        {
            highestSimilarity = similarity;
            bestWord = choices.at(i);
        }
    }

    return bestWord;

}

