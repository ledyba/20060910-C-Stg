################################################################################
# �����������ꂽ�t�@�C���B �ҏW���Ȃ��ł�������!
################################################################################

# �r���h�ϐ��Ƀc�[���Ăяo���ׂ̈̓��͂Əo�͂�ǉ����ĉ�����
C_SRCS += \
$(ROOT)/menu/menuFunc.c \
$(ROOT)/menu/menuMode.c 

OBJS += \
./menu/menuFunc.o \
./menu/menuMode.o 

DEPS += \
${addprefix ./menu/, \
menuFunc.d \
menuMode.d \
}


# �e�T�u�f�B���N�g���[�́A�񋟂���\�[�X���r���h���邽�߂̋K����񋟂���K�v������܂��B
menu/%.o: $(ROOT)/menu/%.c
	@echo '�r���h����t�@�C��: $<'
	@echo '�N����: GCC C �R���p�C���['
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo '�r���h����: $<'
	@echo ' '


