#include<string>
#include<set>
#include<iostream>
#include<algorithm>

void RemoveVowels(std::string &str)
{
    std::set<char> setVowels;
    std::string strVowels = "aeiouyAEIOUY";

    for (char elem : strVowels){
        setVowels.insert(elem);
    }

    for (char letter : setVowels){
        str.erase(remove(str.begin(), str.end(), letter), str.end());
    }
}
