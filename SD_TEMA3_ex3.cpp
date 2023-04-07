#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>

void readFromFile(std::string& a, std::string& b)
{

    std::fstream inputFile;

    inputFile.open("C:/Users/Dragos/Desktop/test.txt", std::ios::in);

    if (inputFile)
    {
        inputFile >> a >> b;
        inputFile.close();
    }
    else
    {
        std::cout << "Invalid file/path" << " ";
    }
}

void print(std::unordered_set<char> string1)
{
    std::unordered_set<char>::iterator itr1;
    for (itr1 = string1.begin(); itr1 != string1.end(); itr1++)
        std::cout << (*itr1) << std::endl;
}


// known issue: if string1 = rolzl and string2 = lorzz , this will return true because keys are unique in unordered sets from stl
bool checkPermutation(std::string a, std::string b)
{
    std::unordered_set<char> set1, set2;
    bool isPermutation = true;

    for (char& x : a)
    {
        set1.insert(x);
    }

    for (char& y : b)
    {
        set2.insert(y);
    }

    if (set1.size() != set2.size())
    {
        isPermutation = false;
    }

    for (char& z: b)
    {
        auto found = set1.find(z);
        if (found == set1.end())
        {
            isPermutation = false;
        }
    }
    print(set1);
    return isPermutation;
}

int main()
{
    std::string a, b;
    readFromFile(a, b);
    bool isPermutation = checkPermutation(a, b);
    std::cout << "String 1: " << a << " " << "String 2: " << b << std::endl;
    std::cout << "Is permutation= " << isPermutation << std::endl;
}