#define GL_SILENCE_DEPRECATION

#include <bits/stdc++.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std; 

float leftEdge[500], rightEdge[500], flag=0;

void myInit()
{
	gluOrtho2D(0, 500, 0, 500); 
} 

//Store all the Edge point for each scan line
void objectpoints(float x0, float y0, float x1, float y1)
{
	float temp, start, slop;
	int i;

	if(y0 > y1) //Swap when leftEdge is greater than rightEdge
	{
		swap(y0, y1);
		swap(x0, x1);
	}
 
	if(y0 == y1)  //Get the slope
	   slop = x0-x1; //Slope at vertex
	else 
	   slop = (x1-x0)/(y1-y0); //Slope for line

	start = x0; //Initial X value

	for(i = y0; i <= y1; i++) //To get leftEdge & rightEdge
	{
      if(start < leftEdge[i])
	  { 
	    leftEdge[i] = start;
	  }	
	  if(start > rightEdge[i])
	  {
        rightEdge[i] = start;
	  }
	    
	  start += slop;
	}      
}

void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
		
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);

	//Draw the lines of polygon
	glVertex2f(100, 50);
	glVertex2f(50, 300);
	glVertex2f(250, 400);
	glVertex2f(450, 300);
	glVertex2f(400, 50);
	glEnd();

	for(int i = 0; i < 500; i++)
	{
		leftEdge[i] = 500;
		rightEdge[i] = 0;
	} 
    
	//To find the leftEdge and rightEdge for each scan
    objectpoints(100, 50, 50, 300);
	objectpoints(50, 300, 250, 400);
	objectpoints(250, 400, 450, 300);
	objectpoints(450, 300, 400, 50);
	objectpoints(400, 50, 100, 50);

	if (flag == 1) //Fill polygon
	{
		for (int i = 0; i < 500; i++) //Total of 500 scan lines
		{
			if (leftEdge[i] < rightEdge[i]) 
			{
				for (int j = leftEdge[i]; j < rightEdge[i]; j++) //To print the point on the scan line of
				{                                                //polygon
					if(i<150)
					glColor3f(0, 1, 0);
					else if(i>150 && i<300)
					glColor3f(1,1,1);
					else
					glColor3f(1.0,0.5,0);
					glBegin(GL_POINTS);
					glVertex2f(j, i);
					glEnd();
				}
			}
			glFlush();
		}
	}
	glFlush();
}


void ScanMenu(int choice)  //Chose option to fill or clear menu
{
	if(choice == 1) //Fill
	  flag = 1;
	else 
	if(choice == 2) //Clear
	  flag = 0;
	else 
      exit(0);
		
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("scanline Fill");
	myInit();
	glutDisplayFunc(display);
	glutCreateMenu(ScanMenu);
	glutAddMenuEntry("scanline fill", 1);
	glutAddMenuEntry("clear", 2);
	glutAddMenuEntry("exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}