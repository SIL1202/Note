#!/usr/bin/env python3
def foo(s: str, p: str) -> None:
    """This function apply KMP algorithm,

    in order to find all the repeated patterns in the text.
    """
    n, m = len(s), len(p)
    lps = [0] * m
    i, j = 1, 0
    while i < m:
        if p[i] == p[j]:
            j += 1
            lps[i] = j
            i += 1
        else:
            if j:
                j = lps[j - 1]
            else:
                lps[i] = 0
                i += 1
    i, j = 0, 0
    while i < n:
        if s[i] == p[j]:
            i += 1
            j += 1
            if j == m:
                print(i - j, end=" ")
                j = lps[j - 1]
        elif i < n and s[i] != p[j]:
            if j:
                j = lps[j - 1]
            else:
                i += 1


# documentation
print(foo.__annotations__)
print(foo.__doc__)

# apply KMP algorithm
text = "abcabcabcd"
pattern = "cab"
foo(s=text, p=pattern)
