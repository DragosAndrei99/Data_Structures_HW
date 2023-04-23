#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

void readFromFile(std::vector<int> &v)
{

    std::fstream inputFile;
    int num;
    inputFile.open("C:/Users/Dragos/Desktop/test.txt", std::ios::in);

    while (inputFile >> num)
        {
          v.push_back(num);
        }
    inputFile.close();
}

void getNums(std::vector<int> v, int dist)
{
    // {key=elem, value=index}
    // salvam elementele din vector in map
    std::unordered_map<int, int> map;
    std::cout << "Exista numere egale in vector cu distanta intre ele mai mica sau egala cu dist la urmatorii indecsi: " << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        if(map.find(v[i]) == map.end()) // daca elem cu key = v[i] nu exista
            map[v[i]] = i;
        else if (i - map[v[i]] <= dist) // daca elem cu key = v[i] exista ( este duplicat ) si este <= dist
            std::cout << i << " " << map[v[i]] << std::endl;
    }
}

int main()
{
    std::vector<int> v;
    int dist;
    readFromFile(v);
    std::cout << "Elementele vectorului: ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Introduceti distanta: " << std::endl;
    std::cin >> dist;
    getNums(v, dist);
}