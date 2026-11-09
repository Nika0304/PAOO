#ifndef GLOBALS_H
#define GLOBALS_H

#include "file_system.h"

// obiecte globale definite in fisiere .cpp diferite (Item 4, obiecte statice)
extern FileSystem tfsGlobal;  // definit in globals_fs.cpp
extern Directory tempDirBad;  // definit in globals_dir.cpp, foloseste tfsGlobal

#endif
