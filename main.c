#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "view.h"
#include "project.h"

void showStartMenu();
void showMenu();
void addFrame(FrameNode** head);
void removeFrame(FrameNode** head);
void changeFramePosition(FrameNode** head);
void changeFrameDuration(FrameNode* head);
void changeAllFramesDuration(FrameNode* head);
void printFrameList(FrameNode* head);
void saveProjectOption(FrameNode* head);
FrameNode* loadProjectOption();

int main()
{
    FrameNode* head = NULL;
    int startChoice = 0;
    int choice = 0;

    printf("Welcome to Magshimim GIF Maker! what would you like to do?\n");

    //show start menu and get valid choice
    while (1)
    {
        showStartMenu();
        scanf("%d", &startChoice);

        if (startChoice == 1)
        {
            //create new project - start with empty list
            head = NULL;
            break;
        }
        else if (startChoice == 2)
        {
            //load existing project
            head = loadProjectOption();
            break;
        }
    }

    //main menu loop
    while (1)
    {
        showMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 0:
                printf("Bye!\n");
                freeFrameList(head);
                return 0;
            case 1:
                addFrame(&head);
                break;
            case 2:
                removeFrame(&head);
                break;
            case 3:
                changeFramePosition(&head);
                break;
            case 4:
                changeFrameDuration(head);
                break;
            case 5:
                changeAllFramesDuration(head);
                break;
            case 6:
                printFrameList(head);
                break;
            case 7:
                if (head == NULL)
                {
                    printf("GIF is empty. Nothing to play.\n");
                }
                else
                {
                    play(head);
                }
                break;
            case 8:
                saveProjectOption(head);
                break;
            default:
                break;
        }
    }

    return 0;
}

//show the start menu options
void showStartMenu()
{
    printf(" [0] Exit\n");
    printf(" [1] Create a new project\n");
    printf(" [2] Load existing project\n");
}

//show the main menu options
void showMenu()
{
    printf("What would you like to do?\n");
    printf(" [0] Exit\n");
    printf(" [1] Add new Frame\n");
    printf(" [2] Remove a Frame\n");
    printf(" [3] Change frame index\n");
    printf(" [4] Change frame duration\n");
    printf(" [5] Change duration of all frames\n");
    printf(" [6] List frames\n");
    printf(" [7] Play GIF!\n");
    printf(" [8] Save project\n");
}

//adds a new frame to the end of the linked list
void addFrame(FrameNode** head)
{
    char name[256] = {0};
    char path[512] = {0};
    unsigned int duration = 0;

    printf("*** Creating new Frame ***\n");

    //get path from user
    printf("Please insert frame path:\n");
    scanf("%s", path);

    //check if the file exists
    if (!fileExists(path))
    {
        printf("File not found. Frame not added.\n");
        return;
    }

    //get duration from user
    printf("Please insert frame duration(in miliseconds):\n");
    scanf("%u", &duration);

    //get name - keep asking until a unique name is given
    while (1)
    {
        printf("Please choose a name for that frame:\n");
        scanf("%s", name);

        if (findFrame(*head, name) == NULL)
        {
            break;
        }
        printf("The name is already taken, please enter another name\n");
    }

    //create the frame and insert it
    FrameNode* newFrame = createFrame(name, duration, path);
    if (newFrame == NULL)
    {
        return;
    }

    insertFrame(head, newFrame);
}

//removes a frame from the linked list by name
void removeFrame(FrameNode** head)
{
    char name[256] = {0};

    printf("Enter the name of the frame you wish to erase\n");
    scanf("%s", name);

    if (findFrame(*head, name) == NULL)
    {
        printf("Frame not found.\n");
        return;
    }

    deleteFrame(head, name);
}

//changes the index (position) of a frame in the linked list
void changeFramePosition(FrameNode** head)
{
    char name[256] = {0};
    int position = 0;
    int listSize = getListSize(*head);

    if (listSize == 0)
    {
        printf("No frames in the GIF.\n");
        return;
    }

    printf("Enter the name of the frame\n");
    scanf("%s", name);

    if (findFrame(*head, name) == NULL)
    {
        printf("Frame not found.\n");
        return;
    }

    printf("Enter the new index in the GIF you wish to place the frame\n");
    scanf("%d", &position);

    if (position < 1 || position > listSize)
    {
        printf("Invalid position.\n");
        return;
    }

    moveFrame(head, name, position);
}

//changes the duration of a specific frame by name
void changeFrameDuration(FrameNode* head)
{
    char name[256] = {0};
    unsigned int newDuration = 0;

    printf("Enter frame name: ");
    scanf("%s", name);

    FrameNode* frame = findFrame(head, name);
    if (frame == NULL)
    {
        printf("Frame not found.\n");
        return;
    }

    printf("Enter new duration (milliseconds): ");
    scanf("%u", &newDuration);

    frame->frame->duration = newDuration;
}

//changes the duration of all frames in the list
void changeAllFramesDuration(FrameNode* head)
{
    unsigned int newDuration = 0;
    FrameNode* current = head;

    if (head == NULL)
    {
        printf("No frames in the GIF.\n");
        return;
    }

    printf("Enter the duration for all frames:\n");
    scanf("%u", &newDuration);

    while (current != NULL)
    {
        current->frame->duration = newDuration;
        current = current->next;
    }
}

//prints all frames in a formatted table
void printFrameList(FrameNode* head)
{
    FrameNode* current = head;

    if (head == NULL)
    {
        printf("No frames in the GIF.\n");
        return;
    }

    //print table header
    printf("\t\t\tName\t\t\tDuration\t\tPath\n");

    while (current != NULL)
    {
        printf("\t\t\t%s\t\t\t%u ms\t\t\t%s\n",
               current->frame->name,
               current->frame->duration,
               current->frame->path);
        current = current->next;
    }
}

//saves the current project to a file
void saveProjectOption(FrameNode* head)
{
    char projectPath[512] = {0};

    if (head == NULL)
    {
        printf("No frames to save.\n");
        return;
    }

    printf("Where to save the project? enter a full path and file name\n");
    scanf("%s", projectPath);

    if (saveProject(head, projectPath))
    {
        printf("Project loaded successfully\n");
    }
    else
    {
        printf("Error saving project.\n");
    }
}

//loads a project from a file and returns the head of the list
FrameNode* loadProjectOption()
{
    char projectPath[512] = {0};

    printf("Enter the path of the project (including project name):\n");
    scanf("%s", projectPath);

    FrameNode* head = loadProject(projectPath);
    if (head == NULL)
    {
        printf("Error loading project.\n");
    }
    else
    {
        printf("Project loaded successfully\n");
    }

    return head;
}
