################################################################################
# 自動生成されたファイル。 編集しないでください!
################################################################################

# ビルド変数にツール呼び出しの為の入力と出力を追加して下さい
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


# 各サブディレクトリーは、提供するソースをビルドするための規則を提供する必要があります。
data/%.o: $(ROOT)/data/%.c
	@echo 'ビルドするファイル: $<'
	@echo '起動中: GCC C コンパイラー'
	@echo gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $<
	@gcc -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags` -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	gcc -MM -MG -P -w -I"D:\prog\C\lib\pxtone_include" -O0 -g3 -Wall -c -fmessage-length=0 `sdl-config --cflags`  $< >> $(@:%.o=%.d)
	@echo 'ビルド完了: $<'
	@echo ' '


