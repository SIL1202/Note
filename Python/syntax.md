### Numbers
1. Division (/) always returns a float. To do floor division and get an integer result you can use the // operator.
2. In interactive mode, the last printed expression is assigned to the variable _.

### Text

1. String literals can span multiple lines. One way is using triple-quotes: """...""" or '''...'''.

2. Strings can be concatenated (glued together) with the + operator, and repeated with *:

    ```python
    # 3 times 'un', followed by 'ium'
    3 * 'un' + 'ium'
    'unununium'
    ```

3. Two or more string literals (i.e. the ones enclosed between quotes) next to each other are automatically concatenated.

    ```python
    'Py' 'thon'
    'Python'
    ```

4. Indices may also be negative numbers, to start counting from the right:

    ```python
    word = 'Python'
    word[0]  # character in position 0
    'P'
    word[5]  # character in position 5
    'n'
    word[-1]  # last character
    'n'
    word[-2]  # second-last character
    'o'
    word[-6]
    'P'
    ```

5. In addition to indexing, *slicing* is also supported. While indexing is used to obtain individual characters, *slicing* allows you to obtain a substring:

    ```python
    word[0:3] # 3 (excluded)
    'pyt'
    ```

6. Note how the start is always included, and the end always excluded. This makes sure that `s[:i] + s[i:]` is always equal to `s`:

    ```python
    word[:2] + word[2:]
    'Python'
    word[:4] + word[4:]
    'Python'
    ```

7. Python strings cannot be changed — they are [immutable](https://docs.python.org/3/glossary.html#term-immutable). Therefore, assigning to an indexed position in the string results in an error:

    ```python
    word[0] = 'J'
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: 'str' object does not support item assignment
    word[2:] = 'py'
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: 'str' object does not support item assignment
    ```

8. The built-in function [`len()`](https://docs.python.org/3/library/functions.html#len) returns the length of a string:

    ```python
    s = 'supercalifragilisticexpialidocious'
    len(s)
    34
    ```

### List

1. 
