#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>

// Item 4: obiecte statice din fisiere diferite
// ordinea in care se construiesc obiectele globale din fisiere .cpp diferite nu e garantata
class FileSystem
{
public:
    FileSystem();

    bool isReady() const;
    int getNumDisks() const;

private:
    int numDisks;
    bool ready;  // devine true abia la sfarsitul constructorului
};

// solutia din carte: in loc de obiect global, o functie care intoarce un obiect static local
// obiectul se construieste la primul apel, deci e mereu gata cand e folosit
FileSystem& tfs();

// obiect care are nevoie de un FileSystem gata construit
class Directory
{
public:
    Directory(FileSystem& fs, const std::string& newLabel);

    bool wasFileSystemReady() const;
    const std::string& getLabel() const;

private:
    std::string label;
    bool fsReady;
};

#endif
