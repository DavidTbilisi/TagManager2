#include "TagManager.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <cerrno>

using namespace std;

Category::Category() : created_at(to_string(time(nullptr))), updated_at(to_string(time(nullptr))), name("default"), color("#000000") {}

Tag::Tag() : created_at(to_string(time(nullptr))), updated_at(to_string(time(nullptr))) {}

bool TagManager::fileExists(const std::string& name) {
    return (access(name.c_str(), F_OK) != -1);
}

std::string TagManager::readFile(const std::string& name) {
    ifstream file(name);
    if (!file.is_open()) {
        cout << "Error: " << strerror(errno) << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

bool TagManager::appendTagToFile(const Tag& tag) {
    const string fileName = "tags.json";
    ofstream file;

    if (!fileExists(fileName)) {
        file.open(fileName, ios::out);
        file << "[]\n";
        file.close();
    }

    file.open(fileName, ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Error: " << strerror(errno) << endl;
        return false;
    }

    string content = readFile(fileName);
    if (content.empty()) {
        cout << "Error: Could not read file" << endl;
        return false;
    }

    size_t pos = content.find_last_of(']');
    if (pos == string::npos) {
        cout << "Error: Malformed JSON in file" << endl;
        return false;
    }
    content.erase(pos);

    string tagJson = R"({
        "created_at": ")" + tag.created_at + R"(",
        "updated_at": ")" + tag.updated_at + R"(",
        "name": ")" + tag.name + R"(",
        "category": {
            "created_at": ")" + tag.category.created_at + R"(",
            "updated_at": ")" + tag.category.updated_at + R"(",
            "name": ")" + tag.category.name + R"(",
            "color": ")" + tag.category.color + R"("
        },
        "fullPath": ")" + tag.fullPath + R"("
    })";

    content += (content.size() > 2 ? "," : "") + tagJson + "]";

    file.close();
    file.open(fileName, ios::out | ios::trunc);
    file << content;
    file.close();
    return true;
}

void TagManager::createTag(const std::string& name, const std::string& path) {
    Tag tag;
    tag.name = name;
    tag.fullPath = path;

    if (!appendTagToFile(tag)) {
        cout << "Error: Could not append tag to file" << endl;
        return;
    }

    cout << "Creating tag: '" << tag.name << "' with fullpath: " << tag.fullPath << endl;
}

void TagManager::searchTag(const std::string& name) {
    cout << "Searching for tag: " << name << endl;
}

void TagManager::listTags() {
    cout << "Listing all tags" << endl;
}

void TagManager::updateTag(const std::string& name, const std::string& newName, const std::string& color) {
    cout << "Updating tag: " << name << " to new name: " << newName << " with color: " << color << endl;
}

void TagManager::deleteTag(const std::string& name) {
    cout << "Deleting tag: " << name << endl;
}

void TagManager::deleteTagByColor(const std::string& color) {
    cout << "Deleting tag by color: " << color << endl;
}

void TagManager::deleteTagByCategory(const std::string& category) {
    cout << "Deleting tag by category: " << category << endl;
}

void TagManager::help() {
    cout << "Name: Tag manager (tm)" << endl;
    cout << "Examples: " << endl;
    cout << "    tm --tag <tag_name> <full_path>" << endl;
    cout << "    tm --search <tag_name>" << endl;
    cout << "    tm --list" << endl;
    cout << "    tm --update <tag_name> <new_name> <new_color>" << endl;
    cout << "    tm --delete <tag_name>" << endl;
    cout << "    tm --delete-color <color>" << endl;
    cout << "    tm --delete-category <category>" << endl;
}
