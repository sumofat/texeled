#include <stdio.h>
#define SOKOL_IMPL
#define SOKOL_D3D11
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "FullMetalJacket/src/fmj.c"
#include "ui/ui.h"
#include "engine/sprite/sprite.h"

sg_pass_action pass_action;
f2 window_size = {640, 480};
FMJFixedBuffer ui_fixed_quad_buffer;

void init(void){
	sg_setup(&(sg_desc){
		.context = sapp_sgcontext()
	});
	pass_action = (sg_pass_action){
		.colors[0] = { .action = SG_ACTION_CLEAR, .value = { 0.0f, 0.0f, 0.0f, 1.0f } }
	};

	u64 quad_mem_size = SIZE_OF_SPRITE_IN_BYTES * 100;
	FMJSpriteBatch sb = {0};
	FMJSpriteBatch sb_ui = {0};
	sb.arena = fmj_arena_allocate(quad_mem_size);
	sb_ui.arena = fmj_arena_allocate(quad_mem_size);

	ui_fixed_quad_buffer = fmj_fixed_buffer_init(200,sizeof(SpriteTrans),8); 

	uint64_t stride = sizeof(float) * (3 + 4 + 2);
	f2 stbl = f2_create(0.0f,0.0f);
	f2 stbr = f2_create(1.0f,0.0f);
	f2 sttr = f2_create(1.0f,1.0f);
	f2 sttl = f2_create(0.0f,1.0f);
	f2 uvs[4] = {stbl,stbr,sttr,sttl};
	f4 white = f4_create(1,1,1,1);	

	FMJUIState ui_state = {0};
	FMJUINode base_node = {0};
	base_node.rect.dim = (f4){0,0,window_size.x,window_size.y};
	base_node.children = fmj_stretch_buffer_init(1,sizeof(FMJUINode),8);
	ui_state.parent_node = base_node;

	FMJUINode bkg_child = {0};
	bkg_child.use_anchor = true;
	bkg_child.rect.anchor = f4_create(0.0f, 0.0f, 1.0f, 1.0f);
	bkg_child.rect.offset = f4_create(0,0,0,0);
	bkg_child.rect.color = f4_create(0,0,1,1);
	bkg_child.rect.highlight_color = f4_create(1,0,1,1);
	bkg_child.rect.current_color = bkg_child.rect.color;
	bkg_child.interactable = false;
	bkg_child.rect.z = 0.1f;
	bkg_child.children = fmj_stretch_buffer_init(1,sizeof(FMJUINode),8);
	bkg_child.type = fmj_ui_node_sprite;	

	FMJSprite ui_sprite = {0};

	ui_sprite = fmj_sprite_init(3,uvs,white,true);
	u64 bkg_ui_id = fmj_stretch_buffer_push(&base_node.children,&bkg_child);

	//ui  evaulation
	fmj_ui_evaluate_node(&base_node,&ui_state.hot_node_state);

	fmj_ui_commit_nodes_for_drawing(&sb_ui.arena,base_node,&ui_fixed_quad_buffer,white,uvs);

}
	

void frame(void) {

    float g = pass_action.colors[0].value.g + 0.01f;
    pass_action.colors[0].value.g = (g > 1.0f) ? 0.0f : g;
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
	return (sapp_desc){
		.init_cb = init,
			.frame_cb = frame,
			.cleanup_cb = cleanup,
			.width = window_size.width,
			.height = window_size.height,
			.window_title = "Clear Sample",
	};
}

