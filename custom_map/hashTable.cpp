#include "hashTable.h"
#include <string>
#include <cstdint>
#include <cstring>

hashTable::hashTable()
{
    this->tableCapacity = 8192;
    this->loadFactor = 0;
    this->contaminationFactor = 0;
    this->table = new element[tableCapacity];
}

hashTable::~hashTable()
{
    delete[] table;
}

constexpr uint32_t c1 = 0xcc9e2d51;
constexpr uint32_t c2 = 0x1b873593;
constexpr uint32_t r1 = 15;
constexpr uint32_t r2 = 13;
constexpr uint32_t m = 5;
constexpr uint32_t n = 0xe6546b64;

uint32_t rotl(uint32_t x, int r)
{
    return (x << r) | (x >> (32 - r));
}

uint32_t fmix(uint32_t h)
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

long murmurHash3(const void* key, size_t len, uint32_t seed = 0)
{
    const uint8_t* data = static_cast<const uint8_t*>(key);
    const int nblocks = len / 4;

    uint32_t h1 = seed;

    for (int i = 0; i < nblocks; ++i) {
        uint32_t k1;
        std::memcpy(&k1, data + i * 4, sizeof(uint32_t));

        k1 *= c1;
        k1 = rotl(k1, r1);
        k1 *= c2;

        h1 ^= k1;
        h1 = rotl(h1, r2);
        h1 = h1 * m + n;
    }

    const uint8_t* tail = data + nblocks * 4;
    uint32_t k1 = 0;

    switch (len & 3)
    {
    case 1:
    {
        k1 ^= tail[0];
        k1 *= c1;
        k1 = rotl(k1, r1);
        k1 *= c2;
        h1 ^= k1;
    }
    case 2:
    {
        k1 ^= tail[1] << 8;
    }
    case 3:
    {
        k1 ^= tail[2] << 16;
    }
    }

    h1 ^= len;

    return fmix(h1);
}

uint32_t murmurHash3(const std::string& str, uint32_t seed = 0)
{
    return murmurHash3(str.c_str(), str.length(), seed);
}

int hashTable::primaryHash(std::string key, unsigned int testRate)
{
    return (murmurHash3(key) + testRate) % tableCapacity;
}

void hashTable::rehashing()
{
    if (this->contaminationFactor >= 0.30 || this->loadFactor >= 0.75)
    {
        //a new vector with the size as the old one is created

        element* temp = new element[this->tableCapacity];

        //a pointer that changes the addresses between the initial vector and the temporary one is made

        element* swap = this->table;
        this->table = temp;
        temp = swap;

        //the memory of the initial vector is reallocated

        delete[] this->table;

        if (this->loadFactor >= 0.75)
            this->tableCapacity *= 2;

        int final = this->loadFactor >= 0.75 ? this->tableCapacity / 2 : tableCapacity;

        this->loadFactor = 0;
        this->contaminationFactor = 0;

        this->table = new element[this->tableCapacity];

        for (int index = 0; index < final; index++)
        {
            if (temp[index].getStatus() == 'o')
                insertElem(temp[index]);
        }
    }
}

void hashTable::insertElem(element Element)
{
    unsigned int testRate = 0;
    int toBeInserted = primaryHash(Element.getKey(), testRate);

    while (table[toBeInserted].getStatus() == 'o')
    {
        testRate++;
        toBeInserted = primaryHash(Element.getKey(), testRate);
    }

    table[toBeInserted].setKey(Element.getKey());
    table[toBeInserted].setValue(Element.getValue());
    table[toBeInserted].setStatus('o');
    table[toBeInserted].setLinkToIt(&table[toBeInserted]);

    this->loadFactor += 1.0 / this->tableCapacity;

    rehashing();
}

int hashTable::findElem(candidate Candidate)
{
    int testRate = 0;

    while (table[primaryHash(Candidate.getCNP(), testRate)].getValue() != Candidate && testRate < tableCapacity)
    {
        testRate++;
    }

    if (testRate >= tableCapacity)
        return -1;
    else
        return primaryHash(Candidate.getCNP(), testRate);
}

void hashTable::eraseElem(candidate Candidate)
{
    int toBeDeleted = findElem(Candidate);

    if (toBeDeleted != -1)
    {
        table[toBeDeleted].setKey("");
        table[toBeDeleted].setValue(candidate());
        table[toBeDeleted].setStatus('d');
        table[toBeDeleted].setLinkToNode(nullptr);

        this->loadFactor -= 1.0 / this->tableCapacity;
        this->contaminationFactor += 1.0 / tableCapacity;
        std::cout << "Elementul a fost sters cu succes!" << std::endl << std::endl;
    }
    else
    {
        std::cout << "Elementul nu a putut fi sters!" << std::endl << std::endl;
    }

    rehashing();
}

void hashTable::clear()
{
    delete[] table;
    table = new element[tableCapacity];
    loadFactor = 0;
    contaminationFactor = 0;
}

void hashTable::write()
{
    for (int index = 0; index < this->tableCapacity; index++)
    {
        std::cout << this->table[index].getKey() << " " << this->table[index].getValue() << " " << this->table[index].getStatus() << std::endl;
    }
    std::cout << this->tableCapacity << " " << this->loadFactor << " " << this->contaminationFactor << std::endl << std::endl;
}

element* hashTable::getElementAdress(int index)
{
    return &table[index];
}

node* hashTable::getLinkToNode(int index)
{
    return table[index].getLinkToNode();
}
