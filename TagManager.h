#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <string>

struct Category {
    std::string created_at;
    std::string updated_at;
    std::string name;
    std::string color;

    Category();
};

struct Tag {
    std::string created_at;
    std::string updated_at;
    std::string name;
    Category category;
    std::string fullPath;

    Tag();
};

class TagManager {
public:
    void createTag(const std::string& name, const std::string& path);
    void searchTag(const std::string& name);
    void listTags();
    void updateTag(const std::string& name, const std::string& newName, const std::string& color);
    void deleteTag(const std::string& name);
    void deleteTagByColor(const std::string& color);
    void deleteTagByCategory(const std::string& category);
    static void help();

private:
    bool fileExists(const std::string& name);
    std::string readFile(const std::string& name);
    bool appendTagToFile(const Tag& tag);
};

#endif // TAGMANAGER_H
