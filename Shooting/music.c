#include <windows.h>
#include <pxtone.h>

int initMusic(){
	int result = 0;
 	result = pxtone_Ready(
	NULL,	// �E�C���h�E�n���h����n���Ă�������
	2,		// �`�����l�������w�肵�Ă��������B( 1:���m���� / 2:�X�e���I )
	44100,	// �b�ԃT���v�����O���[�g�ł��B      ( 11025 / 22050 / 44100 )
	16,		// �P�T���v����\������r�b�g���ł��B( 8 / 16 )
	0.1,   	// �Ȃ��Đ�����̂Ɏg�p����o�b�t�@�T�C�Y��b�Ŏw�肵�܂��B( ���� 0.1 )
	FALSE,	// TRUE: DirectSound ���g�p���܂� / FALSE: WAVEMAPPER ���g�p���܂��B
	NULL	// �T���v�����O���ɌĂ΂��֐��ł��BNULL �ł��܂��܂���B
); // pxtone �̏���
	return result;
}
int loadMusic(char* name){
	int result = 0;
	result = pxtone_Tune_Load(
		NULL,       // ���\�[�X����ǂޏꍇ�̓��W���[���n���h�����w�肵�܂��BNULL �ł����Ȃ������B
		NULL, // ���\�[�X����ǂޏꍇ�̓��\�[�X�̎�ޖ��B�O���t�@�C����ǂޏꍇ�� NULL�B
		name  // �t�@�C���p�X�������̓��\�[�X���B
	);
	return result;
}

int playMusic(long start_sample,long fade_msec){
int result =  pxtone_Tune_Start(
	start_sample,     // �J�n�ʒu�ł��B��� Stop �� Fadeout �Ŏ擾�����l��ݒ肵�܂��B0 �ōŏ�����B
	fade_msec         // �t�F�[�h�C������ꍇ�͂����Ɏ��ԁi�~���b�j���w�肵�܂��B
	);
	return result;
}
