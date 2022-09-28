default:
	clang -std=c11 -g -gcodeview -fenable-matrix -march=x86-64-v2 -DWINDOWS=1 -maes -Wno-int-to-pointer-cast texeled.c -o main.exe -lUser32.lib -lDXGI.lib -lGdi32.lib -lkernel32.lib -lWinMM.lib -lD3D12.lib -lD3DCompiler.lib
osx:
	clang -std=c11 -g -gcodeview -fenable-matrix -march=x86-64-v2 -DOSX=1 -maes -Wno-int-to-pointer-cast texeled.c -o main
