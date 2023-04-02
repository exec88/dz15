#include "chat.h"
#include "iostream"

void Chat::reg(Login _login, char* _pass, int pass_length) {

    hs.add(_login, sha1(_pass, pass_length));
}

bool Chat::login(Login _login, char _pass[], int pass_length) {

    bool success = false;

    if (hs.checkLogin(_login))
    {
        uint* pass_sha1_hash = hs.find(_login);
        uint* digest = sha1(_pass, pass_length);

        success = !memcmp(pass_sha1_hash, digest, SHA1HASHLENGTHBYTES);
        delete[] digest;
    }

    return success;
}