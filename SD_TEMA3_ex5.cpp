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

auto print_key_value = [](const auto& key, const auto& value)
{
    for (int i = 0; i < value.size(); i++)
        std::cout << "Key:[" << key << "] Value:[" << "start=" << value[i].first << "stop=" << value[i].second << "]\n";
};

void getPairsOfIndexes(std::vector<int> v, int k)
{
    // construim unordered_map-ul în care memoram sumele partiale ale elem din vector
    // input vector: 1 2 3 4 5 6 7
    // unorderd_map pairs (key=sum , value=(index_start, index_stop)...
    std::unordered_map<int, std::vector<std::pair<int, int>>> sumMap;
    for (int i = 0; i < v.size(); i++) {
        int sum = 0;
        for (int j = i; j < v.size(); j++)
        {
            sum += v[j];
            sumMap[sum].push_back(std::make_pair(i, j));
        }
    }
    //printare unorded map pt verificare
    for( const auto& [key, value] : sumMap )
        print_key_value(key, value);

    std::cout << "Perechile posibile de indici sunt: " << std::endl;
    for( const auto& [key, value] : sumMap )
        if(k == key )
            for (int i = 0; i < value.size(); i++)
            {
                std::cout << "Start=" <<  value[i].first << "Stop=" << value[i].second << std::endl;
            }
}



int main()
{
    std::vector<int> v;
    readFromFile(v);
    std::cout << "Elementele vectorului: ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    int k;
    do
    {
        std::cin >> k;
        getPairsOfIndexes(v, k);
    } while (k != 0);
}