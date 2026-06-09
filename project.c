#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

//saves the project to a text file, returns TRUE if successful
int saveProject(FrameNode* head, const char* projectPath)
{
    FILE* file = fopen(projectPath, "w");
    if (file == NULL)
    {
        return FALSE;
    }

    FrameNode* current = head;
    while (current != NULL)
    {
        fprintf(file, "%s,%u,%s\n", current->frame->name, current->frame->duration, current->frame->path);
        current = current->next;
    }

    fclose(file);
    return TRUE;
}

//loads a project from a text file and returns the head of the list
FrameNode* loadProject(const char* projectPath)
{
    FILE* file = fopen(projectPath, "r");
    if (file == NULL)
    {
        return NULL;
    }

    FrameNode* head = NULL;
    char line[1024] = {0};
    char name[256] = {0};
    unsigned int duration = 0;
    char path[512] = {0};

    while (fgets(line, sizeof(line), file) != NULL)
    {
        //remove newline character if present
        line[strcspn(line, "\n")] = 0;

        //parse the line into name, duration, path
        char* token = strtok(line, ",");
        if (token != NULL)
        {
            strcpy(name, token);

            token = strtok(NULL, ",");
            if (token != NULL)
            {
                duration = (unsigned int)atoi(token);

                token = strtok(NULL, ",");
                if (token != NULL)
                {
                    strcpy(path, token);

                    //check if file exists before creating frame
                    if (fileExists(path))
                    {
                        FrameNode* newFrame = createFrame(name, duration, path);
                        if (newFrame != NULL)
                        {
                            insertFrame(&head, newFrame);
                        }
                    }
                }
            }
        }
    }

    fclose(file);
    return head;
}
