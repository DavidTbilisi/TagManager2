#include "TagManager.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    TagManager tm;

    if (argc < 2) {
        TagManager::help();
        return 0;
    }

    string command = argv[1];

    if (command == "--tag") {
        if (argc < 4) {
            cout << "Usage: tm --tag <tag_name> <full_path>" << endl;
            return 0;
        }
        string name = argv[2];
        string path = argv[3];
        tm.createTag(name, path);
    } else if (command == "--search") {
        if (argc < 3) {
            cout << "Usage: tm --search <tag_name>" << endl;
            return 0;
        }
        string name = argv[2];
        tm.searchTag(name);
    } else if (command == "--list") {
        tm.listTags();
    } else if (command == "--update") {
        if (argc < 5) {
            cout << "Usage: tm --update <tag_name> <new_name> <new_color>" << endl;
            return 0;
        }
        string name = argv[2];
        string newName = argv[3];
        string newColor = argv[4];
        tm.updateTag(name, newName, newColor);
    } else if (command == "--delete") {
        if (argc < 3) {
            cout << "Usage: tm --delete <tag_name>" << endl;
            return 0;
        }
        string name = argv[2];
        tm.deleteTag(name);
    } else if (command == "--delete-color") {
        if (argc < 3) {
            cout << "Usage: tm --delete-color <color>" << endl;
            return 0;
        }
        string color = argv[2];
        tm.deleteTagByColor(color);
    } else if (command == "--delete-category") {
        if (argc < 3) {
            cout << "Usage: tm --delete-category <category>" << endl;
            return 0;
        }
        string category = argv[2];
        tm.deleteTagByCategory(category);
    } else {
        TagManager::help();
    }
    return 0;
}
