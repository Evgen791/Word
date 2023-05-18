#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    vector<TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : children(ALPHABET_SIZE, nullptr), isEndOfWord(false) {}
};

void insert(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (!node->children[index]) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

void findAutocomplete(TrieNode* root, const string& prefix, vector<string>& result) {
    TrieNode* node = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (!node->children[index]) {
            return; // Префикс не найден в дереве
        }
        node = node->children[index];
    }

    // Обход дочерних узлов и добавление слов в результат
    function<void(TrieNode*, string)> traverse = [&](TrieNode* curNode, string curStr) {
        if (curNode->isEndOfWord) {
            result.push_back(prefix + curStr);
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (curNode->children[i]) {
                traverse(curNode->children[i], curStr + char(i + 'a'));
            }
        }
    };

    traverse(node, "");
}

int main() {
    // Построение Trie из словаря
    vector<string> dictionary = {"apple", "application", "apartment", "baby", "backpack", "cat", "car", "card", "dog", "door"};
    TrieNode* root = new TrieNode();
    for (const auto& word : dictionary) {
        insert(root, word);
    }

    // Цикл чтения строк и вывода автодополнений
    while (true) {
        cout << "Введите часть слова для автодополнения: ";
        string prefix;
        getline(cin, prefix);

        vector<string> result;
        findAutocomplete(root, prefix, result);

        if (result.empty()) {
            cout << "Слова на префикс '" << prefix << "' не найдены." << endl;
        } else {
            for (const auto& word : result) {
                cout << word << endl;
            }
        }
    }

    return 0;
}
