################################################################################
# 自動生成されたファイル。 編集しないでください!
################################################################################

# ビルド変数にツール呼び出しの為の入力と出力を追加して下さい
C_SRCS += \
$(ROOT)/bonus.c \
$(ROOT)/boss.c \
$(ROOT)/bullet.c \
$(ROOT)/common.c \
$(ROOT)/eventGenerator.c \
$(ROOT)/foe.c \
$(ROOT)/fps.c \
$(ROOT)/input.c \
$(ROOT)/laser.c \
$(ROOT)/load.c \
$(ROOT)/main.c \
$(ROOT)/move.c \
$(ROOT)/music.c \
$(ROOT)/number.c \
$(ROOT)/point.c \
$(ROOT)/rand.c \
$(ROOT)/screen.c \
$(ROOT)/ship.c \
$(ROOT)/shipState.c \
$(ROOT)/shot.c 

OBJS += \
./bonus.o \
./boss.o \
./bullet.o \
./common.o \
./eventGenerator.o \
./foe.o \
./fps.o \
./input.o \
./laser.o \
./load.o \
./main.o \
./move.o \
./music.o \
./number.o \
./point.o \
./rand.o \
./screen.o \
./ship.o \
./shipState.o \
./shot.o 

DEPS += \
${addprefix ./, \
bonus.d \
boss.d \
bullet.d \
common.d \
eventGenerator.d \
foe.d \
fps.d \
input.d \
laser.d \
load.d \
main.d \
move.d \
music.d \
number.d \
point.d \
rand.d \
screen.d \
ship.d \
shipState.d \
shot.d \
}


# 各サブディレクトリーは、提供するソースをビルドするための規則を提供する必要があります。
%.o: $(ROOT)/%.c
	@echo 'ビルドするファイル: $<'
	@echo '起動中: GCC C コンパイラー'
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo 'ビルド完了: $<'
	@echo ' '


