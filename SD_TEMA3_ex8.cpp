#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

// input file cu formatul de mai jos/ fiecare rand reprezinta produsele unui magazin, fiecare rand reprezinta nr de magazin
// Chocolate Shampoo Toothpaste Bread Cereal Coffee Chips Avocado Socks (spatiu dupa fiecare rand apoi enter pt new line)
// Socks Tissues Pizza Towels Apples Detergent Juice Avocado Toothpaste Coffee
// Chocolate Shampoo Toothpaste Bread Cereal Coffee Chips Avocado Socks Detergent
// Chocolate Shampoo Toothpaste Bread Cereal Coffee Chips Avocado Socks Juice Pizza
//



void readFromFile(std::vector<std::vector<std::string>>& stores)
{
    std::fstream inputFile;

    inputFile.open("C:/Users/Dragos/Desktop/test.txt", std::ios::in);
    if (inputFile)
    {
        char ch;
        std::string str;
        std::string a;
        std::vector<std::string> temp;
        while(inputFile >> std::noskipws >> ch)
        {
            if(ch != '\n')
            {
                str += ch;
                if(std::isspace(ch))
                {
                    temp.push_back(str);
                    str = "";
                }
            }
            if(ch == '\n') // detects the end of the line
            {
                stores.push_back(temp);
                temp.clear();
            }

        }
        inputFile.close();
    }
    else
    {
        std::cout << "Invalid file/path" << " ";
    }
}

// needs refactoring - some fields or values might be redundant
// creez unordered map de obiecte cu key = nume produs si value de pair ( magazine in care apare , aparitii totale)
void createMap(std::vector<std::vector<std::string>> stores, std::unordered_map<std::string, std::pair<std::string, int>>& allProducts)
{
    for (int i = 0; i < stores.size(); i++)
        {
            std::cout << "Magazin nr:" << i << std::endl;
            for (int j = 0; j < stores[i].size(); j++)
            {
                std::cout << stores[i][j] << " ";
                if(allProducts.find(stores[i][j]) != allProducts.end())
                {
                    allProducts[stores[i][j]].first += " and ";
                    allProducts[stores[i][j]].first += std::to_string(i);
                    allProducts[stores[i][j]].second++;
                } else
                {
                    allProducts[stores[i][j]] = std::make_pair(std::to_string(i), 1);
                }
            }
            std::cout << std::endl;
        }
}


std::vector<int> createAppearancesVector(std::vector<std::vector<std::string>> stores, std::unordered_map<std::string, std::pair<std::string, int>> allProducts)
{
    // iteram prin vector si calculam  aparitiile totale pt fiecare produs
    // intr-un nou vector salvam aparitiile totale in aceeasi ordine astfel indexul noului vectorul este nr de magazin
    // => suma cea mai mica este cea returnata pt ca are cele mai multe produse exclusive
    std::vector<int> appearances;

    for (int i = 0; i < stores.size(); i++)
    {
        int tempSum = 0;
        for (int j = 0; j < stores[i].size(); j++)
        {
            tempSum += allProducts[stores[i][j]].second;
        }
        // index este nr magazin
        appearances.push_back(tempSum);
    }

    return appearances;
}

int calcExclusivistShop(std::vector<int> appearances)
{
    int temp = INT_MAX;
    int result;
    for (int i = 0; i < appearances.size(); i++)
    {
        if(temp > appearances[i])
        {
            temp = appearances[i];
            result = i;
        }
    }

    return result;
}


int main()
{
    std::vector<std::vector<std::string>> stores;
    // map cu toate produsele fara duplicate
    // key=produs / elem=pair(nr magazin, aparitie)
    std::unordered_map<std::string, std::pair<std::string, int>> allProducts;
    readFromFile(stores);
    createMap(stores, allProducts);
    std::vector<int> appearances = createAppearancesVector(stores, allProducts);
    int result = calcExclusivistShop(appearances);

    
    std::cout << "Magazinul cu cele mai multe exclusiviste produse este magazinul nr: " << result;
    return 0;
}