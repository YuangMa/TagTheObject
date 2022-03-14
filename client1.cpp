#include <iostream>
#include "File.h"
#include "Shadow_Directory.h"
#include<list>
using namespace std;

int main() 
{
    Shadow_Directory sd {"http://localhost:8384"};
    std::list<File> files = sd.searchFileByTag("ucdavis");
    std::cout << "Original files tagged on \"ucdavis\"" << std::endl;
    for(File& f : files) {
        std::cout << f.dumpToJson().toStyledString() << std::endl;
    }

    File newfile = sd.createFile("ecs251_hw2", "This is hw2", "user1", "user1");
    std::cout << "Created a new file on server.\n" << newfile.dumpToJson().toStyledString() << std::endl;

    files = sd.searchFileByTag("ucdavis");
    std::cout << "files tagged on \"ucdavis\"" << std::endl;
    for(File& f : files) {
        std::cout << f.dumpToJson().toStyledString() << std::endl;
    }

    File file1 = sd.getFile("fhandle-0");
    std::cout << "Get file on server.\n" << file1.dumpToJson().toStyledString() << std::endl;

    File newfile_update = sd.updateFile("fhandle-1", "This is hw2 modified", "user1", "ucdavis-cs");
    files = sd.searchFileByTag("ucdavis-cs");
    std::cout << "files tagged on \"ucdavis-cs\"" << std::endl;
    for(File& f : files) {
        std::cout << f.dumpToJson().toStyledString() << std::endl;
    }

}