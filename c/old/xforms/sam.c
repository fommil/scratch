#include <forms.h>

FL_FORM *simpleform;

main(int argc, char *argv[])
{
fl_initialize(&argc,argv,"simpleform",0,0);
simpleform = fl_bgn_form(FL_UP_BOX,230,160);
fl_add_button(FL_NORMAL_BUTTON,40,50,150,60,"Push Me");
fl_end_form();
fl_show_form(simpleform,FL_PLACE_MOUSE,FL_NOBORDER,"simpleform");
fl_do_forms();
fl_hide_form(simpleform);
return 0;
}