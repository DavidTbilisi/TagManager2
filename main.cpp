#include <iostream>
#include <string>
#include <time.h>
#include <limits.h> // For PATH_MAX
#include <unistd.h> // For realpath()
#include <errno.h> // For errno
#include <cstring> // For strerror()
using namespace std;

/*
    CPP_VERSION: 11
    Name: Tag manager (alias: tm)
    Version: 0.1
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
    string name; // array of strings
    Category category;
    string fullPath;

};



void createTag(string name[], const string& path) {
    // check if name is array of strings or single string
    Tag tag;
    tag.name = name;
    tag.fullPath = path;

    cout << "Creating tag: " << tag.name << " with fullpath: " << tag.fullPath << endl;
}

void searchTag(string name) {
    cout << "Searching for tag: " << name << endl;

}

void listTags() {
    cout << "Listing all tags" << endl;
}

void updateTag(string name, string color) {
    cout << "Updating tag: " << name << " with color: " << color << endl;
}

void deleteTag(string name) {
    cout << "Deleting tag: " << name << endl;
}

void deleteTagByColor(string color) {
    cout << "Deleting tag by color: " << color << endl;
}

void deleteTagByCategory(string category) {
    cout << "Deleting tag by category: " << category << endl;
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
        if (argc < 6) {
            cout << "Usage: tm --update --tag <tag_name> --name <new_name> --color <new_color>" << endl;
            return 1;
        }
        updateTag(argv[3], argv[5]);
    } else if (command == "--delete") {
        if (argc < 3) {
            cout << "Usage: tm --delete --tag <tag_name>" << endl;
            cout << "Usage: tm --delete --name <tag_name>" << endl;
            return 1;
        }
        if (argc == 4) {
            deleteTag(argv[3]);
        } else if (argc == 5) {
            if (string(argv[3]) == "--name") {
                deleteTag(argv[4]);
            } else if (string(argv[3]) == "--color") {
                deleteTagByColor(argv[4]);
            }
        }
    }
    return 0;
}
