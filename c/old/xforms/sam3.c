#include <forms.h>

FL_FORM *form;
FL_OBJECT *yes, *no, *but, *thebox;

main(int argc, char *argv[])
{
fl_initialize(&argc,argv,"FormDemo",0,0);
form = fl_bgn_form(FL_FRAME_BOX,320,120);
thebox=fl_add_box(FL_FRAME_BOX,0,0,320,20,"Hello World!");
fl_set_object_color(thebox,FL_RED,0);
fl_set_object_lcol(thebox,FL_GREEN);
fl_set_object_lsize(thebox,FL_LARGE_SIZE);
	fl_add_box(FL_FRAME_BOX, 160,40,0,0,"Do You Want To Quit?");
	yes = fl_add_button(FL_NORMAL_BUTTON,40,70,80,30,"Yes");
	no  = fl_add_button(FL_NORMAL_BUTTON,200,70,80,30,"No");
fl_end_form();
fl_show_form(form,FL_PLACE_MOUSE,FL_TRANSIENT,"Question");
while ((but = fl_do_forms())!=yes)
	;
fl_hide_form(form);
return 0;
}