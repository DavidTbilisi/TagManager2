#include <iostream>
#include <string>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

// compile-time version supplied by CMake
#ifndef TM_VERSION
#define TM_VERSION "0.2.0"
#endif

using namespace std;

/*
    CPP_VERSION: 17
    Name: Tag manager (alias: tm)
    Version: 0.2.0
    Description: creating separate tags.json file to link files or folders with tags
    Examples: 
        tm --tag algorithms ./some/folder/or/file.txt
        tm --search --tag algorithms,algo,ds
        tm --search --tag algo
        tm --list
        tm --update --tag algorithms --name algo --color #FF0000
        tm --delete --tag algorithms
        tm --delete --name algo
        tm --delete --category movies
*/

struct Category {
    string created_at = to_string(time(0));
    string updated_at = to_string(time(0));
    string name = "default";
    string color = "#000000";
};

struct Tag {
    string created_at = to_string(time(nullptr));
    string updated_at = to_string(time(nullptr));
    string name;
    Category category;
    string fullPath;
};

vector<Tag> loadTags(const string& file = "tags.json");
void saveTags(const vector<Tag>& tags, const string& file = "tags.json");
void createTag(const string& name, const string& path);
void searchTag(const string& name);
void listTags();
void updateTag(const string& name, const string& newName, const string& color);
void deleteTag(const string& name);
void deleteTagByColor(const string& color);
void deleteTagByCategory(const string& category);
vector<Tag> loadTags(const string& file) {
    vector<Tag> tags;
    ifstream in(file);
    if (!in.is_open()) {
        return tags;
    }
    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    size_t pos = 0;
    while ((pos = data.find('{', pos)) != string::npos) {
        size_t end = data.find('}', pos);
        if (end == string::npos) break;
        string obj = data.substr(pos + 1, end - pos - 1);
        auto get = [&](const string& key) {
            string search = "\"" + key + "\"";
            size_t kp = obj.find(search);
            if (kp == string::npos) return string();
            kp = obj.find('"', kp + search.size());
            if (kp == string::npos) return string();
            size_t ep = obj.find('"', kp + 1);
            if (ep == string::npos) return string();
            return obj.substr(kp + 1, ep - kp - 1);
        };
        Tag t;
        t.name = get("name");
        t.fullPath = get("fullPath");
        t.category.name = get("category");
        t.category.color = get("color");
        t.created_at = get("created_at");
        t.updated_at = get("updated_at");
        tags.push_back(t);
        pos = end + 1;
    }
    return tags;
}

void saveTags(const vector<Tag>& tags, const string& file) {
    ofstream out(file, ios::trunc);
    out << "[\n";
    for (size_t i = 0; i < tags.size(); ++i) {
        const Tag& t = tags[i];
        out << "  {\"name\":\"" << t.name << "\",";
        out << "\"fullPath\":\"" << t.fullPath << "\",";
        out << "\"category\":\"" << t.category.name << "\",";
        out << "\"color\":\"" << t.category.color << "\",";
        out << "\"created_at\":\"" << t.created_at << "\",";
        out << "\"updated_at\":\"" << t.updated_at << "\"}";
        if (i + 1 < tags.size()) out << ",";
        out << "\n";
    }
    out << "]\n";
}

void createTag(const string& name, const string& path) {
    vector<Tag> tags = loadTags();
    Tag tag;
    tag.name = name;
    tag.fullPath = filesystem::absolute(path).string();
    tag.category = Category();
    time_t now = time(nullptr);
    tag.created_at = to_string(now);
    tag.updated_at = tag.created_at;
    tags.push_back(tag);
    saveTags(tags);
    cout << "Creating tag: " << tag.name << " with fullpath: " << tag.fullPath << endl;
}

void searchTag(const string& name) {
    vector<Tag> tags = loadTags();
    for (const auto& t : tags) {
        if (t.name == name) {
            cout << t.name << " -> " << t.fullPath << endl;
        }
    }
}

void listTags() {
    vector<Tag> tags = loadTags();
    for (const auto& t : tags) {
        cout << t.name << " -> " << t.fullPath << endl;
    }
}

void updateTag(const string& name, const string& newName, const string& color) {
    vector<Tag> tags = loadTags();
    for (auto& t : tags) {
        if (t.name == name) {
            t.name = newName;
            t.category.color = color;
            t.updated_at = to_string(time(nullptr));
        }
    }
    saveTags(tags);
}

void deleteTag(const string& name) {
    vector<Tag> tags = loadTags();
    tags.erase(remove_if(tags.begin(), tags.end(), [&](const Tag& t){ return t.name == name; }), tags.end());
    saveTags(tags);
}

void deleteTagByColor(const string& color) {
    vector<Tag> tags = loadTags();
    tags.erase(remove_if(tags.begin(), tags.end(), [&](const Tag& t){ return t.category.color == color; }), tags.end());
    saveTags(tags);
}

void deleteTagByCategory(const string& category) {
    vector<Tag> tags = loadTags();
    tags.erase(remove_if(tags.begin(), tags.end(), [&](const Tag& t){ return t.category.name == category; }), tags.end());
    saveTags(tags);
}

void printVersion() {
    cout << "tm version " << TM_VERSION << endl;
}

void help() {
    cout << "Name: Tag manager (tm)" << endl;
    cout << "Examples: " << endl;
    cout << "    tm --tag algorithms ./some/folder/or/file.txt" << endl;
    cout << "    tm --search --tag algorithms" << endl;
    cout << "    tm --search --tag algo" << endl;
    cout << "    tm --list" << endl;
    cout << "    tm --update --tag algorithms --name algo --color #FF0000" << endl;
    cout << "    tm --delete --tag algorithms" << endl;
    cout << "    tm --delete --name algo" << endl;
    cout << "    tm --delete --category movies" << endl;
    cout << "    tm --version" << endl;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: tm --help" << endl;
        return 1;
    }

    string command = argv[1];
    if (command == "--help") {
        help();
    } else if (command == "--tag") {
        if (argc < 4) {
            cout << "Usage: tm --tag <tag_name> <fullpath>" << endl;
            return 1;
        }
        createTag(argv[2], argv[3]);
    } else if (command == "--search") {
        if (argc < 4) {
            cout << "Usage: tm --search --tag <tag_name>" << endl;
            return 1;
        }
        searchTag(argv[3]);
    } else if (command == "--list") {
        listTags();
    } else if (command == "--update") {
        string tagName;
        string newName;
        string newColor;
        for (int i = 2; i < argc; ++i) {
            string arg = argv[i];
            if (arg == "--tag" && i + 1 < argc) tagName = argv[++i];
            else if (arg == "--name" && i + 1 < argc) newName = argv[++i];
            else if (arg == "--color" && i + 1 < argc) newColor = argv[++i];
        }
        if (tagName.empty() || newName.empty() || newColor.empty()) {
            cout << "Usage: tm --update --tag <tag_name> --name <new_name> --color <new_color>" << endl;
            return 1;
        }
        updateTag(tagName, newName, newColor);
    } else if (command == "--delete") {
        string name;
        string color;
        string category;
        for (int i = 2; i < argc; ++i) {
            string arg = argv[i];
            if ((arg == "--tag" || arg == "--name") && i + 1 < argc) name = argv[++i];
            else if (arg == "--color" && i + 1 < argc) color = argv[++i];
            else if (arg == "--category" && i + 1 < argc) category = argv[++i];
        }
        if (!name.empty()) deleteTag(name);
        if (!color.empty()) deleteTagByColor(color);
        if (!category.empty()) deleteTagByCategory(category);
    } else if (command == "--version") {
        printVersion();
    }
    return 0;
}
