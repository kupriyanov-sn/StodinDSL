En (there is also a Russian version below)

Stodin DSL (domain-specific language) is created as a tool for accelerating the development of C++ programs.
The full description in StodinDSL_en.odt (StodinDSL_en.html) file.  
Parts of documentation is below Russian section.

To work with the project, you need installed g ++ (MinGW), supporting C++ 14 and
gnu make build utility (Ubuntu, apt-get install build-essential).

Description of resources.
1. "compile" directory - the compiler and project sources for Code::Blocks.
    In the "Project \ Set programs' argumentssettings", you need to set the necessary paths
    (e.g. path to "stodin-test\main.stdn").
    Without an IDE, the compiler can be built using the "stodin-compiler" directory files.
2. "examples" directory - examples of programs in the Stodin language.
    Path changes in build scripts may be required.
3. "stodin-compiler" - compiler assembly files that do not require an IDE.
    Path changes in build scripts may be required.
4. "stodin-lib" directory - library files.
5. "stodin-test" directory - tests.
    Path changes in build scripts may be required.
6. "_cleanup.bat" - a script for cleaning object and executable files.
7. "StodinDSL.odt" - description of the language.
8. "StodinDSL.html" - description of the language.
9. "stodin_udl.xml" - Udl file with Stodin keywords for Notepad ++. 
    Python syntax also partially works with Stodin code.
    
---------------------------------------------------------------
Rus

Stodin DSL - предметно ориентированный язык программирования, создаваемый как средство ускорения написания программ на C++.

Для работы с проектом требуются установленные g++(MinGW), поддерживающие C++14 и
утилита сборки gnu make (Ubuntu, apt-get install build-essential).

Описание русурсов.
1. Директория compile - исходники компилятора и прокт для Code::Blocks. 
    В настройках прокта Project\Set programs' arguments необходимо установить необходимые пути
    (например, путь к stodin-test\main.stdn).
    Для вывода utf-8 в Linux, возможно, потребуется выбрать терминал
    (например, в Settings->Environment: lxterminal --title=$TITLE -e ).    
    Без IDE компилятор можно собрать при помощи файлов директории stodin-compiler.
2. Директория examples - примеры программ на языке Stodin. 
    Может потребоваться исменение путей в скриптах сборки.
3. Директория stodin-compiler - файлы сборки компилятора, не требующие IDE.
    Может потребоваться исменение путей в скриптах сборки.
4. Директория stodin-lib - файлы библиотеки.
5. Директория stodin-test - тесты.
    Может потребоваться исменение путей в скриптах сборки.
6. _cleanup.bat (sh) - скрипт очистки от объектных и исполнимых файлов.
7. StodinDSL.odt - описание языка.
8. StodinDSL.html - описание языка.
9. stodin_udl.xml - Udl-файл с ключевыми словами Stodin для Notepad++. Синтаксис Python тоже частично работает
    с кодом Stodin.
---------------------------------------------------------------
 1.Code example.

This chapter provides a math game code written in the Stodin DSL language to demonstrate the syntax.


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

Information for assembling this and other examples is given in chapter 13 (features of the compiler).

  
2.Stodin DSL features.

Stodin DSL has the following features:

    1.The language is simple and concise. At the same time, parsing the code is simple for both humans and software analyzers. 
    2.The language is statically typed. 
    3.Allows you to enable and disable additional features for debugging and improving reliability: detailed exception throwing (stack trace), detection of variable overflows (integer and floating point), detection of division by zero, etc. 
    4.The standard library is developed using Python or C # libraries as examples. 
    5.Stodin DSL is created as a tool for accelerating the development of C++ programs. Therefore, it interacts with C++ code: it is translated into it, uses its executable files, uses constructs that it cannot create itself because of its simplicity and conciseness. 

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
3.Syntax and semantics.

A quick look at the example in Chapter 1 suggests that the Stodin syntax is close to the Python syntax. In fact, only the indented system is common to these languages  (indentation is always 4 spaces in Stodin, unlike Python), as well as some keywords. The main differences from most modern languages (except for those mentioned in chapter 1) are as follows:

1. Functions do not have return values. Instead, references are used.
2. The function arguments use only constant and mutable references.
3. Use chains of functions that modify data.
4. Assigning variables changes the value, not the references.
5. There are no hidden variables (due to the lack of brackets and priorities).

The most interesting is the chain syntax that allows you to write code like:

person @wake_up @put_on coat; hat @go_to nearest shoop @buy apples; eggs; bread

Here the functions (starting with the @ symbol) sequentially perform operations on the variable person. In other languages, this code might look like this:

person.wake_up()
person.put_on(coat)
person.put_on(hat)
person.go_to(nearest, shoop)
person.buy(apples)
person.buy(eggs)
person.buy(bread) 

In this case, the code ratio in characters is 133/79 = 1.68, and readability even increases. In other languages, a close effect can be achieved if an object reference is returned in each method. But in this case, the purchase of products (apples; eggs; bread) will still require three times to write "buy". In addition, in Stodin, this technique also applies to operators: 

a + b c d 

In this case, variables b, c, d are successively added to the variable a.

The sequence of calculating operators is similar to working with a calculator: first a variable is set, then an operator, then a chain of immutable variables. The equivalent of the expression above in C++ code would be:

a += b; a += c; a += d; 

For comparison operators, additional tools are required so that the next link does not block the effect of the previous one:

res > u1 u2 ? u2 u3 ? u3 u4

Here, the results of the comparison are sequentially placed in the res variable until they are true.

res == u1 56 !? u2 26 !? u3 10 !? u4 5

Here, the results of the comparison are sequentially placed in the res variable until they are correct. This form is also acceptable:

res? == u3 3

Here the expression will be evaluated if the res variable is true.
In practice, chains are not used very often, usually in arithmetic expressions or in functions like @print. 