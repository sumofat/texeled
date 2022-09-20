#include <stdio.h>
#include "FullMetalJacket/src/fmj.c"
#include "ui/ui.h"
#include "engine/sprite/sprite.h"

#if WINDOWS
#include "dxgi1_4.h"
//#include "D3DX12.h"
#include "D3d12.h"
#include "D3DCompiler.h"
#endif

f2 window_size = {640, 480};

int main(int argv,char* argc[]){
	printf("TEXELED /n");

	for (int i = 0; i < argv; i++){
		printf("%s/n", argc[i]);
	}

	FMJApp app = fmj_app_create();


	while(app.is_running){
		fmj_app_update(&app);
	}

	return 1;
}




