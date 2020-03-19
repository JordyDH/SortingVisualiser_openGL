#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define AANTAL 200
#define MAXVAL 255
#define LIVEVIEW
#define FASTVIEW
#define DELAY	10

int sort_array[AANTAL];
int g_xPadding	= 0;
int g_yPadding	= 0;
int g_menuId	= 0;

int g_cursor0 = -1;
int g_cursor1 = -1;

int xmin, xmax = 0;
int ymin, ymax = 0;

GLint winWidth = 800, winHeight = 800;

void init(void);
void winReshapeFcn(GLint newWidth, GLint newHeight);
void displayFcn(void);
void drawStaaf();
void menu(int num);
void createMenu(void);
void fillarray();
void delay(int x);
void cleanCursor();

void sortSelectie();
void sortInvoegen();
void sortBubble();


void cleanCursor()
{
	g_cursor0 = -1;
	g_cursor1 = -1;
	displayFcn();
}

void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);  /* window color white */
	g_xPadding = AANTAL * 0.2;
	g_yPadding = MAXVAL * 0.05;
	xmax  = AANTAL + (g_xPadding * 2);
	ymax  = MAXVAL + (g_yPadding * 2);
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport (0,0,newWidth,newHeight);
	gluOrtho2D(xmin,xmax,ymin,ymax);
    	winWidth = newWidth;
    	winHeight = newHeight;
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);    /* clear display window */
	drawStaaf();
	glFlush();
}

int main (int argc,char* argv[])
{
	//Read data from file
	printf("\nAantal elements :%d \n",AANTAL);
	printf("Max value : %d\n",MAXVAL);
	fillarray();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);  /* top left corner */
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("VisualSorter 0.1");
	init();
	createMenu();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();

	return 0;
}

void drawStaaf()
{
	int last_y = 0;
	for(int i = 0; i < AANTAL ; i++)
	{
		if(i == g_cursor0)
			glColor3f(1.0,1.0,0);
		else if(i == g_cursor1)
			glColor3f(0,0,0);
		else glColor3f((float)(i)/(AANTAL),0,1.0 - (float)(i+1)/(AANTAL));
		glRecti(i+g_xPadding,g_yPadding,i+1+g_xPadding,sort_array[i]+g_yPadding);
	}
}


void menu(int num)
{
	printf("%d\n",num);
	switch(num)
	{
		case 0:
			fillarray();
			displayFcn();
			break;
		case 1:
			sortSelectie();
			break;
		case 2:
			sortInvoegen();
			break;
		case 3:
			sortBubble();
			break;
	}
	//glutPostRedisplay();
}

void createMenu(void)
{
	g_menuId = glutCreateMenu(menu);
	glutAddMenuEntry("refill array",0);
	glutAddMenuEntry("sortSelectie",1);
	glutAddMenuEntry("sortInvoegen",2);
	glutAddMenuEntry("sortBubble",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void fillarray()
{
	printf("Filling array with random values\n");
	for(int i = 0; i < AANTAL; i++)
	{
		sort_array[i] = round(rand()%MAXVAL);
	}
}

void delay(int x) 
{
    // Storing start time 
    clock_t start_time = clock(); 

    // looping till required time is not achieved 
    while (clock() < start_time + x) ; 
}

//SORTING ALGO'S
void sortSelectie()
{
	printf("Algo: sortSelectie\n");
	int i, j, k;
	int x;
	for(i = 0; i < AANTAL; i++)
	{
		x = sort_array[i];
		k = i;
		g_cursor0 = i;
		for(j = i+1; j < AANTAL; j++)
		{
			g_cursor1 = j;
			if(sort_array[j] < x)
			{
				x = sort_array[j];
				k = j;
			}
			#ifdef LIVEVIEW
			displayFcn();
			#ifndef FASTVIEW
			delay(DELAY);
			#endif
			#endif
		}
		sort_array[k] = sort_array[i];
		sort_array[i] = x;
		#ifdef LIVEVIEW
		delay(DELAY);
		displayFcn();
		#endif
	}
	cleanCursor();
}

void sortInvoegen()
{
	printf("Algo sortInvoegen\n");
	int i, j;
	int x;
	for(i = 1; i < AANTAL; i++)
	{
		g_cursor0 = i;
		x = sort_array[i];
		j = i - 1;
		while(x < sort_array[j])
		{
			g_cursor1 = j;
			sort_array[j+1] = sort_array[j];
			j--;

			#ifdef LIVEVIEW
			displayFcn();
			#ifndef FASTVIEW
			delay(DELAY);
			#endif
			#endif
		}
		sort_array[j+1] = x;

		#ifdef LIVEVIEW
		delay(DELAY);
		displayFcn();
		#endif
	}
	cleanCursor();

}

void sortBubble()
{
	int i, j;
	int x;

	for(i = 1; i < AANTAL; i++)
	{
		for(j=AANTAL; j >= i; j--)
		{
			g_cursor0 = i;
			if(sort_array[j-1] > sort_array[j])
			{
				g_cursor1 = j;
				x = sort_array[j-1];
				sort_array[j-1] = sort_array[j];
				sort_array[j] = x;
			}
			#ifdef LIVEVIEW
			displayFcn();
			#ifndef FASTVIEW
			delay(DELAY);
			#endif
			#endif
		}
		#ifdef LIVEVIEW
		//delay(DELAY);
		displayFcn();
		#endif
	}
	cleanCursor();

}


