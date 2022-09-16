#include "../FullMetalJacket/src/fmj_types.h"
#include "../engine/sprite/sprite.h"
/*
typedef struct ui_rect{
	int x;
	int y;
	int w;
	int h;
} ui_rect;

ui_rect ui_rect_create(int x, int y, int w, int h){
	return (ui_rect){x, y, w, h};
}
*/

FMJUIRect ui_rect_create(){
	return (FMJUIRect){
		.dim = (f4){0, 0, 0, 0},
		.anchor = (f4){0, 0, 0, 0},
		.offset = (f4){0, 0, 0, 0},
		.color = (f4){1, 1, 1, 1},
		.z = 0,
	};
}
	
//draw nodes
//TODO(Ray):Not for sure what convention to use here before we pull this into FMJ
//either each node is associate with a FMJ3DTrans or it has an ID or some other way
//for the user to connect rendering to the  ui nodes.
void fmj_ui_commit_nodes_for_drawing(FMJMemoryArena* arena,FMJUINode base_node,FMJFixedBuffer* quad_buffer,f4 color,f2 uvs[])
{
    for(int i = 0;i < base_node.children.fixed.count;++i)
    {
        FMJUINode* child_node = fmj_stretch_buffer_check_out(FMJUINode,&base_node.children,i);
        if(child_node)
        {
            if(child_node->type == fmj_ui_node_sprite)
            {
                SpriteTrans st= {0};
                st.sprite = child_node->sprite;
                child_node->st_id = fmj_fixed_buffer_push(quad_buffer,(void*)&st);
                fmj_sprite_add_rect_with_dim(arena,child_node->rect.dim,0,child_node->rect.color,uvs);
            }
            else
            {
                ASSERT(false);//no othe rtypes supported yet.
            }
            fmj_ui_commit_nodes_for_drawing(arena,*child_node,quad_buffer,color,uvs);                            
        }
    }
}
//end draw nodes




