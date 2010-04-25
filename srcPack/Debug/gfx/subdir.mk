################################################################################
# 自動生成されたファイル。 編集しないでください!
################################################################################

# ビルド変数にツール呼び出しの為の入力と出力を追加して下さい
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


# 各サブディレクトリーは、提供するソースをビルドするための規則を提供する必要があります。
gfx/%.o: $(ROOT)/gfx/%.c
	@echo 'ビルドするファイル: $<'
	@echo '起動中: GCC C コンパイラー'
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo 'ビルド完了: $<'
	@echo ' '


