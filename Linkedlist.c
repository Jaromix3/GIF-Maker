#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

//checks if a file exists at the given path
int fileExists(const char* path)
{
    FILE* file = fopen(path, "r");
    if (file != NULL)
    {
        fclose(file);
        return TRUE;
    }
    return FALSE;
}

//creates a new frame node with the given parameters
FrameNode* createFrame(const char* name, unsigned int duration, const char* path)
{
    //allocate memory for the node
    FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
    if (newNode == NULL)
    {
        return NULL;
    }

    //allocate memory for the frame struct
    newNode->frame = (Frame*)malloc(sizeof(Frame));
    if (newNode->frame == NULL)
    {
        free(newNode);
        return NULL;
    }

    //allocate and copy the name
    newNode->frame->name = (char*)malloc(strlen(name) + 1);
    if (newNode->frame->name == NULL)
    {
        free(newNode->frame);
        free(newNode);
        return NULL;
    }

    //allocate and copy the path
    newNode->frame->path = (char*)malloc(strlen(path) + 1);
    if (newNode->frame->path == NULL)
    {
        free(newNode->frame->name);
        free(newNode->frame);
        free(newNode);
        return NULL;
    }

    strcpy(newNode->frame->name, name);
    strcpy(newNode->frame->path, path);
    newNode->frame->duration = duration;
    newNode->next = NULL;

    return newNode;
}

//inserts a frame at the end of the linked list
void insertFrame(FrameNode** head, FrameNode* newFrame)
{
    if (*head == NULL)
    {
        *head = newFrame;
        return;
    }

    FrameNode* current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newFrame;
}

//finds a frame by name, returns NULL if not found
FrameNode* findFrame(FrameNode* head, const char* name)
{
    FrameNode* current = head;
    while (current != NULL)
    {
        if (strcmp(current->frame->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//deletes a frame from the list by name and frees its memory
void deleteFrame(FrameNode** head, const char* name)
{
    if (*head == NULL)
    {
        return;
    }

    //check if the frame to delete is the head
    if (strcmp((*head)->frame->name, name) == 0)
    {
        FrameNode* temp = *head;
        *head = (*head)->next;
        free(temp->frame->name);
        free(temp->frame->path);
        free(temp->frame);
        free(temp);
        return;
    }

    //search for the frame
    FrameNode* current = *head;
    while (current->next != NULL && strcmp(current->next->frame->name, name) != 0)
    {
        current = current->next;
    }

    if (current->next != NULL)
    {
        FrameNode* temp = current->next;
        current->next = temp->next;
        free(temp->frame->name);
        free(temp->frame->path);
        free(temp->frame);
        free(temp);
    }
}

//moves a frame to a new 1-based position in the list
void moveFrame(FrameNode** head, const char* name, int position)
{
    FrameNode* frameToMove = NULL;

    //check if it's the head
    if (strcmp((*head)->frame->name, name) == 0)
    {
        frameToMove = *head;
        *head = (*head)->next;
    }
    else
    {
        //find the node before the frame we want to move
        FrameNode* current = *head;
        while (current->next != NULL && strcmp(current->next->frame->name, name) != 0)
        {
            current = current->next;
        }

        if (current->next == NULL)
        {
            //frame not found
            return;
        }

        frameToMove = current->next;
        current->next = frameToMove->next;
    }

    frameToMove->next = NULL;

    //insert at the new position
    if (position == 1)
    {
        frameToMove->next = *head;
        *head = frameToMove;
    }
    else
    {
        FrameNode* current = *head;
        int i = 0;
        for (i = 1; i < position - 1; i++)
        {
            current = current->next;
        }
        frameToMove->next = current->next;
        current->next = frameToMove;
    }
}

//frees all memory in the linked list
void freeFrameList(FrameNode* head)
{
    FrameNode* current = head;
    while (current != NULL)
    {
        FrameNode* temp = current;
        current = current->next;
        free(temp->frame->name);
        free(temp->frame->path);
        free(temp->frame);
        free(temp);
    }
}

//returns the number of nodes in the list
int getListSize(FrameNode* head)
{
    int size = 0;
    FrameNode* current = head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}
