#include "hash.h"
#include <iostream>
#include <string.h>
using namespace std;

Hash::Hash() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
Hash::~Hash() {
    delete[] array;
}
void Hash::add(Login login, uint* pass_sha1_hash) {
    int index = -1, i = 0;
    int freeCount = 0;
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status == enPairStatus::free) {
            freeCount++;
        }
    }

    if (freeCount == 0)
        resize();

    index = -1, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status == enPairStatus::free) {  // если нашли пустую €чейку то занимаем ее
            
            break;
        }
    }
    if (i >= mem_size) return;

    
    array[index] = Pair(login, pass_sha1_hash);     // положили в свободную €чейку
    count++;

}
int Hash::hash_func(Login login, int offset) {

    int sum = 0, i = 0;
    for (; i < LOGLENGTH; i++) {
        sum += login[i];
    }
    return (sum % mem_size + offset * offset) % mem_size;
}

void Hash::del(Login login) {

    int index = -1, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].login, login)) {
            array[index].status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}
uint* Hash::find(Login login) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        if (strcmp(array[index].login, login) == 0) {
            return array[index].pass_sha1_hash;
        }
    }

    return nullptr;
}

void Hash::resize() {

    Pair* save_ct = array;                        // помним о старом массиве
    int oldSize = mem_size;

    mem_size *= 2;                               // увеличиваем размер
    count = 0;
    array = new Pair[mem_size];                 //  нова€ пам€ть

    for (int i = 0; i < oldSize; i++) {
        Pair curr = save_ct[i];
        add(curr.login, curr.pass_sha1_hash);
    }

    delete[] save_ct;
}

bool Hash::checkLogin(Login login)
{
    bool success = false;
    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        if (strcmp(array[index].login, login) == 0)
        {
            success = true;
            break;
        }
    }
    return success;
}