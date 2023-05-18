#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode* createNode() {
    TrieNode* node = new TrieNode;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    node->isEndOfWord = false;
    return node;
}

void insert(TrieNode* root, string word) {
    TrieNode* node = root;
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (!node->children[index])
            node->children[index] = createNode();
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

vector<string> findWords(TrieNode* root, string prefix) {
    vector<string> words;

    TrieNode* node = root;
    for (int i = 0; i < prefix.length(); i++) {
        int index = prefix[i] - 'a';
        if (!node->children[index])
            return words;
        node = node->children[index];
    }

    if (node->isEndOfWord)
        words.push_back(prefix);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            vector<string> suffixes = findWords(node->children[i], prefix + char('a' + i));
            words.insert(words.end(), suffixes.begin(), suffixes.end());
        }
    }

    return words;
}

int main() {
    // Читаем словарь из файла
    ifstream file("dictionary.txt");
    string word;
    TrieNode* root = createNode();
    while (file >> word)
        insert(root, word);
    file.close();

    // Запускаем бесконечный цикл чтения ввода от пользователя
    while (true) {
        cout << "Введите слово (для выхода введите 'exit'): ";
        string input;
        cin >> input;

        if (input == "exit")
            break;

        vector<string> words = findWords(root, input);
        if (words.empty())
            cout << "Слово не найдено в словаре." << endl;
        else {
            cout << "Найдены следующие слова:" << endl;
            for (string word : words)
                cout << word << endl;
        }
    }

    return 0;
}