# Python wrapper Documentation
This library also has a python wrapper for it, install it here.
```bash
$ python3 setup.py build_ext --inplace
```

### Example
```py
import st

string = st.to_abbreviation("Hello, World!")
print(string)
# outputs "HW"
```

### Functions
> Please note that **NOT ALL** functions are included in this wrapper because they are easily coded in python.

| Function name      | Argument(s)         | Return type |
|--------------------|---------------------|-------------|
| `get_indexes`      | `str`, `str`        | `List[int]` |
| `has_custom_emoji` | `str`               | `bool`      |
| `mock`             | `str`               | `str`       |
| `proper_case`      | `str`               | `str`       |
| `scramble`         | `str`               | `str`       |
| `shorten`          | `str`, `int`, `str` | `str`       |
| `substr`           | `str`, `int`, `int` | `str`       |
| `to_abbreviation`  | `str`               | `str`       |
| `to_chunks`        | `str`               | `List[str]` |