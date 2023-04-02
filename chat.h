#include "sha1.h"
#include "hash.h"

class Chat {
public:
    Chat() {}
    Chat(Hash _hs) : hs(_hs) {}
    void reg(Login login, char* pass, int pass_length);
    bool login(Login login, char* pass, int pass_length);

private:
    Hash hs;
};