# Tag Manager (tm)

## Description

Tag Manager (tm) is a command-line utility for managing tags associated with files or directories. It allows you to create, search, list, update, and delete tags. The tags are stored in a JSON file named `tags.json`.

## Features

- Create tags for files or directories
- Search for tags
- List all tags
- Update existing tags
- Delete tags by name, color, or category

## Installation

### Prerequisites

- C++11 or later
- `jsoncpp` library

### Install `jsoncpp`

For Debian-based systems (e.g., Ubuntu):

```bash
sudo apt-get install libjsoncpp-dev
```

For Red Hat-based systems (e.g., Fedora):

```bash
sudo dnf install jsoncpp-devel
```

For macOS:

```bash
brew install jsoncpp
```

### Clone and Compile

1. Clone the repository:

```bash
git clone https://github.com/yourusername/tag-manager.git
cd tag-manager
```

2. Compile the source files:

```bash
g++ -o tm main.cpp TagManager.cpp -ljsoncpp
```

This will create an executable named `tm`.

## Usage

### Create a Tag

```bash
./tm --tag <tag_name> <full_path>
```

Example:

```bash
./tm --tag algorithms ./some/folder/or/file.txt
```

### Search for a Tag

```bash
./tm --search <tag_name>
```

Example:

```bash
./tm --search algorithms
```

### List All Tags

```bash
./tm --list
```

### Update a Tag

```bash
./tm --update <tag_name> <new_name> <new_color>
```

Example:

```bash
./tm --update algorithms algo #FF0000
```

### Delete a Tag by Name

```bash
./tm --delete <tag_name>
```

Example:

```bash
./tm --delete algorithms
```

### Delete Tags by Color

```bash
./tm --delete-color <color>
```

Example:

```bash
./tm --delete-color #FF0000
```

### Delete Tags by Category

```bash
./tm --delete-category <category>
```

Example:

```bash
./tm --delete-category movies
```

### Help

For a list of available commands and usage examples:

```bash
./tm
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## Authors

- David Chincharashvili - [My GitHub Profile](https://github.com/davidtbilisi)

## Acknowledgments

- Thanks to the contributors of the `jsoncpp` library.
