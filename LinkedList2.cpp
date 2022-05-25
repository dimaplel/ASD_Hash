#include "LinkedList2.h"

Data::Data()
{
    char names[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    name = names[rand() % sizeof(names)];
    treatsPerDay = rand() % 75 + 15;
    fluffiness = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
}

void Data::print() const
{
    cout.precision(2);
    cout << "Name: " << name << " Treats per day: " << treatsPerDay << " Fluffiness: " << fluffiness << "\n";
}

LinkedList::LinkedList()
{
    head = nullptr;
    list_size = 0;
}

LinkedList::~LinkedList()
{
    HashNode* cur_node;

    while(head)
    {
        cur_node = head;
        head = head->next_node;
        cur_node->~HashNode();
    }
}

void LinkedList::push_front(unsigned long long key, const Data &data)
{
    auto* node = new HashNode{key, data, head};
    head = node;
    list_size++;
}

bool LinkedList::erase(unsigned long long key)
{
    HashNode* cur_node = head;
    HashNode* prev = nullptr;

    while(cur_node)
    {
        if(key == cur_node->key)
        {
            if(prev)
                prev->next_node = cur_node->next_node;
            else head = cur_node->next_node;

            cur_node->~HashNode();
            list_size--;
            return true;
        }
        prev = cur_node;
        cur_node = cur_node->next_node;
    }
    return false;

}

Data* LinkedList::get(unsigned long long key) const
{
    HashNode* cur_node = head;

    while(cur_node)
    {
        if(cur_node->key == key)
            return &cur_node->data;

        cur_node = cur_node->next_node;
    }
    return nullptr;
}

void LinkedList::print(bool swtch) const
{
    HashNode* cur_node = head;

    if(swtch)
    {
        for (int i = 0; i < list_size; i++) {
            cur_node->data.print();
            cur_node = cur_node->next_node;
        }
    }
    else
    {
        for (int i = 0; i < list_size; i++) {
            cout << "key " << i + 1 << ": " << cur_node->key << "\n";
            cur_node = cur_node->next_node;
        }
    }
}
