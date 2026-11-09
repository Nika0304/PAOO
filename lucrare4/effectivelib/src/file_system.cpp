#include "file_system.h"

#include <iostream>

FileSystem::FileSystem() : numDisks(0), ready(false)
{
    std::cout << "[FileSystem] constructor: incep sa construiesc\n";
    numDisks = 4;
    ready = true;
    std::cout << "[FileSystem] constructor: gata, " << numDisks << " discuri\n";
}

bool FileSystem::isReady() const
{
    return ready;
}

int FileSystem::getNumDisks() const
{
    return numDisks;
}

FileSystem& tfs()
{
    static FileSystem fs;  // se construieste la primul apel
    return fs;
}

Directory::Directory(FileSystem& fs, const std::string& newLabel) : label(newLabel), fsReady(fs.isReady())
{
    std::cout << "[Directory '" << label << "'] constructor: file system-ul era gata? "
              << (fsReady ? "DA" : "NU") << '\n';
}

bool Directory::wasFileSystemReady() const
{
    return fsReady;
}

const std::string& Directory::getLabel() const
{
    return label;
}
