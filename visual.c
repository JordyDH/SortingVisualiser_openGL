#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define AANTAL 100
#define MAXVAL 1000
#define LIVEVIEW
#define DELAY	5

int sort_array[AANTAL];
int g_xPadding	= 0;
int g_yPadding	= 0;
int g_menuId	= 0;

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

void sortSelectie();


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
		glColor3f((float)(i)/(AANTAL),0,1.0 - (float)(i+1)/(AANTAL));
		glRecti(i+g_xPadding,g_yPadding,i+1+g_xPadding,sort_array[i]+g_yPadding);
	}
}


void menu(int num)
{
	printf("%d\n",num);
	switch(num)
	{
		case 1:
			sortSelectie();
			break;
		case 2:
			break;
		case 3:
			break;
	}
	//glutPostRedisplay();
}

void createMenu(void)
{
	g_menuId = glutCreateMenu(menu);
	glutAddMenuEntry("sortSelectie",1);
	glutAddMenuEntry("---",2);
	glutAddMenuEntry("---",3);
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
		for(j = i+1; j < AANTAL; j++)
		{
			if(sort_array[j] < x)
			{
				x = sort_array[j];
				k = j;
			}
		}
		sort_array[k] = sort_array[i];
		sort_array[i] = x;
		#ifdef LIVEVIEW
		delay(DELAY);
		//glutPostRedisplay();
		displayFcn();
		#endif
	}
}
