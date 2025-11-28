#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class ClsString {
private:
    string value_;

public:
    // Constructors
    ClsString() : value_("") {}
    ClsString(string value) : value_(value) {}

    // Getter & Setter
    void setValue(string value) { value_ = value; }
    string getValue() { return value_; }

    // Static utility functions (operate on any string)
    static string upperAllString(string str) {
        for (char &c : str) 
            c = toupper(c);
        return str;
    }

    static string lowerAllString(string str) {
        for (char &c : str) 
            c = tolower(c);
        return str;
    }

    static string trimLeft(string str) {
        while (!str.empty() && str[0] == ' ') 
            str.erase(0, 1);
        return str;
    }

    static string trimRight(string str) {
        while (!str.empty() && str[str.size() - 1] == ' ') 
            str.erase(str.size() - 1, 1);
        return str;
    }

    static string trim(string str) {
        return trimLeft(trimRight(str));
    }

    static vector<string> splitString(string str, const string& delimiter) {
        vector<string> vString;
        size_t pos;
        string word;
        while ((pos = str.find(delimiter)) != string::npos) {
            word = str.substr(0, pos);
            if (!word.empty())
                vString.push_back(word);
            str.erase(0, pos + delimiter.length());
        }
        if (!str.empty()) 
            vString.push_back(str);
        return vString;
    }

    static string joinString(const vector<string>& vString, const string& delimiter) {
        string str = "";
        for (const string& w : vString) 
            str += w + delimiter;
        if (!str.empty()) 
            str = str.substr(0, str.size() - delimiter.size());
        return str;
    }

    static string joinString(string strArr[], short arrSize, const string& delimiter) {
        string str = "";
        for (int i = 0; i < arrSize; i++) 
            str += strArr[i] + delimiter;
        if (!str.empty()) 
            str = str.substr(0, str.size() - delimiter.size());
        return str;
    }

    static string reverseWordsInString(string str) {
        vector<string> words = splitString(str, " ");
        string result = "";
        for (auto it = words.rbegin(); it != words.rend(); ++it) 
            result += *it + " ";
        if (!result.empty()) 
            result.pop_back();
        return result;
    }

    static string replace(string str, const string& targetWord, const string& replacementWord, bool matchCase = true) {
        vector<string> words = splitString(str, " ");
        for (string& w : words) {
            if (matchCase ? (w == targetWord) : (lowerAllString(w) == lowerAllString(targetWord))) {
                w = replacementWord;
            }
        }
        return joinString(words, " ");
    }

    static string removePunctuationsFromString(string str) {
        string result = "";
        for (char c : str) 
            if (!ispunct(c)) result += c;
        return result;
    }

    // Member functions (operate on value_)
    void upperAllString() {
        value_ = upperAllString(value_);
    }

    void lowerAllString() {
        value_ = lowerAllString(value_);
    }

    void trimLeft() {
        value_ = trimLeft(value_);
    }

    void trimRight() {
        value_ = trimRight(value_);
    }

    void trim() {
        value_ = trim(value_);
    }

    void reverseWordsInString() {
        value_ = reverseWordsInString(value_);
    }

    void replace(const string& targetWord, const string& replacementWord, bool matchCase = true) {
        value_ = replace(value_, targetWord, replacementWord, matchCase);
    }

    void removePunctuationsFromString() {
        value_ = removePunctuationsFromString(value_);
    }
};