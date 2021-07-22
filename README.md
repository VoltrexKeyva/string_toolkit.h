# string_toolkit.h
A simple C library containing tools to manipulate a C string. Inspired by [string-toolkit by VoltrexMaster](https://github.com/VoltrexMaster/string-toolkit). Everything is contained in the header file so you can just download it.

## Functions
All functions and macros start with a `st_` prefix.

### Convert string to abbreviation
Converts the string to the abbreviation for it. e.g: `Hello, World!` to `HW`
```c
char * abbreviation = st_to_abbreviation("Hello, World!");
```

### Create a progress-bar
Creates a progress-bar-like string.
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
int has_custom_emoji1 = st_has_custom_emoji("This is a text");
// returns 0

int has_custom_emoji2 = st_has_custom_emoji("This is a text <a:something:66666666666666666>");
// returns 1
```

### Dynamically concatenate two or more strings together
Like `strcat` but you can specify more than two strings, and you don't need to specify the fixed string length for the result.
```c
char * cat = st_dynamic_concat(3, "Something", " super ", "awesome!");
// returns "Something super awesome!"
```

### Shorten a string
Shortens a string, returns `NULL` if the specified string length is lower or equal to the specified limit. You can also specify your own placeholder for the suffix. If the placeholder is `NULL` then it would refer to default (`...`)
```c
char * shortened = st_shorten("Something", 4, NULL);
// returns "Some..."

char * null = st_shorten("Something", 999, NULL);
// returns NULL

char * custom_placeholder = st_shorten("Something", 4, "???");
// returns "Some???"
```


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
}
```

### Get console arguments flag value.
Gets the value from a console argument.

Returns a `st_flag_data` struct with the following structure.
- `char * value` The string value. Could be `NULL` if the one or more booleans below are not `1`.
- `const bool found` A boolean that tells whether it found the flag or not.
- `const bool has_value` A boolean that tells whether the flag has any value or not. Can be `0` if things like `--flag --flag2` happened.

```c
int main(int argc, char ** argv) {
    // argv is like "./a.out --flag argument stuff",
    // it would return "argument stuff"
    
    st_flag_data data = st_flag_get_value(argc, argv, "flag");
    
    if (data.value != NULL) {
        printf("%s\n", data.value);
    }
}
```

## Macros
### Check if a character is alphanumberic, or an underscore
```c
const bool a = st_is_alnum('a');
// returns 1

const bool b = st_is_alnum('/');
// returns 0
```

### Check if a character is a number
```c
const bool a = st_is_num('6');
// returns 1

const bool b = st_is_num('a');
// returns 0
```
