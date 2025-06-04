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

- C++17 or later

### Clone and Compile

1. Clone the repository:

```bash
git clone https://github.com/yourusername/tag-manager.git
cd tag-manager
```

2. Build using CMake:

```bash
cmake -S . -B build
cmake --build build
```

The executable `tm` will be created in the `build` directory (or
`build/Release` on Windows).

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
./tm --search --tag <tag_name>
```

Example:

```bash
./tm --search --tag algorithms
```

### List All Tags

```bash
./tm --list
```

### Update a Tag

```bash
./tm --update --tag <tag_name> --name <new_name> --color <new_color>
```

Example:

```bash
./tm --update --tag algorithms --name algo --color #FF0000
```

### Delete a Tag by Name

```bash
./tm --delete --tag <tag_name>
./tm --delete --name <tag_name>
```

Example:

```bash
./tm --delete --tag algorithms
./tm --delete --name algo
```

### Delete Tags by Color

```bash
./tm --delete --color <color>
```

Example:

```bash
./tm --delete --color #FF0000
```

### Delete Tags by Category

```bash
./tm --delete --category <category>
```

Example:

```bash
./tm --delete --category movies
```

### Help

For a list of available commands and usage examples:

```bash
./tm --help
```

## Continuous Integration

The repository includes a GitHub Actions workflow that builds the project on
Linux and Windows. Successful builds produce the `tm` executable in the
`build` directory (or `build/Release` on Windows).

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## Authors

- David Chincharashvili - [My GitHub Profile](https://github.com/davidtbilisi)

