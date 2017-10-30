
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



#define MAIN_WINDOW_WIDTH 640
#define MAIN_WINDOW_HEIGHT 480
#define WORLD_HEIGHT 100
#define WORLD_WIDTH 100
#define WORLD_DEPTH 100



struct Vertex3D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
struct Face
{
    int verts[3];
};

typedef struct Face face;
typedef struct Vertex3D vertex3d;

vertex3d vertices[10000];
face faces[10000];

GLdouble eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ;
int vert_count;
int face_count;
int gl_mode;
float r,g,b;
 
void readObjectfromFile(const char* fn)
{
    
    // reads the object from an obj file and  puts it in the  LinkedList
    vert_count = 0;
    face_count = 0;
 
    char line[80];
    char magic;
    GLfloat p1, p2, p3;
    int a,b,c;

    FILE *ifp, *ofp;
    const char *mode = "r";
    ifp = fopen(fn,mode);
    if(ifp == NULL)
    {
        printf("can't open file %s\n",fn);
        return; 
    } 
    

    while(fgets(line,80,ifp))
    {
        magic = line[0];
        switch(magic)
        {
            case 'v':
                sscanf(line,"%s %f %f %f\n",&magic,&p1,&p2,&p3);
                printf("adding vertex %s\n",line);
                vertices[vert_count].x = p1;
                vertices[vert_count].y = p2;
                vertices[vert_count].z = p3;
                vert_count++;
            break;
            case 'f':
                sscanf(line,"%s %d %d %d\n",&magic,&a,&b,&c);
                printf("adding face %d\n",face_count);
            //    printf("%s\n",line);
                faces[face_count].verts[0] = a;
                faces[face_count].verts[1] = b;
                faces[face_count].verts[2] = c;
                face_count++;
            break;
            default:
            break;
        }
            
    }
    printf("added %d vertices\n",vert_count);
    printf("added %d faces\n",face_count);

    fclose(ifp);
    
    return; 
}


void loadWorld()
{
    printf("loadWorld called \n");
 
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r,g,b);
    glPolygonMode(GL_FRONT_AND_BACK,gl_mode);
    glBegin(GL_TRIANGLES);
    printf("loading %d faces\n",face_count);
        for(int i=0;i<face_count;i++)
        {
      //      printf("adding face %d:\n",i);
            face f = faces[i];
    //        printf("face loaded\n");
            for(int j=0;j<3;j++)
            {
            
                int index = f.verts[j] - 1;
  //              printf("index :%d\n",index);
                vertex3d v = vertices[index];
                GLfloat x,y,z;
                x = v.x;
                y = v.y;
                z = v.z;
 //               glNormal3f(0.0f,0.0f,1.0f);
                glVertex3f(x,y,z);
            }
        }
    glEnd();


}

void reshow()
{
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);
    glutPostRedisplay();
}
void getBounds()
{
    float min_X = 10.0f;
    float min_Y = 10.0f;
    float min_Z = 10.0f;
    float max_X = -10.0f;
    float max_Y = -10.0f;
    float max_Z = -10.0f;
    
    printf("vert_count = %d\n",vert_count);
    for(int i=0;i<vert_count;i++)
    {
        
        if(vertices[i].x > max_X)max_X = vertices[i].x;
        if(vertices[i].y > max_Y)max_Y = vertices[i].y;
        if(vertices[i].z > max_Z)max_Z = vertices[i].z;
        if(vertices[i].x < min_X)min_X = vertices[i].x;
        if(vertices[i].y < min_Y)min_Y = vertices[i].y;
        if(vertices[i].z < min_Z)min_Z = vertices[i].z;
    }
    printf("min_X = %f, max_X = %f\n",min_X,max_X);
    printf("min_Y = %f, max_Y = %f\n",min_Y,max_Y);
    printf("min_Z = %f, max_Z = %f\n",min_Z,max_Z);

        
}

void keyLeft(int key,int x,int  y)
{
    float onedeg = 2*M_PI/360;
    //float c = math.sqrt(eyeZ^2 + eyeX^2);
    
    float new_refZ = refZ*cos(onedeg) + refX*sin(onedeg);
    float new_refX = refX*cos(onedeg) - refZ*sin(onedeg);
    refZ = new_refZ;
    refX = new_refX;
    reshow();

}
void keyRight(int key,int x,int  y)
{
    float onedeg = -1*2*M_PI/360;
    printf("onedeg = %f\n",onedeg);

    float new_refZ = refZ*cos(onedeg) + refX*sin(onedeg);
    float new_refX = refX*cos(onedeg) - refZ*sin(onedeg);
    printf("refX = %f, refZ = %f\n",refX,refZ);
    printf("new_refX = %f, new_refZ = %f\n",new_refX,new_refZ);
    
    refZ = new_refZ;
    refX = new_refX;
    printf("refX = %f, refZ = %f\n",refX,refZ);

    reshow();
}
void keyUp(int key,int x,int  y)
{
 //   if(eyeZ >= WORLD_DEPTH * 0.8)return;
    eyeZ += 0.1f;

    reshow();
}
void keyDown(int key,int x,int  y)
{
  //  if(eyeZ <= 0.9)return;
    eyeZ -= 0.1f;
 
    reshow();
}
void wireframe()
{
    gl_mode = GL_LINE;
    reshow();
}
void solid()
{
    gl_mode = GL_FILL;
    reshow();
}
void point()
{
    gl_mode = GL_POINT;
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
    printf("vert_count = %d\n",vert_count);
    glClearColor(0.0,0.0,0.0,0.0);
 

  /* Use depth buffering for hidden surface elimination. */
   // glEnable(GL_DEPTH_TEST);

    //glClearDepth(1.0f);

    //glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_MODELVIEW);
    eyeX = 0.0f;
    eyeY = 0.0f;
    eyeZ = 1.0f;
    refX = 0.0f; 
    refY = 0.0f; 
    refZ = 0.0f; 
    upX = 0.0f; 
    upY = 1.0f; 
    upZ = 0.0f;
    gl_mode = GL_LINE;
    r = 0.0f;
    g = 1.0f;
    b = 0.0f;
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);

}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            wireframe();
            break;
        case 's':
            solid();
            break;
        case 'p':
            point();
            break;
        case 'r':
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            reshow();
            break;
        case 'b':
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
            reshow();
            break;
        case 'g':
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            reshow();
            break;
        case 'y':
            r = 1.0f;
            g = 1.0f;
            b = 0.0f;
            reshow();
            break;
        case 'm':
            r = 1.0f;
            g = 0.0f;
            b = 1.0f;
            reshow();
            break;
        case 'c':
            r = 0.0f;
            g = 1.0f;
            b = 1.0f;
            reshow();
            break;
        case 'a':
            r = 1.0f;
            g = 1.0f;
            b = 1.0f;
            reshow();
            break;
        case 'q':
            getBounds();
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
	glutCreateWindow ("Bunny");

    init();	
    glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (arrow_keys);

    /* instantiate other objects here
    */

	glutMainLoop ();
}

