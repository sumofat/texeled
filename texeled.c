#include <stdio.h>
#include "FullMetalJacket/src/fmj.c"
#include "ui/ui.h"
#include "engine/sprite/sprite.h"

f2 window_size = {640, 480};
typedef float vec4f __attribute__ ((vector_size (16)));
typedef int vec4i __attribute__ ((vector_size (16)));

typedef float vec2f __attribute__ ((vector_size (8)));
typedef int vec2i __attribute__ ((vector_size (8)));

typedef float vec3f __attribute__ ((vector_size (12)));
typedef int vec3i __attribute__ ((vector_size (12)));

typedef float m4x4_t __attribute__((matrix_type(4, 4)));

typedef struct{
	float x, y, z;
}f32proto;

int main(int argv,char* argc[]){
	printf("TEXELED /n");

	vec4f a = { 1, 2, 3, 4 }, b = { 5, 6, 7, 8 };
    vec4f c = a * (a + b);

	vec2f aa = {2,2};
	vec2f bb = {2,2};
	vec2f cc = aa * bb;
	
	vec3f aaa = {2,2,2};
	vec3f bbb = {2,2,2};
	vec3f ccc = aaa * bbb;

	float atest = aaa[0];	
	f32proto aaaa = {aaa[0],aaa[1],aaa[2]};

	for (int i = 0; i < argv; i++){
		printf("%s/n", argc[i]);
	}

	FMJApp app = fmj_app_create();
	app.is_running = true;

	EnableDebugLayer();
	IDXGIAdapter4* adapter = GetAdapter(false);
	ID3D12Device2* device = CreateDevice(adapter);
	ID3D12CommandQueue* commandQueue = CreateCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
	IDXGISwapChain4* swapchain = CreateSwapChain(app.window.ptr,commandQueue,window_size.x,window_size.y,2);

	while(app.is_running){
		fmj_app_update(&app);
	}

	return 1;
}




