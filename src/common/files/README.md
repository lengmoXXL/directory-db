# File library

```cpp
file::Path path("dir/a.txt");
InputFileStream stream(path);
stream << "abc\n" << 123;
stream.close();
```