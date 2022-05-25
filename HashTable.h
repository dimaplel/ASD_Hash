#ifndef ASD2_2_HASHTABLE_H
#define ASD2_2_HASHTABLE_H

#include "LinkedList2.h"

struct HashTable
{
    LinkedList* bucketsArray;
    size_t hash_size, hash_capacity;
    float MaxLoadFactor;

    HashTable()
    {
        hash_size = 0;
        hash_capacity = 6;
        bucketsArray = new LinkedList[hash_capacity];
        MaxLoadFactor = 0.7;
    }

    ~HashTable()
    {
        for(size_t i = 0; i < hash_capacity; i++)
            bucketsArray[i].~LinkedList();
    }

    size_t hash(unsigned long long key) const
    {
        return ((key * 25) % 4194610382161) % hash_capacity;
    }

    void reallocate(float times)
    {
        if(times < 1.0f)
            times = 2.0f;

        size_t prev_cap = hash_capacity;
        hash_capacity *= times;

        auto* new_buckets = new LinkedList[hash_capacity];

        for(int i = 0; i < prev_cap; i++)
        {
            LinkedList& cur_list = bucketsArray[i];
            HashNode* cur_node = cur_list.head;

            while(cur_node)
            {
                size_t index = hash(cur_node->key);
                LinkedList& new_list = new_buckets[index];

                Data* data = new_list.get(cur_node->key);
                if(data)
                    *data = cur_node->data;
                else
                    new_list.push_front(cur_node->key, cur_node->data);

                cur_node = cur_node->next_node;
            }
        }
        delete[] bucketsArray;
        bucketsArray = new_buckets;
    }

    void insert(unsigned long long key, const Data& data)
    {
        float loadFactor = static_cast<float>(hash_size) / static_cast<float>(hash_capacity);
        if(MaxLoadFactor < loadFactor)
        {
            float times = 2.0;
            reallocate(times);
        }
        size_t index = hash(key);
        LinkedList& list = bucketsArray[index];

        Data* pointer = list.get(key);
        if(pointer)
        {
            *pointer = data;
            return;
        }

        list.push_front(key, data);
        hash_size++;
    }

    void erase(unsigned long long key)
    {
        size_t index = hash(key);
        LinkedList& list = bucketsArray[index];

        if(list.erase(key))
            hash_size--;
    }

    Data* find(unsigned long long key)
    {
        size_t index = hash(key);
        LinkedList& list = bucketsArray[index];
        return list.get(key);
    }

    size_t size() const {return hash_size;}
};

#endif //ASD2_2_HASHTABLE_H