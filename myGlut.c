#include <GL/glut.h>

void glutBitmapString(void *font, char *string)
{
	for(int i = 0; string[i]!='\0';i++)
		glutBitmapCharacter(font, string[i]);
}