#ifndef ASD2_2_HASHMAPOA_H
#define ASD2_2_HASHMAPOA_H

#include <iostream>
#include <cmath>
using namespace std;

struct Data
{
    char name;
    short treatsPerDay;
    float fluffiness;

    Data()
    {
        char names[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
        name = names[rand() % sizeof(names)];
        treatsPerDay = rand() % 75 + 15;
        fluffiness = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
    ~Data() = default;

    void print() const
    {
        std::cout.precision(2);
        std::cout << "Name: " << name << " Treats per day: " << treatsPerDay << " Fluffiness: " << fluffiness << "\n";
    }
};


struct HashNode
{
    int status = 0;     // 0 - empty; 1 - removed; 2 - occupied
    Data data;
    unsigned long long key;
};

struct HashMapOA
{
    HashNode* bucketsArray;
    size_t hash_size, hash_capacity;
    float MaxLoadFactor;

    HashMapOA()
    {
        hash_size = 0;
        hash_capacity = 7;
        bucketsArray = new HashNode[hash_capacity];
        MaxLoadFactor = 0.5;
    }

    ~HashMapOA()
    {
        delete[] bucketsArray;
    }

    static size_t nearest_prime(size_t number)
    {
        for(int i = number + 1;;i++)
        {
            bool null_rest = false;
            for(size_t j = 2; j <= round(sqrt(i)); j++)
            {
                if(i % j == 0)
                {
                    null_rest = true;
                    break;
                }
            }
            if(!null_rest)
                return i;
        }
    }

    size_t hash1(unsigned long long key) const
    {
        return ((key * 18 - 41) % 4194610382161);
    }
    size_t hash2(unsigned long long key) const
    {
        return 982137816722392 - (key * 21988211);
    }

    void reallocate(float times)
    {
        if(times < 1.0)
            times = 2.0;

        size_t old_capacity = hash_capacity;
        hash_capacity = nearest_prime(old_capacity * times);

        auto* new_bucketsArray = new HashNode[hash_capacity];
        for(size_t i = 0; i < old_capacity; i++)
        {
            HashNode& copy = bucketsArray[i];
            if(copy.status == 2)
            {
                size_t first_hash = hash1(copy.key) % hash_capacity;
                size_t second_hash = hash2(copy.key) % hash_capacity;
                size_t index = first_hash;
                if(second_hash == 0)
                    second_hash = 1;

                for(int j = 1; new_bucketsArray[index].status != 0; j++)
                    index = (first_hash + j * second_hash) % hash_capacity;

                new_bucketsArray[index] = copy;
            }
        }

        delete[] bucketsArray;
        bucketsArray = new_bucketsArray;
    }

    void insert(unsigned long long key, const Data& value)
    {
        float loadFactor = static_cast<float>(hash_size) / static_cast<float>(hash_capacity);
        if(MaxLoadFactor <= loadFactor)
        {
            float times = 2.0;
            reallocate(times);
        }

        size_t first_hash = hash1(key) % hash_capacity;
        size_t second_hash = hash2(key) % hash_capacity;
        size_t index = first_hash;
        if(second_hash == 0)
            second_hash = 1;

        size_t i = 1;
        while(bucketsArray[index].status == 2)
        {
            HashNode& copy = bucketsArray[index];
            if(copy.key == key)
            {
                copy.data = value;
                return;
            }
            index = (first_hash + i * second_hash) % hash_capacity;
            i++;
        }

        bucketsArray[index] = {2, value, key};
        hash_size++;
    }

    Data* find(unsigned long long key) const
    {
        size_t first_hash = hash1(key) % hash_capacity;
        size_t second_hash = hash2(key) % hash_capacity;
        size_t index = first_hash;
        if(second_hash == 0)
            second_hash = 1;

        int i = 1;
        while(bucketsArray[index].status != 0)
        {
            if(bucketsArray[index].key == key)
            {
                Data* pointer = nullptr;
                if(bucketsArray[index].status == 2)
                    pointer = &bucketsArray[index].data;

                return pointer;
            }
            index = (first_hash + i * second_hash) % hash_capacity;
            i++;
        }
        return nullptr;
    }

    void erase(unsigned long long key)
    {
        size_t first_hash = hash1(key) % hash_capacity;
        size_t second_hash = hash2(key) % hash_capacity;
        size_t index = first_hash;
        if(second_hash == 0)
            second_hash = 1;

        int i = 1;
        while(bucketsArray[index].status != 0)
        {
            HashNode& copy = bucketsArray[index];
            if(copy.key == key)
            {
                if(copy.status == 2)
                {
                    copy.status = 1;
                    hash_size--;
                }
                return;
            }
            index = (first_hash + i * second_hash) % hash_capacity;
            i++;
        }
    }

    size_t size() const {return hash_size;}
};
#endif //ASD2_2_HASHMAPOA_H
