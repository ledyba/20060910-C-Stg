#include <SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/gfx/sprite.h"
#include "include/screen.h"

int initSDL(int WindowMode){
    /* ������ */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)<0) {
        raiseError("failed to initialize SDL.","\n");
        return 0;
    }

	glEnable(GL_LINE_SMOOTH);

	/*OpenGL�֘A*/
/*
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
*/	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// �L���v�V�����̐ݒ�
	SDL_WM_SetCaption( WINDOW_TITLE, NULL );
	
	int VideoFlag = SDL_OPENGL;//SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_OPENGL;
	if(WindowMode) VideoFlag |= SDL_FULLSCREEN;

	// �E�B���h�E�̏�����
	SDL_SetVideoMode(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SCREEN_BPP,
		VideoFlag
		);
	
	// �}�E�X�J�[�\���������ꍇ��
	//SDL_ShowCursor(SDL_DISABLE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LINE_SMOOTH);

	/*���W�n�̕ϊ�*/
	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1.0f, 1.0f);
//	glMatrixMode(GL_MODELVIEW);

	//�o�b�t�@������������F��ݒ�B�F��
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//���������Ă����܂��B
	glClear(GL_COLOR_BUFFER_BIT);
//	glFlush();
	SDL_GL_SwapBuffers();

    /* �I�� */
    return 1;
}
int quitSDL(){
    SDL_Quit();
    return 1;
}
/**
 * �w�i�������h��Ԃ��܂��D
 * 
 */
void drawBlackBackground(){
	glClear(GL_COLOR_BUFFER_BIT);
/*	glColor4f(0.0f , 0.0f , 0.0f ,0.1f);
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glRectf(  0
			, 0 
 			, SCREEN_WIDTH
			, SCREEN_HEIGHT
			);
	glDisable( GL_BLEND );
*/
}
/**
 * ���T�C�h�������h��Ԃ��܂��B
 */
void drawSideBar(){
	glColor3f(0.0f , 0.0f , 0.0f);
	/*RightSide*/
	glRectf(  0 
			, 0
			, GAME_SCREEN_X_START
			, GAME_SCREEN_HEIGHT
			);
	/*LeftSide*/
	glRectf( (GAME_SCREEN_X_START+GAME_SCREEN_WIDTH)
			, 0
			, SCREEN_WIDTH
			, GAME_SCREEN_HEIGHT
			);
}
/**
 * �J�[�\����`�悵�܂�
 * 
 */
void drawCursor(glPoint* point,GLfloat  size,const GLfloat* color,int isRight){
	size /= 2;
	GLfloat height = size;
	GLfloat width = size * 0.86602540378443864676372317075294f;
	glPushMatrix();
	glTranslatef(point->x,point->y,0.0);
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glColor4fv(color);
		glBegin(GL_TRIANGLE_STRIP);
		if(isRight){
				glVertex2d(-width,-height);
				glVertex2d(-width,+height);
				glVertex2d(+width,0);
		}else{
				glVertex2d(+width,-height);
				glVertex2d(+width,+height);
				glVertex2d(-width,0);
		}
		glEnd();
	glDisable( GL_BLEND );
	glPopMatrix();
}
/**
 * �l�p�`��`�悵�܂��B
 * 
 */
void drawBox(glPoint* point,int isFilled,float width,const GLfloat* color){
	glPushMatrix();
	glTranslatef(point->x,point->y,0.0);
	/*�����ݒ�*/
	glLineWidth(width);
	/*�u�����h�ݒ�*/
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	/*�J���[�ݒ�*/
	glColor4fv(color);
		if(isFilled)	glBegin(GL_QUAD_STRIP);
		else			glBegin(GL_LINE_LOOP);
			glVertex2d( point->width, -point->height);
			glVertex2d( point->width,  point->height);
			glVertex2d(-point->width,  point->height);
			glVertex2d(-point->width, -point->height);
		glEnd();
	glDisable( GL_BLEND );
	glPopMatrix();
}

void drawCircle(const glPoint* point,const GLfloat* color,float width,int isFilled){
	/*���W�ݒ�*/
	glPushMatrix();
	glTranslatef(point->x,point->y,0.0);
	/*�����ݒ�*/
	glLineWidth(width);
	/*�u�����h�ݒ�*/
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	/*�J���[�ݒ�*/
	glColor4fv(color);
	if(isFilled){
		glBegin( GL_TRIANGLE_FAN );
		glVertex2d( 0.0f, 0.0f);
	}else{
		glBegin( GL_LINE_LOOP );
	}
	uint i=0;
	GLfloat radius = point->radius;
	for(;i<360;i++){
		glVertex2d( (radius*ucos(i)) / BIT_POINT, (radius*usin(i)) / BIT_POINT );
	}
	if(isFilled)	glVertex2d(radius , 0.0f);
	glEnd();
	glDisable( GL_BLEND );
	glPopMatrix();
}

