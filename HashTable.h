/**
 * HashTable.h
 */
#pragma once

#include <string>
#include <vector>
#include <optional>
#include <ostream>
#include <cstddef>

enum class BucketType { NORMAL, ESS, EAR };

class HashTableBucket
{
    public:
    //constructors
    HashTableBucket();
    HashTableBucket(const std::string& key, const size_t& value);

    //load bucket with key/value and mark occupied
    void load(const std::string& key, const size_t& value);

    //all true/false checkers
    bool isEmpty() const;
    bool isEmptySinceStart() const;
    bool isEmptyAfterRemove() const;

    //bucket type setters
    void makeESS();
    void makeEAR();

    //gets read only refs to key/value
    const std::string& getKey() const;
    const size_t& getValue() const;

    //get modifiable ref for value
    size_t& getValue();

    BucketType getType() const;

    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);

    private:
    std::string key{};
    size_t value{};
    BucketType state{BucketType::ESS};

};

class HashTable
{
    public:
    HashTable(size_t initCapacity = 8);

    //Insert (key,value). Returns false if key exists already
    bool insert(const std::string& key, const size_t& value);
    //Remove (key,value). Returns true if something was removed
    bool remove(const std::string& key);
    //Return true if key is in table
    bool contains(const std::string& key) const;

    //get value for key, nullptr if not found
    std::optional<size_t> get(const std::string& key) const;

    //Access values in map: int idNunm = hashTable("Student1")
    //Also allows assignment: hashTable["Student1"] = 9876;
    size_t& operator[](const std::string& key);

    //returns all keys in table
    std::vector<std::string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;

    //used to print contents of hash table
    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

    private:
    // Table Data
    std::vector<HashTableBucket> tableData;
    std::vector<size_t> offsets;
    size_t numItems{0};

    size_t hash(const std::string& key) const;
    size_t findIndex(const std::string& key) const;
    void resizeIfNeeded();
    void rehash(size_t newCapacity);
    void initOffsets(size_t N);
};
