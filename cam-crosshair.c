/*
*	In order to compile this source code run, in a terminal window, the following command:
*	gcc cam-crosshair.c `pkg-config --libs --cflags opencv` -o cam-crosshair.c
*/
// header:

#ifdef _CH_
#pragma package <opencv>
#endif

#include <stdio.h>
#include <stdlib.h>
/* For "getcwd". */
#include <unistd.h>
/* For "strerror". */
#include <string.h>
/* For "errno". */
#include <errno.h>



#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#include "highgui.h"
#include "cxmisc.h"
//#include "ml.h"
#include <math.h>

char *set_circle(char *circle)
{
static char cwd[PATH_MAX+1];
        if (getcwd(cwd, PATH_MAX+1) == NULL) {
            perror("getcwd failed"); 
           return 0;          
        } else return strcat(cwd, circle);
}

int main(int argc, char ** argv)
{
//declaration block
char* block3_arg_Filename  = malloc(sizeof(char)*PATH_MAX+1);
strncpy(block3_arg_Filename,set_circle("/1.png"),PATH_MAX+1);

IplImage * block1_img_o1 = NULL;
IplImage * block3_img_o1 = NULL;
IplImage * block13_img_i1 = NULL;
IplImage * block13_img_i2 = NULL;
IplImage * block13_img_o1 = NULL;
IplImage * block2_img_i1 = NULL;
IplImage * block2_img_o1 = NULL;
CvFont font;

int end;  end = 0; int key; char keystr[20];
CvCapture * block1_capture = NULL; 
 IplImage * block1_frame = NULL; 
 block1_capture = cvCaptureFromCAM(0); 

cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, CV_AA);

while(!end) 
 {	 
cvGrabFrame (block1_capture); 
 block1_frame = cvRetrieveFrame (block1_capture,CV_WINDOW_AUTOSIZE); 

//execution block
//Weight: 1
// Live Mode 
block1_img_o1 = cvCloneImage( block1_frame );
block13_img_i1 = cvCloneImage(block1_img_o1);// IMAGE conection
//Weight: 1
block3_img_o1 = cvLoadImage(block3_arg_Filename,-1);
block13_img_i2 = cvCloneImage(block3_img_o1);// IMAGE conection
//Weight: 3

if(block13_img_i1){
block13_img_o1 = cvCreateImage(cvSize(block13_img_i1->width,block13_img_i1->height),block13_img_i1->depth,block13_img_i1->nChannels);
if(block13_img_i1->width != block13_img_i2->width || block13_img_i1->height != block13_img_i2->height)
{
	int minW,minH;
	if(block13_img_i1->width > block13_img_i2->width)
		minW = block13_img_i2->width;
	else 
		minW = block13_img_i1->width;

	if(block13_img_i1->height > block13_img_i2->height)
		minH = block13_img_i2->height;
	else 
		minH = block13_img_i1->height;

	cvSetImageROI(block13_img_i2, cvRect( 0, 0, minW, minH ));
	cvSetImageROI(block13_img_i1, cvRect( 0, 0, minW, minH ));
	cvSetImageROI(block13_img_o1, cvRect( 0, 0, minW, minH ));
}
cvAdd(block13_img_i1, block13_img_i2, block13_img_o1,0);
 cvResetImageROI(block13_img_o1);}
block2_img_i1 = cvCloneImage(block13_img_o1);// IMAGE conection
//Weight: 6


key = (char)cvWaitKey (50);
switch ( key ) {
case 27:
  end = 1;
  break;
case -1:
   //do nothing
   break;
case -66:
   strncpy(block3_arg_Filename,set_circle("/1.png"),PATH_MAX+1);
  break;
case -65:
   strncpy(block3_arg_Filename,set_circle("/2.png"),PATH_MAX+1);
  break;
case -64:
   strncpy(block3_arg_Filename,set_circle("/3.png"),PATH_MAX+1);
  break;
case -63:
   strncpy(block3_arg_Filename,set_circle("/4.png"),PATH_MAX+1);
  break;

case -62:
   strncpy(block3_arg_Filename,set_circle("/5.png"),PATH_MAX+1);
  break;

default:
  strncpy(block3_arg_Filename,set_circle("/1.png"),PATH_MAX+1);
  break;
}



if(block2_img_i1){
sprintf(keystr, "%d",key);
cvPutText(block2_img_i1, keystr, cvPoint(10, 130), &font, cvScalar(255, 255, 255, 0));
block2_img_o1 = cvCloneImage(block2_img_i1);
cvNamedWindow("block2_img_o1",CV_WINDOW_AUTOSIZE );
cvShowImage("block2_img_o1",block2_img_i1);
} 

//deallocation block
cvReleaseImage(&block1_img_o1);
cvReleaseImage(&block3_img_o1);
cvReleaseImage(&block13_img_o1);
cvReleaseImage(&block13_img_i1);
cvReleaseImage(&block13_img_i2);
cvReleaseImage(&block2_img_o1);
cvReleaseImage(&block2_img_i1);
}
cvReleaseCapture(&block1_capture);
return 0;
 } //closing main()
