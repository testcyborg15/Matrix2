#include <windows.h>
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"

#include <time.h> 
#include <vector>
#include "Math3D.h"
#include "Vector4D.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

#include <stdlib.h>
#include <crtdbg.h>



#define KEY_ESCAPE 27


typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;


///ARC MOUSE
int iXMouse = 0;
int iYMouse = 0;
int iXMousePrev = 0;
int iYMousePrev = 0;
float fDx = 45.0f;
float fDy = 0.0f;

float g_fRadius = 10.0f; 
bool bDragView = false;
///

bool bPick = false;
int iMousePosX = 0;
int iMousePosY = 0;


float fXPos = 0.0f;
float fYPos = 0.0f;

bool bBankLeft = false;
bool bBankRight = false;
bool bLeft = false;
bool bRight = false;
bool bUp = false;
bool bDown = false;

//test
float fAlpha = 0.0f;
float fBeta = 0.0f;

//time
float dt;
DWORD dwTicks = GetTickCount(), dwNewTicks;

CMatrix4x4 m;
CMatrix4x4 m1;

unsigned int sizeS = 20;
vector<CMatrix4x4> step;
vector<CMatrix4x4> step1;

//sialalala

void InitMarker()
{
	m.Identity();

	CMatrix4x4 mT, mT1;
	mT.ZRotate( 0.087 );
	mT1.XRotate( 0.047 );
	for ( unsigned int id = 0; id < sizeS; ++id )
	{
		m = mT * mT1 * m;

		step.push_back( m );
	}

	m1.YRotate( 0.78 );

	
	for ( unsigned int id = 0; id < sizeS; ++id )
	{
		m1 = mT * mT1 * m1;

		step1.push_back( m1 );
	}
}

void DrawMarker()
{
	CMatrix4x4 mT, mT1;
	mT.YRotate( 0.78 );
	/*
	glColor3f( 1.0f, 1.0f, 0.0f );
	for ( unsigned int id = 0; id < size; ++id )
	{
		glPushMatrix();
		mT1 = step[id] * mT;		
		glMultMatrixd( mT1.Arr );
		
		glBegin( GL_LINES );
		glVertex3f( 0, 0, 0 );
		glVertex3f( 1, 0, 0 );
		glEnd();
		
		glPopMatrix();
	}
	*/
	glColor3f( 1.0f, 1.0f, 0.0f );
	for ( unsigned int id = 0; id < sizeS; ++id )
	{
		glPushMatrix();		
		glMultMatrixd( step1[id].Arr );		
		
		glBegin( GL_LINES );
		glVertex3f( 0, 0, 0 );
		glVertex3f( 1, 0, 0 );
		glEnd();
		
		glPopMatrix();
	}

	glColor3f( 0.0f, 1.0f, 1.0f );
	for ( unsigned int id = 0; id < sizeS; ++id )
	{
		glPushMatrix();		
		glMultMatrixd( step[id].Arr );		
		
		glBegin( GL_LINES );
		glVertex3f( 0, 0, 0 );
		glVertex3f( 1, 0, 0 );
		glEnd();
		
		glPopMatrix();
	}
}

void logic(float dt)
{	
}


void display() 
{
	dwNewTicks = GetTickCount();
	dt = dwNewTicks > dwTicks ? (dwNewTicks - dwTicks) / 1000.0f : 0.0f;
	dwTicks = dwNewTicks;

	logic( dt );
			
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     
	glLoadIdentity();
 
	// Define a viewing transformation
	//gluLookAt( 50.01f, 150.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);					  
	gluLookAt( g_fRadius*cos(fDx*fPI/180.0f)*cos(fDy*fPI/180.0f), g_fRadius*sin(fDx*fPI/180.0f), g_fRadius*cos(fDx*fPI/180.0f)*sin(fDy*fPI/180.0f), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	//-----------------------------------
	//			DRAWING
	//-----------------------------------	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);	
	glDisable(GL_DEPTH_TEST);
	//DRAW UCS
	glBegin(GL_LINES);
	//X "red"
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	//Y "green"
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	//Z "blue"
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
			
	DrawMarker();	
	
	
	glutSwapBuffers();
}


void initialize () 
{
   // select projection matrix
	glMatrixMode(GL_PROJECTION);												
 
	// set the viewport
	glViewport(0, 0, win.width, win.height);									
 
	// set matrix mode
	glMatrixMode(GL_PROJECTION);												
 
	// reset projection matrix
	glLoadIdentity();															
	GLfloat aspect = (GLfloat) win.width / win.height;
 
	// set up a perspective projection matrix
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		
 
	// specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);													
	glShadeModel( GL_SMOOTH );
 
	// specify the clear value for the depth buffer
	glClearDepth( 1.0f );														
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
 
	// specify implementation-specific hints
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						
 
	GLfloat amb_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat specular[] = { 0.7f, 0.7f, 0.3f, 1.0f };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_MULTISAMPLE);

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		std::cout<<"Ready for OpenGL 2.0\n"<<std::endl;
	else {
		std::cout<<"OpenGL 2.0 not supported\n"<<std::endl;
		exit(1);
	}

	InitMarker();	

	
}

void mouseWheel( int wheel, int direction, int x, int y )
{
	g_fRadius -= direction;
}

void mouseMove(int x, int y)
{	
	//normal
	if(bDragView)
	{
		iXMouse = x;
		iYMouse = y;	
		fDy += (iXMousePrev - iXMouse) * 0.1f;
		if(fDx + (iYMousePrev - iYMouse) * 0.1f < 90.0f && fDx + (iYMousePrev - iYMouse) * 0.1f > -90.0f)
			fDx += (iYMousePrev - iYMouse) * 0.1f;
		iYMousePrev = iYMouse;
		iXMousePrev = iXMouse;
	}	
}

void mouse(int button, int state, int x, int y)
{
	if ((button == GLUT_RIGHT_BUTTON)) // It's a wheel event
	{
		if(state == GLUT_DOWN)
		{
			iXMouse = x;
			iYMouse = y;
			iXMousePrev = x;
			iYMousePrev = y;
			bDragView = true;
			
			//do dodawania ksztaltu
			
											
		}
		else
			bDragView = false;
	}

	if ((button == GLUT_LEFT_BUTTON))
	{
		if(state == GLUT_DOWN)
		{
			iMousePosX = x;
			iMousePosY = y;
			bPick = true;
		}
	}
}

void keyboardDown ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch ( key ) 
	{
		case KEY_ESCAPE:        
			exit ( 0 );   
		break;      
			
		case 'q':
			bLeft = true;
		break;

		case 'e':
			bRight = true;
		break;
		
		case 'a':
			bBankLeft = true;
		break;

		case 'd':
			bBankRight = true;
		break;

		case 'w':
			bUp = true;
		break;

		case 's':
			bDown = true;
		break;
				
		default:      
		break;
	}
}

void keyboardUp ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch ( key ) 
	{
		case 'q':
			bLeft = false;
		break;

		case 'e':
			bRight = false;
		break;

		case 'a':
			bBankLeft = false;
		break;

		case 'd':
			bBankRight = false;
		break;
		
		case 'w':
			bUp = false;
		break;

		case 's':
			bDown = false;
		break;
				
		default:      
		break;
	}
}

int main(int argc, char **argv) 
{
	//for debug and memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

	// set window values
	win.width = 800;
	win.height = 600;
	win.title = "Terrain-Tools by Jacek Cichy";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 1500.0f;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );  // Display Mode
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE );  // Display Mode
	glutInitWindowSize(win.width,win.height);				// set window size
	glutCreateWindow(win.title);					// create Window
	glutDisplayFunc(display);						// register Display Function
	glutIdleFunc( display );						// register Idle Function
	glutKeyboardFunc( keyboardDown );						// register Keyboard Handler
	glutKeyboardUpFunc( keyboardUp );
	//glutSpecialFunc( keyboardArrow );						// register Keyboard Handler
	glutMouseFunc( mouse );						// register Mouse Handler
	glutMotionFunc( mouseMove );					//callback dla ruchu myszy z wcisnietymi przyciskami
	//glutPassiveMotionFunc( mouseMove2 );
	glutMouseWheelFunc( mouseWheel );			//rolka
	glutSetOption(GLUT_MULTISAMPLE, 8);

	initialize();		
	glutMainLoop();							// run GLUT mainloop
	
	//czyszczenie po sobie
	//for(unsigned int ID=0; ID<vpDecals.size(); ++ID)
	//	delete vpDecals[ID];

	return 0;
}
