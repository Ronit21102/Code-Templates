#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <cstddef>

template<typename T, std::size_t AlphabetSize = 26>
class Trie {
public:
    struct Node {
        T value{};
        std::array<Node*, AlphabetSize> children{};
        bool isEnd = false;

        Node() = default;
        explicit Node(const T& val) : value(val) {}

        ~Node() {
            for (auto* child : children) {
                delete child;
            }
        }
    };

    Trie() : root(new Node()) {}

    ~Trie() { delete root; }

    // ---- Prefix Trie (standard) ----

    void insert(const std::string& word, const T& value = T{}) {
        Node* cur = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                cur->children[idx] = new Node(value);
            }
            cur = cur->children[idx];
        }
        cur->isEnd = true;
        cur->value = value;
    }

    bool search(const std::string& word) const {
        Node* cur = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return cur->isEnd;
    }

    bool startsWith(const std::string& prefix) const {
        Node* cur = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return true;
    }

    // ---- Suffix Trie (inserts words in reverse) ----

    void insertSuffix(const std::string& word, const T& value = T{}) {
        Node* cur = root;
        for (int i = (int)word.size() - 1; i >= 0; --i) {
            int idx = word[i] - 'a';
            if (!cur->children[idx]) {
                cur->children[idx] = new Node(value);
            }
            cur = cur->children[idx];
        }
        cur->isEnd = true;
        cur->value = value;
    }

    bool searchSuffix(const std::string& suffix) const {
        Node* cur = root;
        for (int i = (int)suffix.size() - 1; i >= 0; --i) {
            int idx = suffix[i] - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return cur->isEnd;
    }

    bool endsWith(const std::string& suffix) const {
        return searchSuffix(suffix);
    }

    // ---- Utility ----

    Node* getRoot() const { return root; }
    bool empty() const { return root == nullptr; }

    // Disable copy
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

private:
    Node* root;
};

// -----------------------------------------------------------------------
// Specialization: Trie with index tracking (from LeetCode pattern)
// -----------------------------------------------------------------------
template<std::size_t AlphabetSize = 26>
class IndexTrie {
public:
    struct Node {
        int idx = -1;
        std::array<Node*, AlphabetSize> children{};

        Node() = default;
        explicit Node(int id) : idx(id) {}

        ~Node() {
            for (auto* child : children) {
                delete child;
            }
        }
    };

    IndexTrie() : root(new Node(0)) {}
    ~IndexTrie() { delete root; }

    Node* getRoot() const { return root; }

    // Insert a word in reverse (suffix trie), tracking the index
    // maintainBest: if true, each node stores the index with the smallest word so far
    void insertSuffixWithIndex(const std::string& word, int index,
                               const std::vector<std::string>& container,
                               bool maintainBest = false) {
        Node* cur = root;
        int n = (int)word.size();

        if (maintainBest && container[root->idx] > container[index]) {
            root->idx = index;
        }

        for (int i = n - 1; i >= 0; --i) {
            int ch_idx = word[i] - 'a';
            if (!cur->children[ch_idx]) {
                cur->children[ch_idx] = new Node(index);
            }
            cur = cur->children[ch_idx];

            if (maintainBest && container[cur->idx].size() > (size_t)n) {
                cur->idx = index;
            }
        }
    }

    // Search for the longest common suffix
    // Returns the index stored at the deepest matching node
    int searchLongestSuffix(const std::string& word) const {
        Node* cur = root;
        int result = root->idx;

        for (int i = (int)word.size() - 1; i >= 0; --i) {
            int ch_idx = word[i] - 'a';
            cur = cur->children[ch_idx];
            if (!cur) return result;
            result = cur->idx;
        }
        return result;
    }

    // Disable copy
    IndexTrie(const IndexTrie&) = delete;
    IndexTrie& operator=(const IndexTrie&) = delete;

private:
    Node* root;
};

#endif // TRIE_HPP
