################################################################################
# �����������ꂽ�t�@�C���B �ҏW���Ȃ��ł�������!
################################################################################

# �r���h�ϐ��Ƀc�[���Ăяo���ׂ̈̓��͂Əo�͂�ǉ����ĉ�����
C_SRCS += \
$(ROOT)/data/buf.c \
$(ROOT)/data/config.c \
$(ROOT)/data/data.c \
$(ROOT)/data/resource_define.c 

OBJS += \
./data/buf.o \
./data/config.o \
./data/data.o \
./data/resource_define.o 

DEPS += \
${addprefix ./data/, \
buf.d \
config.d \
data.d \
resource_define.d \
}


# �e�T�u�f�B���N�g���[�́A�񋟂���\�[�X���r���h���邽�߂̋K����񋟂���K�v������܂��B
data/%.o: $(ROOT)/data/%.c
	@echo '�r���h����t�@�C��: $<'
	@echo '�N����: GCC C �R���p�C���['
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo '�r���h����: $<'
	@echo ' '


