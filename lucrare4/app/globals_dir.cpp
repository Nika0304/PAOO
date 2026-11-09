#include <iostream>  // il includ si aici ca std::cout sa fie gata inainte de obiectele globale de mai jos

#include "globals.h"

// foloseste tfsGlobal, care e definit in alt fisier (globals_fs.cpp)
// standardul nu garanteaza ca tfsGlobal e construit inainte de tempDirBad
Directory tempDirBad(tfsGlobal, "tempDirBad");
