#ifndef PROJECTH
#define PROJECTH

#include "LinkedList.h"

int saveProject(FrameNode* head, const char* projectPath);
FrameNode* loadProject(const char* projectPath);

#endif