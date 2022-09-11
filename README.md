# Genelar
You can use the program by executing the following commands
- `add <id> <string>` - adds a string with id `<id>`
- `remove <id>` - removes the string with id `<id>`
- `query <string>` - prints all `id`s of strings that contain `<string>`
- `quit`

# Complexity
- `add` command - `O(LENGTH_OF_STRING * log(LENGTH_OF_ALL_ACTIVE_STRINGS))`
- `remove` command - `O(LENGTH_OF_STRING * log(LENGTH_OF_ALL_ACTIVE_STRINGS))`
- `query` command - `O(NUMBER_OF_FOUND_MATCHES * log(LENGTH_OF_ALL_ACTIVE_STRINGS))`

# Example usage
```
add 1 alabala
add 2 allow
query al
Entries containing the queried string:  1 2
remove 1
query al
Entries containing the queried string:  2
quit
```

