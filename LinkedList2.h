#ifndef ASD2_2_LINKEDLIST2_H
#define ASD2_2_LINKEDLIST2_H

#include <iostream>
#include <random>
#include <ctime>
#include <cstddef>

using std::cout;
using std::string;

struct Data
{
    char name;
    short treatsPerDay;
    float fluffiness;

    Data();
    ~Data() = default;

    void print() const;
};

struct HashNode
{
    unsigned long long key;
    Data data;
    HashNode* next_node;
};

struct LinkedList
{
    HashNode* head;
    size_t list_size;

    LinkedList();
    ~LinkedList();

    void push_front(unsigned long long key, const Data& data);
    Data* get(unsigned long long key) const;
    bool erase(unsigned long long key);
    size_t size() const {return list_size;}
    void print(bool swtch) const;
};
#endif //ASD2_2_LINKEDLIST2_H