#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

// input file under the below format / each row is a list or a separate competition
// Landon Gray Rosalie Fisher Alyssa Thompson Leo Collins Malik Patel Harper Davis Cedric Kim Kaitlyn Chens
// Jaxon Wright Rosalie Fisher Camila Rodriguez Graham Peters Penelope Lee Trevor Brown Gia Nguyen Marcus Mitchell Fiona Turner
// Xavier Rivera Sloane West Jaxon Wright Leo Collins Rylee Stewart Elijah Wright Rosalie Fisher



void readFromFile(std::unordered_map<std::string, int>& competitors)
{
    std::fstream inputFile;

    inputFile.open("C:/Users/Dragos/Desktop/test.txt", std::ios::in);

    if (inputFile)
    {
        std::string a, b;
        while (inputFile >> a >> b)
        {
            if(competitors.find(a+b) != competitors.end())
            {
                competitors[a+b]++;
            }
            competitors.insert(std::make_pair(a+b, 1));
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Invalid file/path" << " ";
    }
}

// get participants that compete in more than one competition
void getParticipants(std::vector<std::string>& activeInMoreThan1Competition, std::unordered_map<std::string, int>& competitors)
{
    std::unordered_map<std::string, int>::iterator itr1;
        for (itr1 = competitors.begin(); itr1 != competitors.end(); itr1++)
            if((*itr1).second > 1)
            {
                activeInMoreThan1Competition.push_back((*itr1).first);
            }
    
}

int main()
{
    std::vector<std::string> activeInMoreThan1Competition;
    std::unordered_map<std::string, int> competitors;

    readFromFile(competitors);
    getParticipants(activeInMoreThan1Competition, competitors);

    // print
    std::cout << std::endl;
    std::cout << "All the competitors:" << competitors.size() << std::endl << std::endl;
    std::unordered_map<std::string, int>::iterator itr1;
        for (itr1 = competitors.begin(); itr1 != competitors.end(); itr1++)
            std::cout << (*itr1).first << (*itr1).second << std::endl;

    std::cout << std::endl;
    std::cout << "Participants active in more than one competition:" << activeInMoreThan1Competition.size() << std::endl;
    for (int i = 0; i < activeInMoreThan1Competition.size(); i++)
    {
        std::cout << activeInMoreThan1Competition[i] << std::endl;
    }
}