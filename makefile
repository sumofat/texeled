default:
	clang -std=c99 -g -gcodeview -march=x86-64-v2 -DWINDOWS=1 -maes -Wno-int-to-pointer-cast texeled.c -o main.exe -lUser32.lib
old:
	clang -std=c99 -g -gcodeview -march=x86-64-v2 -DWINDOWS=1 -maes -Wno-int-to-pointer-cast main.c -o main.exe
