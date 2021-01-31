#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <iterator>

#include "parser.h"
#include "auxiliary.h"
#include "parser_error.h"

using namespace std;
using namespace auxiliary;

struct Config
{
    string compilerPaths;
    string compiler;
    string makeTool;
    string libPath;
    string sdlLibPath;
    string sdlIncPath;
};
static Config cfg;

bool load_config(string fileName)
{
    size_t pos = fileName.rfind('\\');
    if(pos == string::npos) pos = fileName.rfind('/');
    if(pos != string::npos)
    {
        string dirPath = fileName.substr(0, pos + 1);
        ifstream configFile;
        configFile.open(dirPath + "config.cfg");
        string line;
        while(getline(configFile, line))
        {
            pos = line.find('=');
            if(pos != string::npos)
            {
                if(line.back() == '\r')
                    line.erase(line.size() - 1);
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1, line.size());
                //cout << "key: " << key << "; value: " << endl << value << endl;
                if(key == "COMPILER_PATHS") cfg.compilerPaths = value;
                else if(key == "CC") cfg.compiler = value;
                else if(key == "MAKE") cfg.makeTool = value;
                else if(key == "LIB") cfg.libPath = value;
                else if(key == "SDL_LIB") cfg.sdlLibPath = value;
                else if(key == "SDL_INC") cfg.sdlIncPath = value;
            }
        }
        configFile.close();
        return true;
    }
    return false;
}

string get_begin_lines(const string &header)
{
    return "#include \"_stodin_module_" + header +".h\"\n\
namespace _stodin_module_" + header + "{\n";
}

void do_main_file(string outPath, string mainFile)
{
    ofstream dest;
    dest.open(join(outPath, "main.cpp"));
    dest <<
"#include <iostream>\n\
#include <exception>\n\
#include \"__stodin_common.h\"\n\
#include \"_stodin_module_" + mainFile + ".h\"\n\
using namespace _stodin_module_" + mainFile + ";\n\
int main(int argc, char** argv){\n\
    try\n\
    {\n\
        _stodin_parse_args(argc, argv);\n\
        _stodin_main();\n\
    }\n\
    catch(std::exception& e)\n\
    {\n\
        if(__stodinTrace.size())\n\
        {\n\
            for(auto s: __stodinTrace)\n\
                std::cout << s << std::endl;\n\
        }\n\
        else\n\
            std::cout << e.what() << std::endl;\n\
    }\n\
    return 0; \n\
}\n";
    dest.close();
}



void copy_lib_to_output(string outPath, string fileName)
{
    cpp11_copy_file(join(cfg.libPath, fileName),
                    join(outPath, fileName));

}

static bool _get_long_line(ifstream & source, string &line)
{
    line = "";
    if(getline(source, line))
    {
        while(line.size() && ((line.back() == '\n') || ((line.back() == '\r'))) )
            line.pop_back();
        while(line.size() && (line.back() == '\\') && (line.find('#') == string::npos))
        {
            line.pop_back();
            string s;
            if(getline(source, s))
                line += s;
            else
                break;
        }
        return true;
    }
    else
        return false;
}

bool create_module(const string &name, const string & inPath, const string & outPath, const vector<string> & flags)
{
    bool res = true;
    string makeFilePath = join(outPath, "Makefile");
    string sourcePath = join(inPath, name + ".stdn");
    string destPath = join(outPath, "_stodin_module_" + name + ".cpp");
    bool updateFlag = (std::find(flags.begin(), flags.end(), string("-r")) != flags.end());
    if(!updateFlag) updateFlag = get_last_modification_time(destPath) < get_last_modification_time(sourcePath);

    ifstream source;
    source.open(sourcePath);
    ofstream dest;
    if(updateFlag)
        dest.open(destPath);
    string line;
    string outLine;
    if(updateFlag)
        dest << get_begin_lines(name);
    int counter = 1;
    while(_get_long_line(source, line))
    {
        parser_error::set_line(name, counter);
        if(parser::parse(line, outLine, flags))
        {
            if(outLine.size())
            {
                outLine += "   // " + to_string(counter) + "\n";
                if(updateFlag)
                    dest.write(outLine.c_str(), outLine.size());
            }
        }
        else
            res = false;
        counter++;
    }
    if(parser::parse(".", outLine, flags))
    {
        outLine += "\n";
        if(updateFlag)
            dest.write(outLine.c_str(), outLine.size());
    }
    if(updateFlag)
        dest << "}";
    source.close();
    if(updateFlag)
    {
        dest.close();
        dest.open(join(outPath, "_stodin_module_" + name + ".h"));
    string upHeader = name;
    std::transform(upHeader.begin(), upHeader.end(), upHeader.begin(), [](unsigned char c){ return std::toupper(c); });
        dest << "#ifndef _STODIN_" + upHeader + "_INCLUDED\n\
#define _STODIN_" + upHeader + "_INCLUDED\n\
#include <cstdint>\n\
#include <exception>\n\
#include \"__stodin_types.h\"\n\
#include \"__stodin_string.h\"\n\
#include \"__stodin_array.h\"\n\
#include \"__stodin_dict.h\"\n\
#include \"__stodin_io.h\"\n\
#include \"__stodin_file.h\"\n\
#include \"__stodin_common.h\"\n";
        bool safeFlag = std::find(flags.begin(), flags.end(), string("-safe")) != flags.end();
        if(safeFlag)
            dest << "#include \"__stodin_safe.h\"\n";
        dest << "using namespace std;\n";

        dest << parser::get_module_headers();
        dest << "namespace _stodin_module_" + name + "{\n";
        dest << parser::get_func_lines();
        dest << "}\n#endif\n";
        dest.close();
    }
    return res;
}

string get_sdl_string(const vector<string> &modules, string & sdlInc, string & sdlLib)
{
    if(modules.size())
    {
        for(string module: modules)
        {
            if(module.find("sdl") == 0)
            {
                sdlInc = cfg.sdlIncPath;
                sdlLib = cfg.sdlLibPath;
                return " -lmingw32 -lSDL2main -lSDL2 -mwindows  -Wl,--no-undefined -Wl,--dynamicbase -Wl,--nxcompat -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid ";
            }
        }
    }
    return "";
}

void create_makefile(const vector<string> &modules, const vector<string> &libObjectModules, const vector<string> &cppObjectModules,
    const string & inPath, const string & outPath, string mainFile)
{
    string exeFile = join(string(".."), mainFile + ".exe");
#ifdef _WIN32
    string shellStr = "\nSHELL = cmd.exe";
#else
    string shellStr = "";
#endif // _WIN32

    string sdlInc = "";
    string sdlLib = "";
    string sdlFlags = get_sdl_string(modules, sdlInc, sdlLib);

    // https://www.gnu.org/software/make/manual/html_node/Goals.html
    // https://stackoverflow.com/questions/7353426/automatic-header-dependencies-with-gmake
    // https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html
    ofstream dest;
    dest.open(join(outPath, "Makefile"));
    string compilerPaths = "";
    if(cfg.compilerPaths.size() > 1)
        compilerPaths = string("PATH=") + cfg.compilerPaths;
    if(sdlInc.size())
        dest << "INCLUDE_PATHS=-I\"" << sdlInc << "\"\n";

    dest << compilerPaths + shellStr + "\n\
CC=" + cfg.compiler + "\n\
CFLAGS= -std=c++14 -Wall -fexceptions -c \n\
LFLAGS= " + sdlFlags + "-static-libstdc++ -static-libgcc -static -s\n";
    if(sdlLib.size())
        dest << "LIBS=-L\"" + sdlLib << "\"\n";
    string s = "OBJECTS= ";
    if(modules.size())
    {
        for(string module: modules)
            s += "_stodin_module_" + module + ".o ";
        s += "\\\n";
    }
    if(libObjectModules.size())
    {
        for(string module: libObjectModules)
            s += module + " ";
        s += "\\\n";
    }
    if(cppObjectModules.size())
    {
        for(string module: cppObjectModules)
            s += module + " ";
        s += "\\\n";
    }
    s += "__stodin_string.o ";
    s += "__stodin_io.o ";
    s += "__stodin_file.o ";
    s += "__stodin_common.o ";
    s += "main.o\n";
    dest << s;
    dest << "all: project\n\
project: $(OBJECTS)\n\
\t$(CC) $(INCLUDE_PATHS) $(LFLAGS) $(LIBS) $(OBJECTS) -o " + exeFile + "\n\
%.o:  %.cpp \n\
\t$(CC) $(CFLAGS) $(INCLUDE_PATHS) -MD -MP -MF ${@:.o=.d} $< \n\
DEPS = $(OBJECTS:.o=.d)\n\
ifneq ($(MAKECMDGOALS),clean)\n\
-include $(DEPS)\n\
endif\n\
clean:\n\
\tdel *.out\n\
.PHONY : clean\n";
    dest.close();
}

int main(int argc, char** argv)
{
    try
    {
        if(!load_config(string(argv[0])))
        {
            cout << "config error!" << endl;
            return -1;
        }
        string inPath = "";
        string mainFile = "main";
        vector<string> flags;
        if(argc > 1)
        {
            inPath = auxiliary::get_dir(argv[1]);
            mainFile = auxiliary::get_file_name(argv[1]);
            for(int i = 2; i < argc; ++i)
            {
                flags.push_back(argv[i]);
            }
        }
        string outPath = join(inPath, "stodin-out");
        cpp11_create_folder(outPath);

        vector<string> libFiles = { "__stodin_types.h",
                                    "__stodin_array.h", "__stodin_dict.h",
                                    "__stodin_string.h", "__stodin_string.cpp",
                                    "__stodin_io.h", "__stodin_io.cpp",
                                    "__stodin_file.h", "__stodin_file.cpp",
                                    "__stodin_common.h", "__stodin_common.cpp"};

        bool safeFlag = std::find(flags.begin(), flags.end(), string("-safe")) != flags.end();
        if(safeFlag)
            libFiles.push_back("__stodin_safe.h");
        for(auto & libFile: libFiles)
            copy_lib_to_output(outPath, libFile);

        do_main_file(outPath, mainFile);
        create_module(mainFile, inPath, outPath, flags);
        //cout << "stodin_module: " << moduleRes << endl;
        auto modules = parser::get_modules();
        auto libModules = parser::get_lib_modules();
        auto cppModules = parser::get_cpp_modules();
        vector<string> completedModules = {mainFile};
        while(modules.size() > 0)
        {
            auto modulesCopy = modules;
            for(string module: modulesCopy)
            {
                if(std::find(completedModules.begin(), completedModules.end(), module) == completedModules.end())
                {
                    parser::clear_data();
                    create_module(module, inPath, outPath, flags);
                    completedModules.push_back(module);
                    modules.erase(std::find(modules.begin(), modules.end(), module));
                    auto newModules = parser::get_modules();
                    for(string newModule: newModules)
                    {
                        if(std::find(completedModules.begin(), completedModules.end(), newModule) == completedModules.end())
                        {
                            modules.push_back(newModule);
                        }
                    }
                    auto newLibModules = parser::get_lib_modules();
                    for(string newModule: newLibModules)
                    {
                        if(std::find(libModules.begin(), libModules.end(), newModule) == libModules.end())
                        {
                            libModules.push_back(newModule);
                        }
                    }
                    auto newCppModules = parser::get_cpp_modules();
                    for(string newModule: newCppModules)
                    {
                        if(std::find(cppModules.begin(), cppModules.end(), newModule) == cppModules.end())
                        {
                            cppModules.push_back(newModule);
                        }
                    }
                }
            }
        }
        vector<string> libObjectModules;
        for(auto module: libModules)
        {
            string basicName = "_stodin_lib_" + module;
            string name = basicName + ".h";
            if(file_exists(join(cfg.libPath, name)))
                copy_lib_to_output(outPath, name);
            name = basicName + ".cpp";
            if(file_exists(join(cfg.libPath, name)))
            {
                copy_lib_to_output(outPath, name);
                libObjectModules.push_back(basicName + ".o");
            }
        }

        vector<string> cppObjectModules;
        for(auto module: cppModules)
        {
            string basicName = "_stodin_module_" + module;
            string name = basicName + ".h";
            if(file_exists(join(inPath, name)))
                cpp11_copy_file(join(inPath, name), join(outPath, name));
            name = basicName + ".cpp";
            if(file_exists(join(inPath, name)))
            {
                cpp11_copy_file(join(inPath, name), join(outPath, name));
                cppObjectModules.push_back(basicName + ".o");
            }
        }

        if(parser_error::has_no_errors())
        {
            create_makefile(completedModules, libObjectModules, cppObjectModules, inPath, outPath, mainFile);
            bool runFlag = std::find(flags.begin(), flags.end(), string("-run")) != flags.end();
#ifdef _WIN32
            int sysRes = system(("cd /D " + outPath + " && " + cfg.makeTool + " -f " +
                   join(outPath, "Makefile") + " all").c_str());
            if(!sysRes && runFlag) system(join(inPath, mainFile + ".exe").c_str() );
#else
            int sysRes = system(("cd " + outPath + " ;make -f " +
                "Makefile all ;").c_str());
            if(!sysRes && runFlag) sysRes = system(("cd " + inPath + " ; ./" + mainFile + ".exe").c_str());
            else  cout << "System return value: " << sysRes << endl;
#endif // _WIN32
        }
        else
        {
            cout << "### Translation error!" << endl;
            parser_error::print_errors();
        }

    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
