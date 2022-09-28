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

	float2 f2a = {2,2};
	float2 f2b = {2,2};

	f32 sum_result = sum(f2a);

	float3 f3a = {2,2,2};
	float float3_sum_result = sum(f3a);

	float atest = aaa[0];	
	f32proto aaaa = {aaa[0],aaa[1],aaa[2]};

	float3 dot_testa = {0,1,0};
	float3 dot_testb = {0,1,0};
	float dotp = dot(dot_testa,dot_testb);
	
	f3 conv_test = (f3){dot_testa[0],dot_testa[1],dot_testa[2]};

	float2 sqroot_test = sqroot(f2a);
	float3 sqroot_testfloat3 = sqroot(dot_testa);

	float2 normlaized_float2 = normalize(f2a);

	for (int i = 0; i < argv; i++){
		printf("%s/n", argc[i]);
	}

	FMJApp app = fmj_app_create();
	app.is_running = true;

#if WINDOWS

	EnableDebugLayer();
	IDXGIAdapter4* adapter = GetAdapter(false);
	ID3D12Device2* device = CreateDevice(adapter);
	ID3D12CommandQueue* commandQueue = CreateCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
	IDXGISwapChain4* swapchain = CreateSwapChain(app.window.ptr,commandQueue,window_size.x,window_size.y,2);

	DescriptorHeap rtv_heap = create_descriptor_heap(device,RTV,2,NONE);

	ID3D12Resource* back_buffers[2];
	init_back_buffers(2,back_buffers,device,swapchain,rtv_heap.ptr);

	Fence fence = create_fence(device);
	EventHandle eh = create_event_handle();

	ID3D12CommandAllocator* command_allocator;
	ID3D12Device2_CreateCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT,&IID_ID3D12CommandAllocator,(void**)&command_allocator);

	ID3D12GraphicsCommandList* command_list;
	ID3D12Device2_CreateCommandList(device, 0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator, NULL, &IID_ID3D12GraphicsCommandList, (void**)&command_list);
	ID3D12GraphicsCommandList_Close(command_list);
	ID3D12CommandAllocator_Reset(command_allocator);

#elif OSX || IOS
#endif

	/*
	//Create a vertex buffer quad
	Vertex vertices[] = {
		{ 
			{ 0.0f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } 
		},
		{ 
			{ 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } 
		},
		{ 
			{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } 
		}
	};
	*/

	while(app.is_running){
		fmj_app_update(&app);
	}


	return 1;
}

