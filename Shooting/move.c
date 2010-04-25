#include <SDL.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/move.h"
#include "include/ship.h"

/*�͂ɂ���Ĉړ�����ׂ��ʂ��v�Z���܂��D*/
uint moveByForce(Vector* out,Point* pt,uint weight){
			Vector dis;	//����
			Vector force;//��
			/*�������擾*/
			dis.x = Ship.pt.x - pt->x;
			dis.y = Ship.pt.y - pt->y;
			dis.speed = sqrti(getDistance2(dis.x,dis.y));
			if(Ship.isShotKeyPressed){
				/*�͂̎擾*/
				getForce(&force,&dis,weight);
				/*�����Ă�^���Œ�*/
				pt->x += force.x;
				pt->y += force.y;
			}else{
				if(Ship.isPrevShotKeyPressed){
					/*��񉟂��ė�����*/
					/*�͂̎擾*/
					getForce(&force,&dis,weight);
						out->x = force.x;
						out->y = force.y;
				}
				/*�ʏ�̈ړ�*/
				pt->x += out->x;
				pt->y += out->y;
			}
			return dis.speed << BIT;
}
void getForce(Vector* force,const Vector* dis,uint weight){
			/*�͂̌v�Z*/
			//��ʐ��̕������₷���H
			uint d = dis->speed;//min(dis->speed,200);
			if(Ship.power >= 0){
				force->speed = ((G1*(Ship.power * Ship.power * (d+100)))) / (G2 * weight);
			}else{
				force->speed = -((G2*(Ship.power * Ship.power)*5)) / (G1 * (d+100) *  weight);
			}
//			force->speed = ((G1*(Ship.power * Ship.power * (d+100)))) / (G2 * weight);
			/*�p���[���}�C�i�X�Ȃ�C���ʂ��}�C�i�X*/
//			if(Ship.power < 0)force->speed*=-1;
			uint distance = dis->speed << BIT;
			/*�͂̑��x����*/
			if(force->speed > distance)force->speed = distance;
			/*�͂̐�������*/
			force->x = ((force->speed * dis->x) / (distance + 1));
			force->y = ((force->speed * dis->y) / (distance + 1));
}
/*
//�z�[�~���O�O�����v�Z����B
void moveByHoming(Vector* source,const Point* pt,const Point* target,uint theta){
	Vector foeVec,rightVec,leftVec;
	//�G�ւ̑��x�x�N�g�����擾
	getVector(&foeVec,pt,target,source->speed);
	//�E���̊p�x����
	rightVec = *source;
	rotateVector(&rightVec,theta);
	if(source->x * foeVec.x + source->y * foeVec.y 
	>= source->x * rightVec.x + source->y * rightVec.y){		//�p�x�����`�F�b�N
		//�͈͓�
		*source = foeVec;
	}else{
		//�͈͊O
		//�����̊p�x����
		leftVec = *source;
		rotateVector(&leftVec,-theta);
		if(foeVec.x * rightVec.x + foeVec.y * rightVec.y
		>= foeVec.x * leftVec.y + foeVec.y * leftVec.y){
			*source = rightVec;
		}else{
			*source = leftVec;
		}
	}
}
*/
