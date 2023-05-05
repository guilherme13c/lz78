#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::pair;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

// The Node class represents a node in the compact trie dictionary
class Node {
  public:
    int index; // The index of the node in the dictionary
    char c;    // The character at this node
    unordered_map<char, Node *> children; // Pointers to the node's children

    // Constructor
    Node(int i, char ch) : index(i), c(ch) {}

    // Destructor
    ~Node() {
        for (auto it : children) {
            delete it.second;
        }
    }
};

// The LZ78 class represents the LZ78 encoder and decoder
class LZ78 {
  public:
    // Encode the input text using LZ78 with a compact trie dictionary
    static vector<pair<int, char>> encode(string input) {
        vector<pair<int, char>> output;
        unordered_map<string, int> dictionary;
        int next_index = 1;
        Node *root = new Node(0, '\0');
        Node *current = root;

        // Iterate through the input text
        for (char c : input) {
            string s = "" + (char)(current->c + c);

            // If the current node's children include the next character,
            // continue down the trie
            if (current->children.count(c)) {
                current = current->children[c];
            }
            // Otherwise, add the new string to the dictionary
            else {
                output.push_back({current->index, c});
                dictionary[s] = next_index;
                next_index++;
                current->children[c] = new Node(dictionary[s], c);
                current = root;
            }
        }

        // Handle the last character
        output.push_back({current->index, '\0'});

        delete root;

        return output;
    }

    // Decode the input vector of pairs using LZ78 with a compact trie
    // dictionary
    static string decode(vector<pair<int, char>> input) {
        unordered_map<int, string> dictionary;
        int next_index = 1;
        string output = "";

        for (auto p : input) {
            int index = p.first;
            char c = p.second;

            // If the index is 0, the string is just the character
            if (index == 0) {
                output += c;
                dictionary[next_index] = string(1, c);
                next_index++;
            }
            // Otherwise, append the dictionary entry to the output
            else {
                string s = dictionary[index] + c;
                output += s;
                dictionary[next_index] = s;
                next_index++;
            }
        }

        return output;
    }
};

static void save_encoded_file(string file_name,
                              vector<pair<int, char>> encoded) {
    ofstream fout(file_name);

    for (auto p : encoded) {
        fout << p.first << "," << p.second << "\n";
    }

    fout.close();
}

static vector<pair<int, char>> read_encoded_file(string input_file_name) {
    vector<pair<int, char>> encoded = vector<pair<int, char>>();
    ifstream fin(input_file_name);

    // Read each line of the file
    string line;
    while (getline(fin, line)) {
        // Parse the line into pairs
        stringstream ss(line);

        string pair_str;
        while (getline(ss, pair_str)) {
            int comma_pos = (int)(pair_str.find(','));
            int index = stoi(pair_str.substr(0, comma_pos));
            char c = pair_str[comma_pos + 1];
            encoded.push_back({index, c});
        }
    }

    fin.close();
    return encoded;
}
