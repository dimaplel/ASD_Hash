#include <unordered_map>
//#include "HashTable.h"
#include "HashMapOA.h"

using namespace std;

unsigned long long generateRandLong()
{
    unsigned long long key = 1;
    size_t iter = rand() % 14 + 7;
    for(int i = 0; i < iter; ++i)
        key += pow((rand() % 15), i);
    return key;
}

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
// generate random keys:
    long long* keys = new long long[keysAmount];
    long long* keysToInsert = new long long[iters];
    long long* keysToErase = new long long[iters];
    long long* keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generateRandLong();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }
// test my HashTable:
    HashMapOA hashTable;
    clock_t myStart = clock();
    clock_t insert_stime = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.insert(keysToInsert[i], Data());
    }
//    cout << "Inserting done!\n";
    clock_t insert_etime = clock();
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
//    cout << "Erasing done!\n";
    clock_t erase_time = clock();
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
//    cout << "Finding done!\n";
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
// test STL hash1 table:
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({keysToInsert[i], Data()});
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
         ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
         << ", found amount: " << stlFoundAmount << endl << endl;

//    cout << "Insert time: " << (double(-insert_stime + insert_etime)) / CLOCKS_PER_SEC << ";    Erasing time: " <<
//    (double(-insert_etime + erase_time)) / CLOCKS_PER_SEC <<";   Find time: " <<
//    (double(-erase_time + myEnd)) / CLOCKS_PER_SEC << ";\n";
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
                                                                        stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}
