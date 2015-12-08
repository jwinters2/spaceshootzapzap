#include "coord.h"

float MapCoord(float x,float oldmin,float oldmax,float newmin,float newmax)
{
  //return(((x-oldmin)+((newmax-newmin)/(oldmax-oldmin)))+newmin);
  return(((x-oldmin)*((newmax-newmin)/(oldmax-oldmin)))+newmin);
}

float MapLength(float x,float oldlength,float newlength)
{
  return(x*newlength/oldlength);
}
