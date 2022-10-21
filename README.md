# Empowered Enum

![Alla pugna!](https://img.shields.io/badge/ALLA-PUGNA-F70808?style=for-the-badge)

`eenum` is a utility macro that automatically builds metadata for an enum definition.

This library requires C++20.

A nix development environment is defined to easily run unit tests:

```bash
$ nix develop
$ build
```

With meson, ninja and a C++20 capable compiler it is also possible to:

```bash
$ meson build
$ ninja -C build test
```

To use the library it is enough to include both the hpp files in `src/` folder.

## eenum definition

To define an empowered enum, the macro `eenum` must be called.

Its signatures is:
```cpp
eenum(name, underlying type, values ...)
```

For example:


```cpp
eenum(test, unsigned, TEST1 = 5, TEST2, TEST3 = 42)
```

Will define an enum called `test` that inherits from `unsigned`. It is equivalent to:

```cpp
enum class test: unsigned
{
    TEST1 = 5,
    TEST2
    TEST3 = 42
};
```

The generated eenum can be used just like a normal enum class:

```cpp
test t = test::TEST1;

switch(t)
{
    case (test::TEST1): ...
    case (test::TEST2): ...
} // compiler warning: TEST3 unhandled
```

And it will be able to:

```cpp
t = "TEST2"; //equivalent to t = test::TEST2

std::string t_string = t; //"TEST1"
t_string = t.to_string()l //"TEST1"
```

Casts to and from strings are `constexpr`, but at runtime will cost respectively `O(log(n))` and `O(n)`, where `n` is the number of values.