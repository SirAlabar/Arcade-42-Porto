#ifndef ARCADE_HPP
#define ARCADE_HPP
#include <exception>
#include <filesystem>
#pragma once
#include <cstdlib>
#include <ctime>
#include <dlfcn.h>
#include <iostream>
#include <sys/stat.h>
#include <raylib.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 800

class HotReload {
    private:
    void* library;
    std::string libraryPath;
    std::string sourcePath;
    time_t lastModTime;
    time_t lastSourceModTime;


    time_t getLastMod(const std::string &path) {
        struct stat fileStat;
        if (stat(path.c_str(), &fileStat) == 0)
            return fileStat.st_mtime;
        return 0;
    }


    template<typename FuncType>
    FuncType loadSymbol(const char * name) {
        dlerror();
        FuncType func = reinterpret_cast<FuncType>(dlsym(library, name));
        if (char *error = dlerror()) {
            std::cerr << "Error loading: '" << name << "': " << error << std::endl;
            return nullptr;
        }
        return func;
    }

    typedef void (*update_func)();
    typedef void (*render_func)();

    update_func update_handler;
    render_func render_handler;

    public:
    HotReload(std::string& path) :  library(nullptr), libraryPath(path + ".so"), sourcePath(path + ".cpp"), update_handler(nullptr), render_handler(nullptr) {
        lastSourceModTime = getLastMod(sourcePath);
        if (std::filesystem::exists(libraryPath)) 
            loadLibrary();
        else {
            std::cerr << "Error: shared object doesn't exist" << std::endl;
            throw std::exception();
        }
    }
    ~HotReload() {
        unloadLibrary();
    }

    void loadLibrary(void) {
        unloadLibrary();
        library = dlopen(libraryPath.c_str(), RTLD_NOW);
        if (!library) {
            std::cerr << "Error: cannon load dynamic library" << dlerror() << std::endl;
            return;
        }
        dlerror();
        update_handler = loadSymbol<update_func>("update");
        render_handler = loadSymbol<render_func>("render");
        lastModTime = getLastMod(libraryPath);
        std::cout << "Library loaded successfully" << std::endl;
    }

    void unloadLibrary(void) {
        if (library) {
            dlclose(library);
            library = nullptr;
            update_handler = nullptr;
            render_handler = nullptr;
        }
    }
    bool recompileLibrary() {
        std::cout << "Recompiling shared objects" << std::endl;
        int result = std::system(("c++ -shared -fPIC " + sourcePath + " -o" + libraryPath).c_str());
        if (result == 0) {
            std::cout << "Recompilation successful" << std::endl;
            return true;
        }
        else {
            std::cerr << "Recompilation failed with exit code: " << result << std::endl;
            return false;
        }
    }

    bool checkAndReload() {
        time_t currSourceModTime = getLastMod(sourcePath);
        if ( currSourceModTime > lastSourceModTime) {
            lastSourceModTime = currSourceModTime;
            if (recompileLibrary()) {
                loadLibrary();
                return true;
            }
        }
        if (getLastMod(libraryPath) > lastModTime) {
            loadLibrary();
            return true;
        }
        return false;
    }

	void update () {
		update_handler();
	}
	void render () {
		render_handler();
	}

};
#endif
