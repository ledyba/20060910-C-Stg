typedef struct{
	void* data;
	long offset;
	long size;
}BUF;

BUF* makeBuf(void* data,long size);
void deleteBuf(BUF* buffer);

//���ɂ́E�E�E
int readBuf(BUF* buf,void* addr,long size);
//write
int seekBuf(BUF* buf,long offset,int origin);
