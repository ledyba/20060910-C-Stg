################################################################################
# 自動生成されたファイル。 編集しないでください!
################################################################################

# ビルド変数にツール呼び出しの為の入力と出力を追加して下さい
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


# 各サブディレクトリーは、提供するソースをビルドするための規則を提供する必要があります。
stage/%.o: $(ROOT)/stage/%.c
	@echo 'ビルドするファイル: $<'
	@echo '起動中: GCC C コンパイラー'
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -I"D:\prog\C\PGL\include" -I"F:\path\MSYS\include\SDL" -I"F:\path\MinGW\include" -O3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo 'ビルド完了: $<'
	@echo ' '


