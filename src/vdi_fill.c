#include <stdio.h>
#include <fb/libfb.h>

#include "ovdisis.h"
#include "various.h"

void vdi_v_fillarea(VDI_Workstation *vwk)
{
  EDEBUG("v_fillarea: Call not implemented!\n");
}

void vdi_vr_recfl(VDI_Workstation *vwk)
{
  int y,ni;
  unsigned long col;
  RECT cor;

  /* vr_recfl has no perimeter and hollow means nothing! */
  if(vwk->fill_a.interior == FIS_HOLLOW)
    return;

  cor.x1 = vdipb->ptsin[0];
  cor.y1 = vdipb->ptsin[1];
  cor.x2 = vdipb->ptsin[2];
  cor.y2 = vdipb->ptsin[3];

  if(do_rectclip(&cor, &vwk->clip))
    {
      ni = gem2tos_color(vwk->inq.attr.planes, vwk->fill_a.color);
      col = get_color(vwk, ni);

      switch(vwk->fill_a.interior)
	{
	case FIS_SOLID:
	  for(y=cor.y1 ; y<=cor.y2 ; y++)
	    FBhline(vwk->fb, cor.x1, cor.x2, y, col);
	  break;
	case FIS_PATTERN:
	case FIS_HATCH:
	case FIS_USER:
	  EDEBUG("vr_recfl: Unsupported filling style, %d!\n", vwk->fill_a.interior);
	  break;
	default:
	  EDEBUG("vr_recfl: Unknown filling style, %d!\n", vwk->fill_a.interior);
	  break;
	}
    }
}

void vdi_v_contour(VDI_Workstation *vwk)
{
  EDEBUG("v_contour: Call not implemented!\n");
}

void vdi_vsf_color(VDI_Workstation *vwk)
{
  vwk->fill_a.color = (int)vdipb->intin[0];
  vdipb->intout[0] = (short)vwk->fill_a.color;

  vdipb->contrl[N_INTOUT] = 1;
}

void vdi_vsf_interior(VDI_Workstation *vwk)
{
  vwk->fill_a.interior=(int)vdipb->intin[0];
  vdipb->intout[0]=(short)vwk->fill_a.interior;

  vdipb->contrl[N_INTOUT]=1;
}

void vdi_vsf_style(VDI_Workstation *vwk)
{
  vwk->fill_a.style=(int)vdipb->intin[0];
  vdipb->intout[0]=(short)vwk->fill_a.style;

  vdipb->contrl[N_INTOUT]=1;
}

void vdi_vsf_udpat(VDI_Workstation *vwk)
{
  int n,r;

  vwk->fill_a.udpat_nbpl=(int)vdipb->contrl[N_INTIN]/16;
  
  for(n=0 ; n < vwk->fill_a.udpat_nbpl ; n++)
    for(r=0 ; r < 16 ; r++)
      vwk->fill_a.udpat[n][r]=(unsigned short)vdipb->intin[n*16+r];
}

void vdi_vsf_perimeter(VDI_Workstation *vwk)
{
  vwk->fill_a.perimeter=(int)vdipb->intin[0];
  vdipb->intout[0]=(short)vwk->fill_a.perimeter;

  vdipb->contrl[N_INTOUT]=1;
}

void vdi_vqf_attributes(VDI_Workstation *vwk)
{
  vdipb->intout[0]=(short)vwk->fill_a.interior;
  vdipb->intout[1]=(short)vwk->fill_a.color;
  vdipb->intout[2]=(short)vwk->fill_a.style;
  vdipb->intout[3]=(short)vwk->write_mode;
  vdipb->intout[4]=(short)vwk->fill_a.perimeter;

  vdipb->contrl[N_INTOUT]=5;
}







