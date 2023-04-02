#pragma once
#include <string.h>
#include "sha1.h"
#pragma warning(push)
#pragma warning(disable: 28719) // __WARNING_BANNED_API_USAGE
#pragma warning(disable: 28726) // __WARNING_BANNED_API_USAGEL2


#define LOGLENGTH 10                      

typedef char Login[LOGLENGTH];           //логин

class Hash {                         // хеш

public:

    Hash();
    ~Hash();
    void add(Login login, uint* pass_sha1_hash);
    void del(Login login);
    uint* find(Login login);
    bool checkLogin(Login login);

private:

    enum class enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair {                             //ключ-значение

        Pair() :                           // конструктор 
            login(""),
            pass_sha1_hash(nullptr),
            status(enPairStatus::free) {

        }
        Pair(Login _login, uint* _pass_sha1_hash)
        {
            status = enPairStatus::engaged;
            strcpy(login, _login);
            pass_sha1_hash = _pass_sha1_hash;

        }
        Pair(const Pair& other)
        {
            strcpy(login, other.login);
            pass_sha1_hash = other.pass_sha1_hash;
        }
        Pair& operator = (const Pair& other) { //  оператор присваивания
            strcpy(login, other.login);
            status = other.status;

            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            return *this;
        }

        uint* pass_sha1_hash;
        Login login;
        enPairStatus status; // состояние ячейки
    };

    int hash_func(Login login, int offset);
    void resize();


    Pair* array;
    int mem_size;
    int count;

};