/**
 * HashTable.h
 */

#include <string>
#include <ostream>
#include <cstddef>

enum class BucketType { NORMAL, ESS, EAR };

class HashTableBucket {};

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
