#pragma once
#include <unordered_map>

/**
 * 支持所有字符的前缀树
*/
class Trie {
public:
  Trie() = default;

  void Insert(std::string word) {
    int sz = word.size();
    Trie* cur = this;
    for (int i = 0; i < sz; i++) {
        if (cur->children_.count(word[i])) {
            cur = cur->children_[word[i]];
        } else {
            Trie* new_node = new Trie;
            cur->children_[word[i]] = new_node;
            cur = new_node;
        }
    }
    cur->is_end_ = true;
  }

  bool Search(std::string word) {
    Trie* res = SearchPrefix(word);
    return res && res->is_end_;

  }

  bool StartsWith(std::string prefix) {
    return !!SearchPrefix(prefix);
  }

private:
  std::unordered_map<char, Trie*> children_;
  bool is_end_ = false;

  Trie* SearchPrefix(std::string prefix) {
    int sz = prefix.size();
    Trie* cur = this;
    for (int i = 0; i < sz; i++) {
        if (cur->children_.count(prefix[i])) {
            cur = cur->children_[prefix[i]];
        } else {
            return nullptr;
        }
    }
    return cur;
  }
};