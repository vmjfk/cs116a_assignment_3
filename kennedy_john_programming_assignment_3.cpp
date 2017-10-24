
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAIN_WINDOW_WIDTH 400
#define MAIN_WINDOW_HEIGHT 600
#define WORLD_WIDTH 100
#define WORLD_HEIGHT 10
#define WORLD_DEPTH 100
#define TOTAL_VECTORS WORLD_WIDTH*WORLD_DEPTH

typedef GLfloat Vectorf [3];

Vectorf world[TOTAL_VECTORS]; 
GLdouble eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ;

void buildWorld(int x, int y, int z)
{

    for(int i = 0; i<z;i++)
    {
        for(int j = 0;j<x;j++)
        {
            world[j*x+i][0] = float(i);
            world[j*x+i][1] = float(rand())/float(RAND_MAX);
            world[j*x+i][2] = float(j);
        }
    }


/*
    int worldptr = 0;
    GLfloat zptr, xptr = 0.0f; 
    Vectorf verts[6];
    while(zptr < z)
    {
        
        // put in the first triangle vectors
 /*       verts[0][0] = xptr;
        verts[0][1] = float(rand())/float(RAND_MAX);
        printf("y = %f\n",verts[0][1]);
        verts[0][2] = zptr;
        verts[1][0] = xptr + 1;
        verts[1][1] = float(rand())/float(RAND_MAX); //need to make this random Y
        verts[1][2] = zptr;
  
        verts[2][0] = xptr;
        verts[2][1] = float(rand())/float(RAND_MAX); //Y coordinate
        verts[2][2] = zptr + 1;
 /*       
        //second triangle
        verts[3][0] = xptr + 1;
        verts[3][1] = float(rand())/float(RAND_MAX); // Y
        verts[3][2] = zptr + 1.0f;
/*
        verts[4][0] = xptr;
        verts[4][1] = 0.0f; // Y
        verts[4][2] = zptr;
        verts[5][0] = xptr + 1.0;
        verts[5][1] = 0.0f; // Y
        verts[5][2] = zptr;

        // put vectors in world
        for(int i = 0;i<2;i++)
        {
            if(verts[i][0] >= 0.0f)
            {
                printf("x = %f, y = %f, z = %f\n",verts[i][0],verts[i][1],verts[i][2]);
                world[worldptr][0] = verts[i][0];
                world[worldptr][1] = verts[i][1];
                world[worldptr][2] = verts[i][2];
                worldptr++;
            }
        }

        // increment xptr 
        xptr++; 
        
        // set x and z ptr within bounds
        if(xptr == x)
        {
            xptr = 0; 
            zptr++;
        }
    }
    
    printf("final worldptr = %d\n",worldptr);
*/
}
void loadWorld()
{
    printf("loadWorld called \n");

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
        
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
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //triangle();
    //buildWorld(WORLD_WIDTH,WORLD_HEIGHT,WORLD_DEPTH);
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
    buildWorld(WORLD_WIDTH,WORLD_HEIGHT,WORLD_DEPTH);
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

