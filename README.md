# dictle
dictle is a dictionary written in c inspired by python.

# Documentation
# Examples
* Persons
```c
#include <stdio.h>
#include <dictle/dictionary.h>

int main() {
	dict_t* person = dict_create(STRING, STRING, "Name", "John");
	dict_append(&person, STRING, INTEGER, "Age", 50);
	dict_print(person);

}
```
# Todo
* Infinite recursion
* Implement floating point parsing for string to dictionary

# Upcoming features
* Note: more features coming soon
