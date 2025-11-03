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

bool HashTable::insert(const std::string& key, const size_t& value) {}
bool HashTable::remove(const std::string& key) {}
bool HashTable::contains(const std::string& key) const {}

std::optional<size_t> HashTable::get(const std::string& key) const {}
size_t& HashTable::operator[](const std::string& key) {}
std::vector<std::string> HashTable::keys() const {}

double HashTable::alpha() const {}
size_t HashTable::capacity() const {}
size_t HashTable::size() const {}

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {}

//helpers
size_t HashTable::hash(const std::string& key) const {}
size_t HashTable::findIndex(const std::string& key) const {}

void HashTable::resizeIfNeeded() {}
void HashTable::rehash(size_t newCapacity) {}
void HashTable::initOffsets(size_t N) {}







