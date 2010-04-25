#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data/buf.h"
BUF* makeBuf(void* data,long size){
	BUF *buffer;
	buffer = malloc(sizeof((BUF)(*buffer)));
	buffer->data = malloc(size);
	memcpy(buffer->data , data , size);
	buffer->offset = 0;
	buffer->size = size;
	return buffer;
}

void deleteBuf(BUF* buffer){
	free(buffer->data);
	free(buffer);
}

int readBuf(BUF* buf,void* addr,long size){
	if(buf->offset + size < buf->size){
		memcpy((buf->data+buf->offset),addr,size);
		buf->offset += size;
		return TRUE;
	}else{
		return FALSE;
	}
}
int seekBuf(BUF* buf,long offset,int origin){
	long addr;
	switch(origin){
		case SEEK_SET:
			addr = 0;
			break;
		case SEEK_CUR:
			addr = buf->offset;
			break;
		case SEEK_END:
			addr = buf->size;
			break;
		default:
			addr = 0;
			break;
	}
	if(addr + offset < buf->size){
		buf->offset = addr + offset;
		return TRUE;
	}else{
		return FALSE;
	}
}
