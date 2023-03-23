#include "trie1.h"

int main() {
    Trie* trie = new Trie;
    trie->Insert("apple");
    trie->Search("apple");
    trie->Search("app");
    trie->StartsWith("app");
    trie->Insert("app");
    trie->Search("app");
    return 0;
}