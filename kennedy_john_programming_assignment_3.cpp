
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"

#include <string.h>



#define MAIN_WINDOW_WIDTH 400
#define MAIN_WINDOW_HEIGHT 600
#define WORLD_HEIGHT 100
#define WORLD_WIDTH 100
#define WORLD_DEPTH 100

struct Vertex3D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
struct triangle
{
    int aindex;
    int bindex;
    int cindex;
};

struct gobj
{
    LinkedList* vertices;
    LinkedList* triangles;
};

GLdouble eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ;

gobj obj; 

void readObjectfromFile(const char* fn)
{
    
    // reads the object from an obj file and  puts it in the  LinkedList
    
    char line[80];
    float p1, p2, p3;
    FILE *ifp, *ofp;
    const char *mode = "r";
    ifp = fopen(fn,mode);
    if(ifp == NULL)
    {
        printf("can't open file %s\n",fn);
        return; 
    } 
 
    obj.vertices = createLinkedList();
    obj.triangles = createLinkedList();
    

    while(fscanf(ifp,"%s %f %f %f",line,&p1,&p2,&p3) != EOF)
    {
        printf("%s %f %f %f\n",line,p1,p2,p3);
        if(strcmp(line,"v") == 0)
        {
            
        }
        if(strcmp(line,"f") == 0)
        {
            printf("it's a face!\n");
        }
        if(strcmp(line,"f") != 0 && strcmp(line,"v") != 0)
        {
            printf("we dont' know what it is!\n");
        }
    }
    
    fclose(ifp);

//            char* item = strtok(line," ");
    return; 
}


void loadWorld()
{
    printf("loadWorld called \n");

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
/*    
        // fix this to add and re-add verts to make the strip
        for(int i=0;i<WORLD_DEPTH - 1;i++)
        {
            for(int j=0;j< WORLD_WIDTH - 1;j++)
            {
                int pos = 0;

                pos = i*WORLD_DEPTH +j;
                glVertex3f(world[pos][0],world[pos][1],world[pos][2]);
             //   printf("loading vertex %f,%f,%f\n",world[pos][0],world[pos][1],world[pos][2]);
                
                pos = (i+1)*WORLD_DEPTH +j;
                glVertex3f(world[pos][0],world[pos][1],world[pos][2]);                
             //   printf("loading vertex %f,%f,%f\n",world[pos][0],world[pos][1],world[pos][2]);

                pos = (i)*WORLD_DEPTH +j + 1;
                glVertex3f(world[pos][0],world[pos][1],world[pos][2]);                
             //   printf("loading vertex %f,%f,%f\n",world[pos][0],world[pos][1],world[pos][2]);

                pos = (i+ 1)*WORLD_DEPTH +j;
                glVertex3f(world[pos][0],world[pos][1],world[pos][2]);
               // printf("loading vertex %f,%f,%f\n",world[pos][0],world[pos][1],world[pos][2]);

                pos = (i + 1)*WORLD_DEPTH +j + 1;
                glVertex3f(world[pos][0],world[pos][1],world[pos][2]);
             //   printf("loading vertex %f,%f,%f\n",world[pos][0],world[pos][1],world[pos][2]);

                pos = i*WORLD_DEPTH +j + 1;
                glVertex3f(world[pos][0],world[pos][1],world[pos][2]);
             //   printf("loading vertex %f,%f,%f\n",world[pos][0],world[pos][1],world[pos][2]);
            }
                // printf("loading vertex %f,%f,%f\n",world[i][0],world[i][1],world[i][2]);
        }
*/     
    glEnd();
    glFlush();


}

void reshow()
{
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);
    glutPostRedisplay();
}

void keyLeft(int key,int x,int  y)
{
    if(eyeX >= WORLD_WIDTH - 1.0)return;
    eyeX += 1.0f;
    refX += 1.0f;
    reshow();

}
void keyRight(int key,int x,int  y)
{
    if(eyeX <= 0.9)return;
    eyeX -= 1.0f;
    refX -= 1.0f;
    reshow();
}
void keyUp(int key,int x,int  y)
{
    if(eyeZ >= WORLD_DEPTH * 0.8)return;
    eyeZ += 1.0f;
    refZ += 1.0f;
    reshow();
}
void keyDown(int key,int x,int  y)
{
    if(eyeZ <= 0.9)return;
    eyeZ -= 1.0f;
    refZ -= 1.0f;
    reshow();
}
void cameraUp()
{
    if(eyeY >= WORLD_HEIGHT * 0.9)return;
    eyeY += 1.0f;
    refY += 1.0f;
    reshow();
}
void cameraDown()
{
    if(eyeY <=2)return;
    eyeY -= 1.0f;
    refY -= 1.0f;
    reshow();
}
void toggleup()
{
    if(upY == 0.0f)
    {
        upY++;
        upZ = 0;
        
    }
    else
    {
        upY = 0.0f;
        upZ++;
        eyeY = 40.0f;
        eyeX = 5.0f;
        eyeZ = 5.0f;
        refY = 0.0f;        
        refX = 5.0f;
        refZ = 5.0f;
    }       
    reshow();
}

void arrow_keys (int key, int x, int y)
{
 
    switch (key)
    {
        case GLUT_KEY_LEFT:
            keyLeft(key,x,y);            
            break;
        case GLUT_KEY_RIGHT:
            keyRight(key,x,y);
            break;
        case GLUT_KEY_UP:
            keyUp(key,x,y);            
            break; 
        case GLUT_KEY_DOWN:
            keyDown(key,x,y);            
            break;
        default:
            break;
    }
    printf("arrow key = %c, x = %d, y = %d\n",key,x,y);

}
void init(void)
{
    printf("init called\n");
    glClearColor(0.0,0.0,0.0,0.0);
    //glClearDepth(1.0f);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_MODELVIEW);
    eyeX = WORLD_WIDTH * 0.5f;
    eyeY = 5.0f;
    eyeZ = 0.0f;
    refX = WORLD_WIDTH * 0.5f; 
    refY = 5.0f; 
    refZ = WORLD_DEPTH * 0.5f; 
    upX = 0.0f; 
    upY = 1.0f; 
    upZ = 0.0f;
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);

}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
            cameraUp();
            break;
        case 'z':
            cameraDown();
            break;
        case 't':
            toggleup();
            break;
        default:
            break;
    }
    printf("keyboard key = %c, x = %d, y = %d\n",key,x,y);
}
void display()
{
    printf("display called\n");
    glClear(GL_COLOR_BUFFER_BIT);

    loadWorld();
    glFlush();
    glutSwapBuffers();

    
    
}


void reshape(int width, int height)
{
    printf("reshape called.\n");
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) width/(GLfloat)height;
    gluPerspective(45.0f,aspect, 0.1f,100.0f);  
    glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char *argv[])
{  
    readObjectfromFile("bunny.obj");
    //buildWorld(WORLD_WIDTH,WORLD_HEIGHT,WORLD_DEPTH);
    //loadWorld();

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("Flying camera");

    init();	
    glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (arrow_keys);

    /* instantiate other objects here
    */

	glutMainLoop ();
}

