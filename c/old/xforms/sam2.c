#include <forms.h>

FL_FORM *form;
FL_OBJECT *yes, *no, *but;

main(int argc, char *argv[])
{
fl_initialize(&argc,argv,"FormDemo",0,0);
form = fl_bgn_form(FL_FRAME_BOX,320,120);
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