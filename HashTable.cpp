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

void HashTableBucket::load(const std::string& key, const size_t& value) {}

bool HashTableBucket::isEmpty() const {}

bool HashTableBucket::isEmptySinceStart() const {}

bool HashTableBucket::isEmptyAfterRemove() const {}

void HashTableBucket::makeESS() {}
void HashTableBucket::makeEAR() {}

const std::string& HashTableBucket::getKey() const {}
const size_t& HashTableBucket::getValue() const {}
size_t& HashTableBucket::getValue() {}

BucketType HashTableBucket::getType() const {}

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {}

//HashTable



