#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;  
} Frame;

// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

// Function declarations
int fileExists(const char* path);
FrameNode* createFrame(const char* name, unsigned int duration, const char* path);
void insertFrame(FrameNode** head, FrameNode* newFrame);
FrameNode* findFrame(FrameNode* head, const char* name);
void deleteFrame(FrameNode** head, const char* name);
void moveFrame(FrameNode** head, const char* name, int position);
void freeFrameList(FrameNode* head);
int getListSize(FrameNode* head);

#endif