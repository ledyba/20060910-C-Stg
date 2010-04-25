################################################################################
# �����������ꂽ�t�@�C���B �ҏW���Ȃ��ł�������!
################################################################################

# �r���h�ϐ��Ƀc�[���Ăяo���ׂ̈̓��͂Əo�͂�ǉ����ĉ�����
C_SRCS += \
$(ROOT)/stage/animationManager.c \
$(ROOT)/stage/eventGenerator.c \
$(ROOT)/stage/stageEngine.c \
$(ROOT)/stage/stageLoader.c 

OBJS += \
./stage/animationManager.o \
./stage/eventGenerator.o \
./stage/stageEngine.o \
./stage/stageLoader.o 

DEPS += \
${addprefix ./stage/, \
animationManager.d \
eventGenerator.d \
stageEngine.d \
stageLoader.d \
}


# �e�T�u�f�B���N�g���[�́A�񋟂���\�[�X���r���h���邽�߂̋K����񋟂���K�v������܂��B
stage/%.o: $(ROOT)/stage/%.c
	@echo '�r���h����t�@�C��: $<'
	@echo '�N����: GCC C �R���p�C���['
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo '�r���h����: $<'
	@echo ' '


