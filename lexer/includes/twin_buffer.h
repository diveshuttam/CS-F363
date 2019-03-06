#ifndef __TWIN_BUFFER_H
#define __TWIN_BUFFER_H
#include<stdbool.h>
#include<stdio.h>
#include"lexerDef.h"
typedef enum BufferName{
	Buffer1,
	Buffer2
} BufferName;



struct Stream{
	bool valid;
	char *filename;
	char *current_ptr;
    char *eof_ptr;
	int remaining_buffer_size;
	int total_size;
	int half_size;
	int min_threshold;
	bool reached_eof;
	char *twin_buffer; // the twin buffer
	char *buffers[2];  // Both buffer[0] and buffer[1] are pointers to part of the twin_buffer
	BufferName current_buffer;
	FILE *fp;
};

typedef struct Stream *Stream;
Stream getStream(const char *filename);
char getChar(Stream s);
char retractChar(Stream s);
bool isEofStream(const Stream s); //current char is not eof
#endif