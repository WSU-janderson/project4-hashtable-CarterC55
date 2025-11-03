/**
 * HashTable.cpp
 * Name: Carter Chinn
 * Implements hash table
 * Includesconstructors, load, isEmpty, insert, remove, contains, get, operator[] overload, operator << overload,
 * keys, alpha, capacity, size, hash, findIndex, resizeIfNeeded, rehash, initOffsets)
 */

#include "HashTable.h"

#include <functional>
#include <random>
#include <algorithm>

//HashTableBucket
HashTableBucket::HashTableBucket(): key(), value(0), state(BucketType::ESS) {}
HashTableBucket::HashTableBucket(const std::string& key, const size_t& value): key(key), value(value), state(BucketType::NORMAL) {}

void HashTableBucket::load(const std::string& key, const size_t& value)
{
    this->key = key;
    this->value = value;
    state = BucketType::NORMAL;
}

bool HashTableBucket::isEmpty() const
{
    return state != BucketType::NORMAL;
}

bool HashTableBucket::isEmptySinceStart() const
{
    return state == BucketType::ESS;
}

bool HashTableBucket::isEmptyAfterRemove() const
{
    return state == BucketType::EAR;
}

void HashTableBucket::makeESS()
{
    state = BucketType::ESS;
}
void HashTableBucket::makeEAR()
{
    state = BucketType::EAR;
}

const std::string& HashTableBucket::getKey() const
{
    return key;
}
const size_t& HashTableBucket::getValue() const
{
    return value;
}
size_t& HashTableBucket::getValue()
{
    return value;
}

BucketType HashTableBucket::getType() const
{
    return state;
}

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket)
{
    if (bucket.state == BucketType::NORMAL)
    {
        os << "<" << bucket.key << ", " << bucket.value << ">";
    }
    return os;
}

//HashTable
HashTable::HashTable(size_t initCapacity): tableData(initCapacity), offsets(), numItems(0) {initOffsets(initCapacity);}

bool HashTable::insert(const std::string& key, const size_t& value)
{
    //no dupes
    if (contains(key))
    {
        return false;
    }

    resizeIfNeeded();

    size_t N = capacity();
    if (N == 0)
    {
        rehash(1);
        N = capacity();
    }

    size_t home = hash(key) % N;
    size_t firstEAR = N;

    for (size_t step = 0; step < N; step++)
    {
        size_t index;
        if (step == 0)
        {
            index = home;
        }
        else
        {
            index = (home + offsets[step - 1]) % N;
        }

        HashTableBucket& bucket = tableData[index];
        BucketType type = bucket.getType();

        if (type == BucketType::NORMAL)
        {
            continue;
        }
        else if (type == BucketType::EAR)
        {
            if (firstEAR == N)
            {
                firstEAR = index;
            }
        }
        else //ESS
        {
            size_t target;
            if (firstEAR != N)
            {
                target = firstEAR;
            }
            else
            {
                target = index;
            }

            tableData[target].load(key,value);
            numItems++;
            return true;
        }
    }

    if (firstEAR != N)
    {
        tableData[firstEAR].load(key,value);
        numItems++;
        return true;
    }

    //full table
    rehash(N * 2);
    return insert(key, value);
}

bool HashTable::remove(const std::string& key)
{
    size_t index = findIndex(key);
    if (index == capacity())
    {
        return false;
    }
    tableData[index].makeEAR();
    if (numItems > 0)
    {
        numItems--;
    }
    return true;
}

bool HashTable::contains(const std::string& key) const
{
    return findIndex(key) != capacity();
}

std::optional<size_t> HashTable::get(const std::string& key) const
{
    size_t index = findIndex(key);
    if (index == capacity())
    {
        return std::nullopt;
    }
    return tableData[index].getValue();
}
size_t& HashTable::operator[](const std::string& key)
{
    size_t index = findIndex(key);
    return tableData[index].getValue();
}
std::vector<std::string> HashTable::keys() const
{
    std::vector<std::string> result;
    result.reserve(numItems);
    for (const auto& bucket : tableData)
    {
        if (bucket.getType() == BucketType::NORMAL)
        {
            result.push_back(bucket.getKey());
        }
    }
    return result;
}

double HashTable::alpha() const
{
    if (capacity() == 0) return 0.0;
    return static_cast<double>(numItems) / static_cast<double>(capacity());
}
size_t HashTable::capacity() const
{
    return tableData.size();
}
size_t HashTable::size() const
{
    return numItems;
}

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable)
{
    for (size_t i = 0; i < hashTable.capacity(); i++)
    {
        const HashTableBucket& bucket = hashTable.tableData[i];
        if (bucket.getType() == BucketType::NORMAL)
        {
            os << "Bucket " << i << ": <" << bucket.getKey() << ", " << bucket.getValue() << ">\n";
        }
    }
    return os;
}

//helpers
size_t HashTable::hash(const std::string& key) const
{
    std::hash<std::string> hasher;
    return hasher(key);
}

size_t HashTable::findIndex(const std::string& key) const
{
    size_t N = capacity();
    if (N == 0) return N; //empty table

    size_t home = hash(key) % N;
    //probe up to N positions
    for (size_t step = 0; step < N; step++)
    {
        size_t index;
        if (step == 0)
        {
            index = home; //first probe
        } else
        {
            index = (home+offsets[step-1]) % N; //subsequent probes
        }

        const HashTableBucket& bucket = tableData[index];
        BucketType type = bucket.getType();

        if (type == BucketType::NORMAL)
        {
            if (bucket.getKey() == key)
            {
                return index;
            }
        } else if (type == BucketType::ESS)
        {
            return N; //never hit used bucked
        }
    }
    return N; //not found in table
}

void HashTable::resizeIfNeeded()
{
    if (alpha() >= 0.5)
    {
        rehash(capacity() * 2);
    }
}
void HashTable::rehash(size_t newCapacity)
{
    if (newCapacity == 0) return;

    std::vector<HashTableBucket> oldData = std::move(tableData);
    tableData = std::vector<HashTableBucket>(newCapacity);
    numItems = 0;
    initOffsets(newCapacity);

    for (const auto& bucket : oldData)
    {
        if (bucket.getType() == BucketType::NORMAL)
        {
            insert(bucket.getKey(), bucket.getValue());
        }
    }
}
void HashTable::initOffsets(size_t N)
{
    offsets.clear();
    if (N <= 1) return;

    offsets.reserve(N-1);
    for (size_t i = 1; i < N; i++)
    {
        offsets.push_back(i);
    }

    //psuedo-random probing order
    std::mt19937 rng(0);
    std::shuffle(offsets.begin(), offsets.end(), rng);
}







