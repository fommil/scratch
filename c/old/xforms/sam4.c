#include <forms.h>

FL_FORM *form;
FL_OBJECT *samplot,*yes,*but;

main(int argc, char *argv[])
{
int i;
float xdatapoints[50],ydatapoints[50];
for(i=0;i<50;i++)
	{
	xdatapoints[i]=i;
	ydatapoints[i]=20;
	}

fl_initialize(&argc,argv,"FormDemo",0,0);
form = fl_bgn_form(FL_FRAME_BOX,700,500);
	yes = fl_add_button(FL_NORMAL_BUTTON,0,0,80,20,"Quit");
samplot=fl_add_xyplot(FL_NORMAL_XYPLOT,0,20,700,480,"");
fl_set_xyplot_data(samplot,xdatapoints,ydatapoints,50,"title","x-title","y|title");
fl_end_form();
fl_show_form(form,FL_PLACE_MOUSE,FL_TRANSIENT,"Sam's Program");
while ((but = fl_do_forms())!=yes)
	;
fl_hide_form(form);
return 0;
}