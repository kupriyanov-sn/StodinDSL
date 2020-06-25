# Stodin DSL

This document was originally written in Russian. Translated automatically. 

Table of contents

 1. Code example.
 2. Stodin DSL features.
 3. Syntax and semantics.
 4. Variables and standard types.
 5. Functions.
 6. Branch operators.
 7. Loops.
 8. Constants and Enumerations (enum).
 9. Structures.
 10. Standard containers.
 11. Exceptions and Asserts.
 12. Modules.
 13. Features of the compiler (translator).
 14. Standard library.
 15. Development.

## 1. Code example.

This chapter provides a math game code written in the Stodin DSL language to demonstrate the syntax.

```python
import random
import time

def get_multi_question
    mref a:int b:int answer:int 
    *v @array|int
    for a in 12; 99; 1
        *c @int a % 10
        if != c 0
            v @add a
    a @random:choice v
    b @random:randint 3 9
    answer = a * b

def math_round
    mref res:bool
    *tAllStart @int @time:time
    *counter @int 0
    for
        *tStart @int @time:time
        *a; *b; *answer @int 0
        a b answer @get_multi_question
        *strAnswer @string @to_string answer
        @print* a " * " b "\n"
        *strRes @string @getline
        if strRes "q"
            res = false
            return
        if strRes strAnswer
            @print "True\n"
            counter + 1
        else
            @print* "False! Correct answer is: " answer "\n"
        *tEnd @int @time:time - tStart
        @print* "t = " tEnd "\n"
        if counter 6
            break
    *tAllEnd @int @time:time - tAllStart
    *speed @double tAllEnd$double / counter
    @print* "speed: " speed "\nEnter to proceed or q to quit: \n"
    *key @string @getline
    res != key "q"

def main
    @print "\nInput an answer or q to quit: \n"
    for *b @bool in b @math_round
        for 0
```

Information for assembling this and other examples is given in chapter 13 (features of the compiler).  

## 2. Stodin DSL features.

Stodin DSL has the following features: 
1. The language is simple and concise. At the same time, parsing the code is simple for both humans and software analyzers.
2. The language is statically typed.
3. Allows you to enable and disable additional features for debugging and improving reliability: detailed exception throwing (stack trace), detection of variable overflows (integer and floating point), detection of division by zero, etc.
4. The standard library is developed using Python or C # libraries as examples.
5. Stodin DSL is created as a tool for accelerating the development of C++ programs. Therefore, it interacts with C++ code: it is translated into it, uses its executable files, uses constructs that it cannot create itself because of its simplicity and conciseness.

Although Stodin can in many cases replace a general-purpose language, it is closer to domain-specific languages (DSL) for the following reasons:

1. The features used in DSL: chain syntax, the absence of blocks of code allocated by parentheses, translation into another programming language.
2. Stodin has a number of restrictions introduced for simplicity, conciseness, and to reduce the necessity of frequent syntax changes:
2.1. The language has no priority system.
2.2. The language is completely free of brackets: round, square, curly, angular, as well as words that replace them (begin, end).
2.3. Stodin DSL does not have metaprogramming capabilities. Including there is no possibility of developing templates in the C++ style, although customization of the type of templates from libraries is available.
2.4. There are no features for functional programming.
2.5. There is no way to create custom classes with inheritance, encapsulation and polymorphism, although you can use classes from libraries.
2.6. There is no special unsafe mode. Instead, it uses the connection of files with C++ code.
2.7. No memory management required. The care of allocating and freeing memory is passed on to libraries.

Stodin's limitations allowed him to come nearer to laconicism in the Python language, despite the presence of static typing. If on relatively small programs the Stodin code is more than Python code by characters (about 1.5 times), then on medium and large programs it can become even. Python achieves conciseness through ingenious constructs that are very difficult to distribute throughout the code. Stodin simply saves on brackets and uses chain syntax, as a result of which a comparable conciseness is achieved without additional labor costs.
 3. Syntax and semantics.
A quick look at the example in Chapter 1 suggests that the Stodin syntax is close to the Python syntax. In fact, only the indented system is common to these languages  (indentation is always 4 spaces in Stodin, unlike Python), as well as some keywords. The main differences from most modern languages (except for those mentioned in chapter 1) are as follows:

1. Functions do not have return values. Instead, references are used.
2. The function arguments use only constant and mutable references.
3. Use chains of functions that modify data.
4. Assigning variables changes the value, not the references.
5. There are no hidden variables (due to the lack of brackets and priorities).

The most interesting is the chain syntax that allows you to write code like: 
```
person @wake_up @put_on coat; hat @go_to nearest shoop @buy apples; eggs; bread
```
Here the functions (starting with the @ symbol) sequentially perform operations on the variable person. In other languages, this code might look like this: 
```python
person.wake_up()
person.put_on(coat)
person.put_on(hat) 
person.go_to(nearest, shoop)
person.buy(apples)
person.buy(eggs)
person.buy(bread)
```
In this case, the code ratio in characters is 133/79 = 1.68, and readability even increases. In other languages, a close effect can be achieved if an object reference is returned in each method. But in this case, the purchase of products (apples; eggs; bread) will still require three times to write "buy". In addition, in Stodin, this technique also applies to operators: 
```
a + b c d
```
In this case, variables b, c, d are successively added to the variable a.

The sequence of calculating operators is similar to working with a calculator: first a variable is set, then an operator, then a chain of immutable variables. The equivalent of the expression above in C++ code would be: 
```c++
a += b; a += c; a += d;
```
For comparison operators, additional tools are required so that the next link does not block the effect of the previous one: 
```
res > u1 u2 ? u2 u3 ? u3 u4
```
Here, the results of the comparison are sequentially placed in the res variable until they are true. 
```
res == u1 56 !? u2 26 !? u3 10 !? u4 5
```
Here, the results of the comparison are sequentially placed in the res variable until they are correct. This form is also acceptable: 
```
res? == u3 3
```
Here the expression will be evaluated if the res variable is true.

In practice, chains are not used very often, usually in arithmetic expressions or in functions like @print. 
 4. Variables and standard types.
Creation of a variable is marked with *, and then its type and value follow: 
```
*a @int 5
```
Creating a variable can be combined with a chained one: 
``` 
*sz @int @size arr + 15
```
At the time of writing, there is no type inference (except for traversing array elements in a loop). It is not very difficult to implement it, but there is no certainty that this will not complicate the work of code analyzers.

Variables in Stodin code (unlike constants) can only be created inside functions. If a global variable is required for some external library in C or C++, it is recommended to create one in this library.

Standard types that do not require connecting modules are shown in the table below: 

|Stodin type |     C++ type    |            Comment              |
| ---------- |:---------------:| -------------------------------:|
| uint       | uint64_t        |                                 |
| int        | int64_t         |                                 |
| u64        | uint64_t        |                                 |
| i64        | int64_t         |                                 |
| u8         | uint8_t         |                                 |
| i8         | int8_t          |                                 |
| u16        | uint16_t        |                                 |
| i16        | int16_t         |                                 |
| u32        | uint32_t        |                                 |
| i32        | int32_t         |                                 |
| double     | double          |                                 |
| float      | float           |                                 |
| ldouble    | long double     |                                 |
| string     | __stodin_string | Wrapper class for std::string   |
| bool       | bool            |                                 |
| array      | __stodin_array  | Wrapper class for std::vector   |
| dict       | __stodin_dict   | Wrapper class for std::map      |
| file       | __stodin_file   | Wrapper class for std::iostream |

Wrapper classes are needed to convert return values to references.
Type conversion is done using the $ sign: 

```python
*u3 @int 10
*d @double u3$double / 3.3
res @math:float_compare d 3.03 0.01
u3 = d$int
res? == u3 3
```

## 5. Functions.
The function header is generally written in three lines, using the keywords: def, mref, cref. After def is the name of the function, after mref is a list of links to mutable variables (accumulators) with types, after cref, constant links with types. When using the function, batteries are written on the left of the header, constant links on the right. For example: 

```python
def double_add
    mref a:int b:int
    cref c:int
    a + c
    b + c

a b @double_add c
```
The application of functions is given in chapters 1, 3. In addition, there are additional features:
1. If the function accepts one constant parameter, then you can mark it with an asterisk so as not to write a character; after each argument, for example: 
```
a b @double_add* c d e f
@print* a b c "\n"
```
2. As for comparison operators, the separator “?” Can be used in function chains or "!?".
3. To create encapsulated functions, just underline the heading:  def _double_add
Encapsulated functions should be placed above their place of use. Open functions can be located everywhere. 

## 6. Branch operators.

The following keywords are used for branching: if, ifnot, elif, else. In the simplest case, the code with branch operators will look like: 

```python
if someVar
    @do_something_1
elif anotherVar
    @do_something_2
else
    @do_something_3
```
Since the values from the functions are not returned, but created, there are some features of the application of these operators. An arbitrary expression cannot be used in a branch operator. Instead, there are 6 intuitive forms: 

```python
if a # with ifnot
if a b # without ifnot
if > a b # without ifnot
if a in b c d # with ifnot
if a in someArray # with ifnot
if *a @bool in a @some_func b c # with ifnot
```
The use of chain expressions could be implemented using external variables, or using a lambda with closure. But the use of chains complicates the analysis of the code when creating tests, since the tests must go through all branches.

The ifnot operator was required to change the estimate of the operator variable to inverted. For the last three forms of the if statement, this is difficult to do by simply inverting the variable a.  
## 7. Loops.
Stodin has only one statement for loops that has a set of options:

```python
for
for 0
for 1
for n
for *i in 10;0;-1   
for *i @uint in 10;0;-1   
for *a in v
for *a in b c d
for *b @bool in b @some_func c
```

`for` without parameters sets an infinite loop .
`for 0` is an empty statement.
`for 1` defines a block of code that can have its own local variables.
`for n` sets the loop executing n times .
`for *i in begin;end;step`  defines a loop in which variable "i" changes from variable (constant) "begin" to variable (constant) "end" with step "step".
`for *i @uint in 0;10;1` defines a cycle in which the variable "i" of a given type changes from the variable (constant) "begin" to the variable (constant) "end" with the step "step". 
`for *a in v` defines a cycle in which the variable a changes in accordance with the values of the array v.
`for *a in b c d`  defines a loop in which the variable a goes around the list of variables. 
`for *b @bool in b @some_func c` sets the loop that runs while the variable b is true. The value of the variable is determined by the @some_func function .

## 8. Constants and Enumerations (enum).
Declarations of constants are given below:

```
const CNST_1 @int 5
const VCNST @array|int 4 8 14
const _CNST_2 @int 15
```
The declaration of constants begins with the const keyword, then comes the name of the constant, the type of constant, initializing the value (or a list of values). A constant can be a simple type, a string type, an array. The underscore in the first character makes the constant local in the current module.
Announcement listings are listed below: 

```
enum symbols @u8 A=5 B C D
enum _symbols2 @u8 A B C D
```
The declaration of enumerations begins with the keyword enum, then comes the name of the enumerations, the type of enumeration, a list of enumeration names. An enumeration type can only be an integer value. The underscore in the first character makes the enumeration local in the current module. An example of using the enumeration is given below:

```
*enumD @symbols symbols^D
res == enumD symbols^D
res == enumD$int 8
```

## 9. Structures

Examples of structures are given below:

```python
struct OpenStruct
    *i1 @int 1
    *s2 @string "2"
    *arr @array|string "3" "4"

struct _StaticStruct
    *s1 @string "static"
```
Structures in Stodin do not have functions; they are used only for data storage. When creating fields, structures are initialized with the values specified in the structure description. In addition, structures that do not have nested structures and containers (except string) can be initialized with a list of values at the stage of creating a variable:

```python
struct OpenStruct2
    *s1 @string "1"
    *s2 @string "1"
    *s3 @string "1"
    *s4 @string "1"

*os2 @OpenStruct2 "6" "7" "8" "9"
```

A structure whose type begins to underline is available only in the module in which it is declared. 

## 10. Standard containers.

Stodin has three standard containers that do not require plug-ins: string, array, and dictionary.
An array is created as follows :
`*v @array|uint 1 2 4`
Here, the name of the array consists of at least two parts, separated by the symbol |. The name is followed by an initialization list specifying the number and value of array elements.
An appeal to an array element can be as follows:
`v|0 + 5`
Here, the number 5 is added to the zero element of the array.
An array can have a more complex structure: 
`*aIntInt @array|array|int @resize 3 `
This is an array of arrays. It cannot be initialized with simple values at creation. Only a list of already created arrays. You can set its size using the @resize function. In addition, you can fill in an array of arrays (just like an array) as follows:
`aIntInt|* = 4 5 6 `
This construct creates a new array element using a list of values. If we continue this expression with a chain of functions, then it will change this last element of the array.
Dictionaries are created like this: 
`*m @dict|uint,string @add 1 "1" ; 2 "2" ; 3 "3"`

That is, after the sign | it is required to specify a pair of types for the key-value, separated by commas without spaces. A dictionary cannot be initialized with simple values at creation. Therefore, in the above example, the @add function is used.
You can access a dictionary element as well as an array element. You can get around the elements of the dictionary that we created above: 

```python
for *b in m
    *s @string @to_string b.first     
    res? == s b.second
```
You can fill out the dictionary in the following way:

```python
*tests @dict|string,bool
tests|*"array test" @test_array
tests|*"bitwise operators test" @test_bitwise_operators
tests|*"bool test" @test_bool
```
For a dictionary, this way of filling is important, because in Stodin a dictionary element is not automatically created when a key is accessed that is not in the dictionary (as implemented in C++, C #, Python). If we apply for a key that is not in the dictionary without using the * character, an exception will be thrown. This prevents accidental creation of a new element.
You can use dictionary dictionaries:

```python
*ssDict @dict|string,dict|string,int
*sDict @dict|string,int @add "1" 1; "2" 2; "3" 3
ssDict @add "01" sDict; "02" sDict; "03" sDict
ssDict|*"04" @add "4" 4
ssDict|"04"|*"5" = 5
```
Dictionary dictionary has a difficult to read type. To simplify, you can use the typedef operator:
typedef dict|string,int dctStr
`*ssDict @dict|string,dctStr`

Using a string in Stodin is almost the same as using std::string. The only difference is that in Stodin there are no separate quotes for the character. Each double-quoted single-character literal is converted to a character during translation.
Strings consist of bytes, have utf-8 encoding (depends on the editor). Accordingly, a certain letter may contain an indefinite number of bytes. So far, funds have not been provided for convenient work with characters included in alphabets such as Cyrillic.
All methods for working with a string, an array, a dictionary in wrapper classes, in a library written in C++, are taken out in friend functions, so that chains can be used. 

## 11. Exceptions and Asserts.

An example of using exceptions is given below:

```python
*arr @array|int 1 2 3 4
try
    arr|12 = 3
catch out_of_range e
    @print* e "\n"
res = false
try
    throw domain_error "test domain_error"
catch domain_error e
    @print* e "\n"
try
    assert > 1 2
catch logic_error e
    @print* e "\n"
```
That is, three traditionally used keywords are used: try, catch, throw, and exception types from the C++ exception library. In addition, assert is used as a way to throw an exception of type logic_error when a certain condition is met. The assert format corresponds to the if format (without ifnot).
Unlike C++ code, Stodin always throws an exception when it goes beyond the boundaries of a standard array, string, or dictionary.
By default, Stodin does not throw exceptions when dividing by zero or overflow. To enable the mode when such exceptions are generated, you need to use the -safe switch.
By default, Stodin does not display verbose exceptions (stack trace). To enable this mode, use the -trace flag. This mode has some limitations: exceptions are not caught in the place where the variable was created and in statements such as if and for. Accordingly, they will be intercepted just above the place where the error occurred (in a function that uses a function with no exception caught). 

## 12. Modules.

Modules in Stodin are divided into local and library. Local ones are divided into modules written in Stodin and modules written in C++. Library modules are all C++ code, even if they were originally written in Stodin and then translated into C++ code. Each module contains a unique namespace associated with the module file name.
Connection of modules has the form:
```python
import time
import math
import ^ math
import ^ structs
import ^cpp local_test
```
To connect the library module, use the import keyword and the module name following it. A local module written in Stodin requires the ^ sign in front of the module name. When connecting a local module that represents a file with C++ code, it requires the ^cpp prefix before the module name. When using local modules of both types, the ^ character is required before the module name:
```
game.hinter @^hinter:set_word wordPair.answer
game.scorer @^scorer:update_time
```
Here ^hinter and ^scorer are the names of the modules, set_word and update_time are functions from the modules. For library modules, the ^ sign is not required. This separation is based on experience with Python modules, in which there may be conflicts associated with the coincidence of the names of local and library modules. 

A local module written in C++ can consist of a single header file, or a header and executable file. The code of such modules should be in the namespace, starting with the _stodin_module_ prefix, followed by the file name without the extension. The code example of such a module is given below:
```c++
#ifndef _STODIN_MODULE_LOCAL_TEST_H
#define _STODIN_MODULE_LOCAL_TEST_H

#include <iostream>

namespace _stodin_module_local_test
{
    inline void test(bool & res){res = true;}
}

#endif // _STODIN_MODULE_LOCAL_TEST_H
```
When creating classes in modules written in C++, all class methods must be rendered in friend functions. 

## 13. Features of the compiler (translator).

The compiler does not require any project file. Instead, it sequentially connects the modules specified in the modules that it has already connected, starting from the main local module, whose name is passed to the compiler.
All translated files are placed in the “stodin-out” directory, which is created in the directory where the main module is located. It also contains all the necessary library files and an automatically created make-file. Then, using the make-file, an executable file is created, which is placed next to the main module and has its name.

The compiler has flags:

-run : run compiled file.
-r  : recompile the whole project. 
-trace : verbose exception output (stack trace).
-safe : overflow detection of variables.
Thus, the call to the compiler can take the form :
	compile_file_path main.stdn -r -trace -safe -run
where compile_file_path - path to the compiler file;
      main is the name of the main module. 

For the Stodin compiler to work correctly, the following must be installed on the computer:
1. C++ compiler (g ++ or MinGW) supporting C++14.
2. Make utility (gcc-make, mingw32-make).
3. The standard Stodin library (comes with a compiler).

The paths to the compiler, collector and directories must be specified in the config.cfg file, which is located next to the compiler executable file. An example of the settings for this file is given below: 
COMPILER_PATHS=.;C:\MinGW\bin;C:\MinGW;
CC="C:\MinGW\bin\g++.exe"
MAKE="C:\MinGW\bin\mingw32-make.exe"
LIB=D:\stodin\stodin-lib\

Description of these settings:
"COMPILER_PATHS" – are paths required for the C++ compiler.
"CC" - is the path to the C++ compiler.
"MAKE" – is the path to the collector.
"LIB" - is the path to the standard Stodin library. 

## 14. Standard library.

A detailed description of the standard library will be made in a separate document. At the time of writing this documentation, the following standard library modules are being developed that require import:
fileinfo - functions for working with files and directories.
math - mathematical functions.
random - functions for random number generator, random selection, mixing.
time - functions for determining the time.
exstr - additional functions for working with a string.

Also, many functions are implemented in modules that do not require import:
array - work with arrays.
common - various functions, for example, working with main arguments.
dict - work with dictionaries.
file - work with files.
io - work with input and output.
safe - safe mathematical operators (for -safe mode).
string - work with a string. 

## 15. Development.

No significant syntax changes are currently planned. The only thing that is clearly needed at this point is the implementation of the syntax for connecting module packages and compiled libraries (dll or so). In addition, some additional syntax may be required if work with streams is implemented.
For further development, the following developments are required:
1. Adding modules to the standard library (and adding existing ones).
2. Creation of code analyzers.
3. Development of projects in the Stodin language.

Perhaps the following will be added to the standard Stodin library:
1. The module for working with strings consisting of graphemes, with index access to the grapheme, and to the byte. Such lines would be convenient when processing non-English text.
2. Modules for processing text data files, such as json or xml.
3. Image processing module. Perhaps interaction with OpenCV is suitable here.
4. A module for displaying graphics. Perhaps interaction with SDL is suitable here.
5. A module for working with input-output ports, such as RS-232 or USB HID.

Modules for working with a network, with a GUI, with databases, data encryption, etc. are not planned to be developed yet due to the author’s limited capabilities.
Code analyzers can be used, for example, to generate the optimal number of tests based on the calculation of branching operators and analysis of the use of side effects. 
