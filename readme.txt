En (there is also a Russian version below)

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

