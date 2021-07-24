# string_toolkit.h
A simple C/C++ library containing tools to manipulate a C string. Inspired by [string-toolkit by VoltrexMaster](https://github.com/VoltrexMaster/string-toolkit). Everything is contained in the header file so you can just download it.

All structs, functions, and macro names start with a `st_` prefix.

## Structs
### `st_str_arr`
Represents an array of strings.
- `char ** data` The array. Can be `NULL` if the size below is `0`.
- `const unsigned int size` The array size.

### `st_uint_arr`
Represents a dynamically allocated unsigned integer array. Similar to the struct above.
- `unsigned int * data` The array. Can be `NULL` if the size below is `0`.
- `const unsigned int size` The array size.

### `st_flag_data`
The data returned after retrieving a value from a console flag.
- `char * value` The string value. Could be `NULL` if the one or more booleans below are not `1`.
- `const bool found` A boolean that tells whether it found the flag or not.
- `const bool has_value` A boolean that tells whether the flag has any value or not. Can be `0` if things like `--flag --flag2` happened.

## Functions

### Return a list of indexes matching a character
Returns a [`st_uint_arr`](#st_uint_arr) struct. Array returned can be empty if the provided string is empty or if the character does not exist in the string.
```c
st_uint_arr indexes = st_get_indexes("Hello, World!", 'l');

if (indexes.data != NULL) {
    for (unsigned int i = 0; i < indexes.size; i++) {
        printf("%d\n", indexes.data[i]);
    }
}
```

### Repeat a string several times
Returns `NULL` if the string is empty or if the second argument is `0`.
```c
char * repeated_string = st_repeat("Hello", 5);
// "HelloHelloHelloHelloHello"
```

### Check if a string start or ends with a specific string
Self-explanatory.
```c
bool a = st_starts_with("Hello", "He");

bool b = st_ends_with("Hello", "lo");
```

### Strip a string from a character
Strips a string from a specific character. Returns `NULL` if the string is empty.
```c
char * text = st_strip(" text ", ' ');
// "text"
```

### Split a string by a character
Splits the string by a character delimiter. Returns a [`st_str_arr`](#st_str_arr) struct, as follows.
```c
st_str_arr arr1 = st_split("Hello world!", ' ');
// { "Hello", "world!" }

st_str_arr arr2 = st_split("  Hello   world!  ", ' ');
// { "Hello", "world!" }

st_str_arr arr3 = st_split(" Hello ", ' ');
// empty array

st_str_arr arr4 = st_split("       ", ' ');
// empty array
```

### Split a string by chunks
Splits the string to chunks in the form of a string array. Returns a [`st_str_arr`](#st_str_arr) struct, the string array can be empty if the specified string is longer than the chunk amount.

```c
st_str_arr arr = st_to_chunks("Hello world!", 5);
// { "Hello", " worl", "d!" }
```

### Get the sub-string of a string
Slices a string like so. Returns `NULL` if the sum of both numbers is equal or more than the string length.
```c
char * sub_string = st_substr("Super awesome!", 6, 7);
// outputs "awesome"
```
> in C++, the third parameter is optional, and it defaults to `0`.

### Convert string to abbreviation
Converts the string to the abbreviation for it. e.g: `Hello, World!` to `HW`. Returns `NULL` if the string length is less than `2`.
```c
char * abbreviation = st_to_abbreviation("Hello, World!");
```

### Create a progress-bar
Creates a progress-bar-like string. Returns `NULL` if:
- The second parameter is less than the first one,
- The second parameter is `0`,
- The first or second parameter is less than `0`, or
- The last parameter is `0`.

```c
// create a 50%-like progress bar
char * progress = st_progress_bar(
    50.0, // in total
    100.0, // total
    '=', // elapsed progress character
    '@', // seek progress character
    '-', // empty progress character
    10 // progress bar character length
);
```

### Scramble a string
Scrambles the characters of a string.
```c
char string[] = "My string!";
st_scramble(string);
```

### Mock-ify a string
Converts a string to random-case. Basically mocking it.
```c
char string[] = "Super funny text";
st_mock(string);
```

### Convert a string to proper-case
Convert things like `this is a text` to `This Is A Text`, yes it may not be perfect, but at least it's somewhat good.
```c
char string[] = "this is a text";
st_proper_case(string);
```

### Check if a string contains a discord custom emoji
A discord custom emoji can be `<:emoji_name:emoji_id>` or `<a:emoji_name:emoji_id>`. This function validates if the specified string contains them.
```c
bool has_custom_emoji1 = st_has_custom_emoji("This is a text");
// returns 0

bool has_custom_emoji2 = st_has_custom_emoji("This is a text <a:something:66666666666666666>");
// returns 1
```

### Dynamically concatenate two or more strings together
Like `strcat` but you can specify more than two strings, and you don't need to specify the fixed string length for the result. Returns `NULL` if one of the strings specified is empty.
```c
char * cat = st_dynamic_concat(3, "Something", " super ", "awesome!");
// returns "Something super awesome!"
```

### Shorten a string
Shortens a string, returns `NULL` if:
- the specified string length is lower or equal to the specified limit,
- the specified string is empty, or
- the specified limit is `0`.

You can also specify your own placeholder for the suffix. If the placeholder is `NULL` then it would refer to default (`...`)
```c
char * shortened = st_shorten("Something", 4, NULL);
// returns "Some..."

char * null = st_shorten("Something", 999, NULL);
// returns NULL

char * custom_placeholder = st_shorten("Something", 4, "???");
// returns "Some???"
```
> in C++, the third parameter is optional, and it defaults to `NULL`.

### Get console arguments without any options.
Filters things like `./a.out argument some text --arg1 wow --arg2 so fun` to `argument some text`.

Returns `NULL` if:
- Argument count is less than `2`
- The argument is like `./a.out --arg1 wow --arg2 so fun` so the result could be an empty string.
```c
int main(int argc, char ** argv) {
    char * result = st_get_content_no_options(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    }
    
    return 0;
}
```

### Get console arguments without any flags.
Filters things like `./a.out argument some text --arg1 wow --arg2 so fun` to `argument some text wow so fun`.

Returns `NULL` if:
- Argument count is less than `2`
- The argument is like `./a.out --arg1 --arg2` so the result could be an empty string.
```c
int main(int argc, char ** argv) {
    char * result = st_get_content_no_flags(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    }
    
    return 0;
}
```

### Get console arguments flag value.
Gets the value from a console argument. Returns a [`st_flag_data`](#st_flag_data) struct.

```c
int main(int argc, char ** argv) {
    // argv is like "./a.out --flag argument stuff",
    // it would return "argument stuff"
    
    st_flag_data data = st_flag_get_value(argc, argv, "flag");
    
    if (data.value != NULL) {
        printf("%s\n", data.value);
    }
    
    return 0;
}
```

## Macros
### Check if a character is alphanumberic, or an underscore
```c
bool a = st_is_alnum('a');
// returns 1

bool b = st_is_alnum('/');
// returns 0
```

### Check if a character is a number
```c
bool a = st_is_num('6');
// returns 1

bool b = st_is_num('a');
// returns 0
```