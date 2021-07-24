#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define st_is_alnum(t) \
    (t > 47 && t < 58) || (t > 96 && t < 123) || (t > 64 && t < 91) || t == 95
#define st_is_num(t) \
    t > 47 && t < 58
#define _trim_arr(_t, _a, _ns, _na) \
    _na = (_t *)malloc(_ns * sizeof(_t)); for (unsigned int __i = 0; __i < _ns; __i++) _na[__i] = _a[__i]; free(_a)

#ifndef __cplusplus
// for C

#define _free_two_dim_arr(type, arr, length) \
    __free_two_dim_arr((void **)arr, length)
#define _allocate_memory(type, size) \
    malloc(size)
#define _opt_param(name, default) \
    name

#define bool         unsigned char
#define true         1
#define false        0

void __free_two_dim_arr(void ** arr, const unsigned int length)
#else
// for C++

#define _free_two_dim_arr(type, arr, length) \
    __free_two_dim_arr<type>(arr, length)
#define _allocate_memory(type, size) \
    (type)malloc(size)
#define _opt_param(name, default) \
    name = default

template<typename T>void __free_two_dim_arr(T ** arr, const unsigned int length)
#endif
{
    if (!length)
        return;
    
    for (unsigned int i = 0; i < length; i++)
        free(arr[i]);

    free(arr);
}

typedef struct {
    const unsigned int size;
    unsigned int * data;
} st_uint_arr;

st_uint_arr st_get_indexes(const char * str, const char character) {
    if (str[0] == '\0') {
        const st_uint_arr arr = { 0, NULL };
        return arr;
    }
    
    unsigned int * ptrl = _allocate_memory(unsigned int *, strlen(str) * sizeof(unsigned int));
    unsigned int size = 0;
    
    for (unsigned int i = 0; i < strlen(str); i++)
        if (str[i] == character) {
            ptrl[size] = i;
            size++;
        }
    
    if (!size) {
        free(ptrl);
        const st_uint_arr arr = { 0, NULL };
        return arr;
    }
    
    st_uint_arr arr = { size };
    if (size != strlen(str))
        _trim_arr(unsigned int, ptrl, size, arr.data);
    
    return arr;
}

char * st_repeat(const char * str, const unsigned int amount) {    
    if (!amount || str[0] == '\0')
        return NULL;
    else if (str[1] == '\0') {
        char * ptr = _allocate_memory(char *, amount * sizeof(char));
        memset(ptr, str[0], amount * sizeof(char));
        ptr[amount] = '\0';
        
        return ptr;
    }
    
    const unsigned int length = strlen(str) * amount;
    char * ptr = _allocate_memory(char *, length * sizeof(char));
    ptr[length] = '\0';
    
    for (unsigned int i = 0; i < length; i += amount) {
        unsigned int k = 0;
        for (unsigned int j = i; j < i + amount; j++) {
            ptr[j] = str[k];
            k++;
        }
    }
    
    return ptr;
}

bool st_starts_with(const char * string, const char * with_what) {
    const unsigned int length = strlen(with_what);
    if (length > strlen(string))
        return false;
    else if (with_what[0] == '\0' || string[0] == '\0')
        return true;
    
    for (unsigned int i = 0; i < length; i++)
        if (string[i] != with_what[i])
            return false;
    
    return true;
}

bool st_ends_with(char * string, char * with_what) {
    strrev(string);
    strrev(with_what);
    return st_starts_with(string, with_what);
}

typedef struct {
    const unsigned int size;
    char ** data;
} st_str_arr;

st_str_arr st_split(const char * string, const char delimiter) {
    const unsigned int string_length = strlen(string);
    if (string_length < 3) {
        const st_str_arr arr = { 0, NULL };
        return arr;
    }
    
    unsigned int ** indices = _allocate_memory(unsigned int **, string_length * sizeof(unsigned int *));
    unsigned int indices_length = 0;
    bool start_match = false;
    
    int current_start = -1;
    
    for (unsigned int i = 0; i < string_length; i++) {
        if (!start_match) {
            if (string[i] != delimiter) {
                start_match = true;
                
                if (string[i + 1] == delimiter) {
                    indices[indices_length] = _allocate_memory(unsigned int *, 2 * sizeof(unsigned int));
                    indices[indices_length][0] = i;
                    indices[indices_length][1] = i;
                    
                    indices_length++;
                } else
                    current_start = i;
            }
            
            continue;
        }
        
        if (i != (string_length - 1)) {
            if (string[i] == delimiter && string[i + 1] != delimiter)
                current_start = i + 1;
        
            else if (string[i] != delimiter && string[i + 1] == delimiter) {
                indices[indices_length] = _allocate_memory(unsigned int *, 2 * sizeof(unsigned int));
                indices[indices_length][0] = current_start == -1 ? i : (unsigned int)current_start;
                indices[indices_length][1] = i;
                indices_length++;
                
                current_start = -1;
            }
        
            continue;
        }
        
        if (current_start != -1) {
            indices[indices_length] = _allocate_memory(unsigned int *, 2 * sizeof(unsigned int));
            indices[indices_length][0] = (unsigned int)current_start;
            indices[indices_length][1] = string_length - 1;
            indices_length++;
        }
    }
    
    if (indices_length < 2) {
        _free_two_dim_arr(unsigned int, indices, indices_length);
        const st_str_arr arr = { 0, NULL };
        return arr;
    }
    
    st_str_arr arr = { indices_length };
    arr.data = _allocate_memory(char **, indices_length * sizeof(char *));
    
    for (unsigned int i = 0; i < indices_length; i++) {
        if (indices[i][0] == indices[i][1]) {
            arr.data[i] = _allocate_memory(char *, 2 * sizeof(char));
            arr.data[i][0] = string[indices[i][0]];
            arr.data[i][1] = '\0';
            continue;
        }
        
        arr.data[i] = _allocate_memory(char *, (indices[i][1] - indices[i][0] + 1) * sizeof(char));
        
        unsigned int k = 0;
        for (unsigned int j = indices[i][0]; j <= indices[i][1]; j++) {
            arr.data[i][k] = string[j];
            k++;
        }
        
        arr.data[i][k] = '\0';
    }
    
    _free_two_dim_arr(unsigned int, indices, indices_length);
    return arr;
}

st_str_arr st_to_chunks(const char * string, const unsigned int chunk_by) {
    const unsigned int string_length = strlen(string);
    if (chunk_by >= string_length) {
        const st_str_arr arr = { 0, NULL };
        return arr;
    }
    
    const unsigned int array_length = ceil((double)string_length / (double)chunk_by);
    st_str_arr output = { array_length };
    
    output.data = _allocate_memory(char **, array_length * sizeof(char *));
    
    unsigned int j = 0;
    for (unsigned int i = 0; i < array_length; i++) {
        // won't overload
        if ((j + chunk_by) <= string_length) {
            output.data[i] = _allocate_memory(char *, chunk_by * sizeof(char));
            output.data[i][chunk_by] = '\0';
            
            const unsigned int l = j + chunk_by;
            unsigned int k = 0;
            for (; j < l; j++) {
                output.data[i][k] = string[j];
                k++;
            }
            
            continue;
        }
        
        // will overload
        const unsigned int l = string_length - j;
        output.data[i] = _allocate_memory(char *, l * sizeof(char));
        output.data[i][l] = '\0';
    
        unsigned int k = 0;
        for (; j < string_length; j++) {
            output.data[i][k] = string[j];
            k++;
        }
    }
    
    return output;
}

char * st_strip(const char * string, const char strip_char) {
    if (string[0] == '\0')
        return NULL;
    
    const unsigned int length = strlen(string);
    unsigned int start = 0;
    unsigned int end = length - 1;
    
    for (unsigned int i = 0; i < length; i++)
        if (string[i] != strip_char) {
            start = i;
            break;
        }
    
    for (unsigned int i = length - 1; i != 0; i--)
        if (string[i] != strip_char) {
            end = i;
            break;
        }
    
    if (start == 0 && end == (length - 1))
        return NULL;
    
    char * ptr = _allocate_memory(char *, (end - start + 1) * sizeof(char));
    ptr[end] = '\0';
    
    unsigned int index = 0;
    for (unsigned int i = start; i < end; i++) {
        ptr[index] = string[i];
        index++;
    }
    
    return ptr;
}

char * st_substr(const char * string, unsigned int a, _opt_param(unsigned int b, 0)) {
    if (string[0] == '\0' || (a + b) >= strlen(string))
        return NULL;
    
    if (!b)
        b = strlen(string) - a;
    
    char * ptr = _allocate_memory(char *, b * sizeof(char));
    
    const unsigned int max = a + b;
    unsigned int i = 0;
    for (; a < max; a++) {
        ptr[i] = string[a];
        i++;
    }
    
    ptr[i] = '\0';
    return ptr;
}

char * st_get_content_no_flags(const unsigned int argc, char ** argv) {
    if (argc < 2 || (strlen(argv[0]) > 2 && argv[0][0] == '-' && argv[0][1] == '-'))
        return NULL;
    
    unsigned int * indices = _allocate_memory(unsigned int *, argc * sizeof(unsigned int));
    unsigned int indices_length = 0;
    unsigned int size = 0;
    
    for (unsigned int i = 1; i < argc; i++) {
        if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-')
            continue;
        
        indices[indices_length] = i;
        indices_length++;
        
        size += (strlen(argv[i]) + 1) * sizeof(char);
    }
    
    if (!size) {
        free(indices);
        return NULL;
    }
    
    char * ptr = _allocate_memory(char *, size);
    ptr[(size / sizeof(char)) - 1] = '\0';
    
    unsigned int index = 0;
    for (unsigned int s = 0; s < indices_length; s++) {
        for (unsigned int j = 0; j < strlen(argv[indices[s]]); j++) {
            ptr[index] = argv[indices[s]][j];
            index++;
        }
        
        if (s != (indices_length - 1)) {
            ptr[index] = ' ';
            index++;
        }
    }
    
    free(indices);
    return ptr;
}

char * st_get_content_no_options(const unsigned int argc, char ** argv) {
    if (argc < 2 || (strlen(argv[0]) > 2 && argv[0][0] == '-' && argv[0][1] == '-'))
        return NULL;
    
    unsigned int end = argc;
    unsigned int size = 0;
    for (unsigned int i = 1; i < argc; i++) {
        if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-') {
            end = i;
            break;
        }
        
        size += (strlen(argv[i]) + 1) * sizeof(char);
    }
    
    char * ptr = _allocate_memory(char *, size);
    ptr[(size / sizeof(char)) - 1] = '\0';
    
    unsigned int index = 0;
    for (unsigned int start = 1; start < end; start++) {
        for (unsigned int j = 0; j < strlen(argv[start]); j++) {
            ptr[index] = argv[start][j];
            index++;
        }
        
        if (start != (end - 1)) {
            ptr[index] = ' ';
            index++;
        }
    }
    
    return ptr;
}

typedef struct {
    char * value;
    const bool found;
    const bool has_value;
} st_flag_data;

st_flag_data st_flag_get_value(const unsigned int argc, char ** argv, const char * key) {
    if (!argc) {
        const st_flag_data output = { NULL, 0, 0 };
        return output;
    }

    char * key_ptr = _allocate_memory(char *, (2 + strlen(key)) * sizeof(char));
    memset(key_ptr, '-', 2 * sizeof(char));
    
    for (unsigned int i = 0; i < strlen(key); i++)
        key_ptr[i + 2] = key[i];
    key_ptr[strlen(key) + 2] = '\0';
    
    bool found = false;
    
    unsigned int start = 0;
    unsigned int end = argc;
    unsigned int size = 0;
    
    for (unsigned int i = 0; i < argc; i++) {
        if (!found && !strcmp(argv[i], key_ptr)) {
            start = i + 1;
            found = true;
            continue;
        }
        
        if (found) {
            if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-') {
                end = i;
                break;
            }
            
            size += (1 + strlen(argv[i])) * sizeof(char);
        }
    }
    
    st_flag_data output = { NULL, found, size != 0 };
    
    if (!found)
        return output;
    
    if (size) {
        output.value = _allocate_memory(char *, size);
        output.value[size / sizeof(char)] = '\0';
        
        unsigned int index = 0;
        for (; start != end; start++) {
            for (unsigned int j = 0; j < strlen(argv[start]); j++) {
                output.value[index] = argv[start][j];
                index++;
            }
            
            if (start != (end - 1)) {
                output.value[index] = ' ';
                index++;
            }
        }
    }
    
    return output;
}

char * st_shorten(const char * string, const unsigned int limit, _opt_param(const char * placeholder, NULL)) {
    if (string[0] == '\0' || !limit || strlen(string) <= limit)
        return NULL;
    
    const unsigned int placeholder_length = placeholder == NULL ? 3 : strlen(placeholder);
    char * ptr = _allocate_memory(char *, (1 + limit + placeholder_length) * sizeof(char));
    for (unsigned int i = 0; i < limit; i++)
        ptr[i] = string[i];
    
    if (placeholder != NULL) {
        for (unsigned int i = 0; i < placeholder_length; i++)
            ptr[placeholder_length + i] = placeholder[i];
    } else
        memset(ptr + limit, '.', 3 * sizeof(char));
    
    ptr[limit + placeholder_length] = '\0';
    return ptr;
}

// like strcat but you don't have to include a fixed string length
char * st_dynamic_concat(const unsigned int amount, ...) {    
    unsigned int bytes = 1 * sizeof(char);
    va_list vl1;
    va_start(vl1, amount);
    
    for (unsigned int i = 0; i < amount; i++) {
        const char * arg = va_arg(vl1, const char *);
        if (arg[0] == '\0')
            return NULL;
        bytes += strlen(arg) * sizeof(char);
    }
    
    va_end(vl1);
    
    char * ptr = _allocate_memory(char *, bytes);
    
    va_list vl2;
    va_start(vl2, amount);
    
    unsigned int index = 0;
    for (unsigned int i = 0; i < amount; i++) {
        const char * arg = va_arg(vl2, const char *);
        const unsigned int argl = strlen(arg);
        
        for (unsigned int j = index; j < index + argl; j++)
            ptr[j] = arg[j - index];
        index += argl;
    }
    
    va_end(vl2);
    ptr[index] = '\0';
    return ptr;
}

bool st_has_custom_emoji(char text[]) {
    if (strlen(text) < 23)
        return false;
    
    unsigned char s = 0; // status
    unsigned char nc = 0; // number count
    bool ia = false; // is animated
    
    for (unsigned int i = 0; i < strlen(text); i++) {
        if (!s && text[i] == '<')
            s++;
        else if (s == 1) {
            if (text[i] == 'a' && !ia) {
                ia = true;
                continue;
            } else if ((ia && text[i] == 'a') || text[i] != ':') return false;
            s++;
        } else if (s == 2) {
            if (st_is_alnum(text[i]))
                nc++;
            else {
                if (text[i] != ':' || nc < 2 || nc > 32)
                    return false;
                nc = 0;
                s++;
            }
        } else if (s == 3) {
            if (st_is_num(text[i])) 
                nc++;
            else
                return text[i] == '>' && nc > 16 && nc < 20;
        }
    }
    
    return false;
}

void st_proper_case(char text[]) {
    bool s = false;
    unsigned int i = 0;
    
    if (text[0] != ' ') {
        text[0] = toupper(text[0]);
        i++;
    }
    
    for (; i < strlen(text); i++) {
        if (text[i] == ' ') {
            s = true;
            continue;
        } else if (s) {
            text[i] = toupper(text[i]);
            s = false;
        } else
            text[i] = tolower(text[i]);
    }
}

void st_mock(char text[]) {
    for (unsigned int i = 0; i < strlen(text); i += 2)
        text[i] = toupper(text[i]);
}

void st_scramble(char text[]) {
    const unsigned int length = strlen(text);
    if (length == 1)
        return;
    
    for (unsigned int i = 0; i < length - 1; i++) {
        const unsigned int j = rand() % length;
        const char temp = text[j];
        text[j] = text[i];
        text[i] = temp;
    }
}

char * st_progress_bar(
    const double in_total, const double total,
    const char elapsed_char, const char progress_char,
    const char empty_char, const unsigned int bar_length
) {
    if (in_total < 0 || total < 1 || in_total > total || !bar_length)
        return NULL;
    
    const unsigned int available = floor((in_total / total) * bar_length);
    const unsigned int remaining_length = bar_length - (available + (available == bar_length ? 0 : 1));

    char * result = _allocate_memory(char *, (1 * sizeof(char)) + (available * sizeof(char)) + (remaining_length * sizeof(char)));
    result[sizeof(result) / sizeof(char)] = '\0';
    
    memset(result, elapsed_char, available * sizeof(char));
    
    if (remaining_length) {
        memset(result + available, progress_char, sizeof(char));
        memset(result + available + 1, empty_char, remaining_length * sizeof(char));
    }
    
    return result;
}

char * st_to_abbreviation(const char * text) {
    if (strlen(text) < 2)
        return NULL;
    
    char * result = _allocate_memory(char *, sizeof(text));
    bool s = false;
    unsigned int length = 0;
    
    if (text[0] != ' ') {
        result[0] = text[0];
        length++;
    }
    
    for (unsigned int i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            s = true;
            continue;
        } else if (s) {
            result[length] = text[i];
            length++;
        }
        
        s = false;
    }
    
    result[length] = '\0';
    return result;
}