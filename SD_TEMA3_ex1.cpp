#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
class HashTable {
private:
    int elements = 0;
    std::vector<std::list<std::pair<std::string, std::string>>> table;
public:

    HashTable(int size);
    int getElements();
    int hashFunction(std::string key);
    void insert(std::pair<std::string, std::string> elem);
    std::pair<std::string, std::string>* search(std::string key);
    void remove(std::string key);
    void print();
    void rehash();

};

// constructor fn initializing table size 
HashTable::HashTable(int size)
    :table(size)
{
}

int HashTable::getElements()
{
    return this->elements;
}

// hashing based on first 2 chars of key
int HashTable::hashFunction(std::string key)
{
    char firstChar = key[0];
    char secondChar = key[1];
    char lastChar = key.back();
    int charToInt = int(firstChar) + int(secondChar) + int(lastChar);
    return charToInt % table.size();
}

void HashTable::insert(std::pair<std::string, std::string> elem)
{
    while ((float)(this->elements / this->table.size()) >= 1.00)
    {
        this->elements = 0;
        this->rehash();
    }
    int hashValue = hashFunction(elem.first);
    // list from table at given index
    auto& position = table[hashValue];
    auto iterator = begin(position);
    bool keyExists = false;
    for (; iterator != end(position); iterator++)
    {
        if (iterator->first == elem.first)
        {
            // replace value if key exists
            keyExists = true;
            iterator->second = elem.second;
            break;
        }
    }
    if (!keyExists) // if key is unique
    {
        // push into list at the end
        position.emplace_back(elem);
        elements++;
    }

    return;
}

std::pair<std::string, std::string>* HashTable::search(std::string key)
{
    std::pair<std::string, std::string>* result = nullptr;
    int hashValue = hashFunction(key);
    // list from table at given index
    auto& position = table[hashValue];
    auto iterator = begin(position);
    auto endIterator = end(position);
    for (; iterator != end(position); iterator++)
    {
        if (iterator->first == key)
        {
            // return pointer of value that is found at iterator
            result = &*iterator;
            break;
        }
    }
    return result;
}

void HashTable::remove(std::string key)
{
    int hashValue = hashFunction(key);
    // list from table at given index
    auto& position = table[hashValue];
    auto iterator = begin(position);
    bool keyFound = false;
    for (; iterator != end(position); iterator++)
    {
        if (iterator->first == key)
        {
            keyFound = true;
            iterator = position.erase(iterator);
            std::cout << "Pair removed" << std::endl;
            break;
        }
    }

    if (!keyFound)
    {
        std::cout << "Key was not found" << std::endl;
    }
    return;
}

void HashTable::print()
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].size() == 0) continue;

        auto iterator = table[i].begin();
        std::cout << "Index" << i;
        for (; iterator != table[i].end(); iterator++)
        {
            std::cout << "-->" << "(Key: " << iterator->first << " " << "Value: " << iterator->second << ") ";
        }
        std::cout << std::endl;
    }
}

void HashTable::rehash()
{
    std::vector<std::list<std::pair<std::string, std::string>>> temp = this->table;
    int oldSize = table.size();
    this->table = std::vector<std::list<std::pair<std::string, std::string>>>(oldSize * 2);
    for (int i = 0; i < oldSize; i++)
    {
        auto iterator = temp[i].begin();
        for (; iterator != temp[i].end(); iterator++)
        {
            this->insert(*iterator);
        }
    }

    return;
}

void readFromFile(HashTable& table)
{
    std::fstream inputFile;

    inputFile.open("C:/Users/Dragos/Desktop/test.txt", std::ios::in);

    if (inputFile)
    {
        std::string a, b;
        while (inputFile >> a >> b)
        {
            table.insert(std::make_pair(a, b));

        }
        inputFile.close();
    }
    else
    {
        std::cout << "Invalid file/path" << " ";
    }
}

void prompt()
{
    std::cout << "Menu:" << std::endl;
    std::cout << "1.Initialize hash table with elements read from file:" << std::endl;
    std::cout << "2.Insert:" << std::endl;
    std::cout << "3.Search:" << std::endl;
    std::cout << "4.Remove:" << std::endl;
    std::cout << "5.Print:" << std::endl;

    std::cout << "0. Exit" << std::endl;
}

int main()
{
    std::pair<std::string, std::string>* elem;
    int input;
    std::string key;
    std::string value;
    HashTable* table = new HashTable(5);
    while (prompt(), std::cin >> input && input != 0)
    {
        switch (input)
        {
        case 1:
            readFromFile(*table);
            std::cout << "Hash table was initialized" << std::endl;
            break;
        case 2:
            std::cout << "Enter key: " << std::endl;
            std::cin >> key;
            std::cout << "Enter value: " << std::endl;
            std::cin >> value;
            table->insert(std::make_pair(key, value));
            break;
        case 3:
            std::cout << "Enter key of element to be searched:" << std::endl;
            std::cin >> key;
            elem = table->search(key);
            std::cout << "(Key: " << elem->first << " " << "Value: " << elem->second << ") " << std::endl;           
            break;
        case 4:
            std::cout << "Enter key of element to be removed:" << std::endl;
            std::cin >> key;
            table->remove(key);
            break;
        case 5:
            table->print();
        default:
            break;
        }
    }

}
