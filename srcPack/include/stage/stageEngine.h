/*�X�e�[�W�i�s�Ɋւ��邱�Ƃ��s���܂��B�����I�ɁB*/

#define STAGE_MAX	5			//�X�e�[�W��
int StageNumber;				//���݂̃X�e�[�W��

/**
 * �X�e�[�W�G���W��������������B
 */
int initStageEngine(int stage);
/**
 * �X�e�[�W�G���W�������ۂɓ�����
 */
void startStageEngine();
/**
 * �G�����A�C�x���g�����Ȃǂ𑍍��I�ɍs���B
 */
void moveStageEngine();
/**
 * �������J���A���̑������������s���B
 * moveStageEngine����̂݁A�Ă΂��B
 */
int quitStageEngine();
