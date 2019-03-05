
#include "twin_buffer.h"

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


Stream getStream(char *filename){
    FILE *fp=fopen(filename,"r");
    if(fp==NULL){
        return NULL;
    }
    Stream s=malloc(sizeof(struct Stream));
    s->valid=false;
    s->current_ptr=NULL;
    s->filename=malloc(strlen(filename)+1);
    strcpy(s->filename,filename);
    s->min_threshold=MAX_TOKEN_SIZE;
    s->twin_buffer=(char*)malloc(sizeof(char)*2*BLOCK_SIZE);
    s->buffers[0]=&(s->twin_buffer[0]);
    s->buffers[1]=&(s->twin_buffer[BLOCK_SIZE]);
    s->remaining_buffer_size=-1;
    s->total_size=2*BLOCK_SIZE;
    s->half_size=BLOCK_SIZE;
    s->reached_eof=false;
    s->current_buffer=Buffer1;
    s->eof_ptr=NULL;
    s->fp=fp;
}

char getChar(Stream s){
    char to_return=0;
    if(s==NULL){
        return 0;
    }
    if(isEofStream(s)){
        return '\0';
    }
    if(s->valid==false && s->reached_eof==false){
        int x=fread(s->buffers[Buffer1],sizeof(char),s->half_size,s->fp);
        (s->twin_buffer)[x]='\0';
        if(x<s->half_size){
            s->reached_eof=true;
            s->eof_ptr=(&(s->buffers[Buffer1][x]))+1;
        }
        if(x!=0){
            s->valid=true;
        }
        to_return=s->twin_buffer[0];
        s->remaining_buffer_size=x-1;
        s->current_ptr=&(s->twin_buffer[1]);
        s->current_buffer=Buffer1;
    }
    else{
        if(s->valid==true && s->remaining_buffer_size<s->min_threshold && s->reached_eof==false){
            if(s->current_buffer==Buffer1){
                int x=fread(s->buffers[Buffer2],s->half_size,1,s->fp);
                (s->twin_buffer)[x]='\0';
                if(x<s->half_size){
                    s->reached_eof=true;
                    s->eof_ptr=(&(s->buffers[Buffer2][x]))+1;
                }
                s->remaining_buffer_size=s->remaining_buffer_size+x;
            }
            else if(s->current_buffer==Buffer2){
                int x=fread(s->buffers[Buffer2],s->half_size,1,s->fp);
                (s->twin_buffer)[x]='\0';
                if(x<s->half_size){
                    s->reached_eof=true;
                    s->eof_ptr=(&(s->buffers[Buffer1][x]))+1;
                }
                s->remaining_buffer_size=s->remaining_buffer_size+x;
            }
        }
        to_return=*(s->current_ptr);
        int a=((s->current_ptr)-(s->twin_buffer)+1)%(s->total_size);
        s->current_ptr=&(s->twin_buffer[a]);
        s->remaining_buffer_size=s->remaining_buffer_size-1;
    }
    return to_return;
}

char retractChar(Stream s){
    if(s==NULL){
        return 0;
    }
    if(s->valid==true){
        int a=(s->total_size + (s->current_ptr-s->twin_buffer) - 1)%(s->total_size);
        s->current_ptr=&(s->twin_buffer[a]);
        s->remaining_buffer_size=s->remaining_buffer_size+1;
        if(a==(s->total_size-1)){
            s->current_buffer=Buffer2;
        }
        else if(a==(s->half_size-1)){
            s->current_buffer=Buffer1;
        }
    }
    return *(s->current_ptr);
}

bool isEofStream(Stream s){ //current char is not eof
    return (s->valid && s->current_ptr==s->eof_ptr && s->reached_eof)||(!s->valid && s->reached_eof);
}