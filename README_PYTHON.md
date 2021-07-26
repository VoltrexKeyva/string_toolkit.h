# string-toolkit Documentation.
You can install from pip with:
```bash
$ python3 -m pip install string-toolkit
```
or build directly from source with:
```bash
$ git clone https://github.com/vierofernando/string_toolkit.h.git
$ cd string_toolkit.h/
$ python3 setup.py build_ext --inplace
```

### Example
```py
>>> import st
>>> st.to_abbreviation("Hello, World!")
```

### Trying with more functions
```py
>>> st.get_indexes("Hello, World!", "l")
[2, 3, 10]
>>>
>>> st.has_custom_emoji("Hello!")
False
>>> st.has_custom_emoji("Hello, <:hello:69696969696969696>!")
True
>>>
>>> st.mock("Hello, World!")
'HeLlO, WOrLd!'
>>>
>>> st.proper_case("HeLlO, WOrLd!")
'Hello, World!'
>>>
>>> st.scramble("Hello, World!")
'd,ll relooHW!'
>>>
>>> st.shorten("Hello, World!", 5, "...")
'Hello...'
>>>
>>> st.substr("Hello, World!", 7, 5)
'World'
>>>
>>> st.progress_bar(50, 100, "=", "@", ".", 30)
'===============@..............'
>>>
>>> st.to_chunks("Hello, World!", 5)
['Hello', ', Wor', 'ld!']
```