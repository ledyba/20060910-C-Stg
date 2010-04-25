################################################################################
# �����������ꂽ�t�@�C���B �ҏW���Ȃ��ł�������!
################################################################################

# �r���h�ϐ��Ƀc�[���Ăяo���ׂ̈̓��͂Əo�͂�ǉ����ĉ�����
C_SRCS += \
$(ROOT)/gfx/animation.c \
$(ROOT)/gfx/graphic.c \
$(ROOT)/gfx/sprite.c \
$(ROOT)/gfx/spriteArea.c \
$(ROOT)/gfx/textRenderer.c 

OBJS += \
./gfx/animation.o \
./gfx/graphic.o \
./gfx/sprite.o \
./gfx/spriteArea.o \
./gfx/textRenderer.o 

DEPS += \
${addprefix ./gfx/, \
animation.d \
graphic.d \
sprite.d \
spriteArea.d \
textRenderer.d \
}


# �e�T�u�f�B���N�g���[�́A�񋟂���\�[�X���r���h���邽�߂̋K����񋟂���K�v������܂��B
gfx/%.o: $(ROOT)/gfx/%.c
	@echo '�r���h����t�@�C��: $<'
	@echo '�N����: GCC C �R���p�C���['
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo '�r���h����: $<'
	@echo ' '


