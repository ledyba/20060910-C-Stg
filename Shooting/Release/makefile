################################################################################
# 自動生成されたファイル。 編集しないでください!
################################################################################

ROOT := ..

-include $(ROOT)/makefile.init

RM := rm -rf

# ビルドに関与するすべてのソースをここに定義します。
-include sources.mk
-include $(SUBDIRS:%=%/subdir.mk)
-include objects.mk
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif

-include $(ROOT)/makefile.defs

# ビルド変数にツール呼び出しの為の入力と出力を追加して下さい

# 全ターゲット
all: Shooting.exe

# ツール呼び出し
Shooting.exe: $(OBJS) $(USER_OBJS)
	@echo 'ビルド・ターゲット: $@'
	@echo '起動中: GCC C リンカー'
	@echo gcc -s -L"F:\path\MSYS\lib" -L"D:\prog\C\PGL\Release" -L"D:\prog\C\lib\pxtone_include" -mwindows -oShooting.exe $(OBJS) $(USER_OBJS) $(LIBS)
	@gcc -s -L"F:\path\MSYS\lib" -L"D:\prog\C\PGL\Release" -L"D:\prog\C\lib\pxtone_include" -mwindows -oShooting.exe $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'ビルド完了ターゲット: $@'
	@echo ' '

# その他のターゲット
clean:
	-$(RM) $(OBJS)$(EXECUTABLES)$(DEPS) Shooting.exe
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include $(ROOT)/makefile.targets
