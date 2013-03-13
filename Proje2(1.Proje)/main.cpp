//
//  main.cpp
//  Levent BUDAKOĞLU - 040080242 
//  Proje-2 dersi - 1. Projesi (Güneş Sistemi) 
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "imageloader.h"
#include <math.h>
GLfloat material_shininess[] = { 20 };
GLuint _textureId[6]; //The id of the texture
GLdouble angle = 0; 
GLfloat cameraangleY=0;
GLfloat targetcameraangleY = 0;
GLfloat cameraangleX=0;
GLfloat targetcameraangleX = 0;
GLuint sky_texture [6]; 

// SOIL kullanmadım, bulduğum bu loadTexture fonksiyonunu kullandım
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);   // değişiklik 13.03.2013
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   // değişiklik 13.03.2013
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}



// Hazır skybox örneğini denemek istedim, ancak tam olarak olmadı
void skybox (void) {
	float x = 0;
	float y = 0;
	float z = 0;
	float width  = 100;
	float height = 100;
	float length = 100;
	
	glBindTexture(GL_TEXTURE_2D, sky_texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
	glBegin(GL_QUADS);      
	    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z);
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, sky_texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin(GL_QUADS);  
	    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z + length);
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z + length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, sky_texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin(GL_QUADS);      

	    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y,  z + length);
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,  z + length); 
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, sky_texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin(GL_QUADS);      
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, sky_texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin(GL_QUADS);      
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z); 
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length); 
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z + length);
	    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);     

	glEnd();
	glBindTexture(GL_TEXTURE_2D, sky_texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin(GL_QUADS);  
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
	    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z + length);
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();
}

static void Key(unsigned char key, int x, int y)
{
    printf("%d", key);
	switch (key) {
		case 27: // ESC
			exit(0);
            		break;
        	case 'r': // r
            		cameraangleX = 0;
            		targetcameraangleX = 0;
            		cameraangleY = 0;
            		targetcameraangleY = 0;
            		break;  
	}
}

void SpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            targetcameraangleY+=45;
            break;
        case GLUT_KEY_RIGHT:
            targetcameraangleY-=45;
            break;
        case GLUT_KEY_UP:
            targetcameraangleX+=15;
            break;
        case GLUT_KEY_DOWN:
            targetcameraangleX-=15;
            break;
    }
}



static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);  // değişiklik
    //  Güneş çizdirme   //    // Güneş Texture ı başlangıçta gözüküyo, ancak ışıklandırma ile ilgili olarak farklı bir renge bürünüyor
    glPushMatrix();
    glDisable(GL_LIGHTING);    // değişiklik 13.03.2013 // skybox dan önce güneşte olduğu gibi ışıklandırma disable edilip camera rotasyonları verilmeli
    glRotated(cameraangleX, 1, 0, 0); // değişiklik 13.03.2013
    glRotated(cameraangleY, 0, 1, 0);  // değişiklik 13.03.2013
    skybox();      // skybox çizdirme
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glTranslatef(0.f, 0.f, -24.f);
    glRotated(cameraangleX, 1, 0, 0);
    glRotated(cameraangleY, 0, 1, 0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glRotatef(90,1.0f,0.0f,0.0f);     //kutupları ayarlamak için 90 derece döndür 
    gluQuadricTexture(quadric,1);
    gluSphere( quadric , 2 , 60 , 30 );    // küre
    glEnable(GL_LIGHTING);
    glPopMatrix();
    //  Güneş çizdirme   //

    //  Dünya çizdirme   //
    glPushMatrix();
    glRotated(angle*0.4, 0, 1, 0);
    glTranslatef(0.f, 0.f, -4.f);

    glBindTexture(GL_TEXTURE_2D, _textureId[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPushMatrix();
    glRotatef(90,1.0f,0.0f,0.0f);
    gluSphere( quadric , 0.6 , 60 , 30 );
    glPopMatrix();
    //  Dünya çizdirme   //

    //  Uydu 1 (Ay)      //
    glPushMatrix();
    glRotated(angle*1.2, 0, -1, 0);
    glTranslatef(0.f, 0.f, -1.f);
    
    glBindTexture(GL_TEXTURE_2D, _textureId[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPushMatrix();
    glRotatef(90,1.0f,0.0f,0.0f);
    gluSphere( quadric , 0.2 , 60 , 30 );
    glPopMatrix();
    //  Uydu 1 (Ay)      //
    glPopMatrix();

    //  Uydu 2 (Venüs)   //
    glPushMatrix();
    glRotated(angle*0.70, 0, 1, 0);
    glTranslatef(0.f, 0.f, -1.4f);
    
    glBindTexture(GL_TEXTURE_2D, _textureId[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPushMatrix();
    glRotatef(90,1.0f,0.0f,0.0f);
    gluSphere( quadric , 0.3 , 60 , 30 );
    glPopMatrix();
    //  Uydu 2 (Venüs)   //

    //  Mars çizdirme    //
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotated(angle*0.1, 0, 1, 0);
    glTranslatef(0.f, 0.f, -9.5f);

    glBindTexture(GL_TEXTURE_2D, _textureId[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPushMatrix();
    glRotatef(90,1.0f,0.0f,0.0f);
    gluSphere( quadric , 0.85 , 60 , 30 );
    glPopMatrix();
    //  Mars çizdirme    //

    //  Uydu 1 (Neptün)  //
    glPushMatrix();
    glRotated(angle*0.9, 0, -1, 0);
    glTranslatef(0.f, 0.f, -1.2f);

    glBindTexture(GL_TEXTURE_2D, _textureId[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPushMatrix();
    glRotatef(90,1.0f,0.0f,0.0f);
    gluSphere( quadric , 0.2 , 60 , 30 );
    glPopMatrix();
    //  Uydu 1 (Neptün)  //

    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    
}

static void timerCallback (int value)
{
 
    angle ++;
    GLfloat light_position[] = { 0.0, 0.0, 0.0 , 1.0 };
    GLfloat diff = targetcameraangleY - cameraangleY;
    if( abs(diff) > 0.000001)
    {
        cameraangleY += diff / 15;
    }
    diff = targetcameraangleX - cameraangleX;
    if( abs(diff) > 0.0001)
    {
        cameraangleX += diff / 15;
    }
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMateriali(GL_FRONT,GL_SHININESS, 3);
    glutTimerFunc(10, timerCallback, 0);
    glutPostRedisplay();
}

// Işıklandırma ayarları, Ders4 örneğinden
void setupLight(){
	Image* image = loadBMP("space.bmp");
	sky_texture[0] = loadTexture(image);; //load the texture
	sky_texture[1] = loadTexture(image);; //load the texture
	sky_texture[2] = loadTexture(image);; //load the texture
	sky_texture[3] = loadTexture(image);; //load the texture
	sky_texture[4] = loadTexture(image);; //load the texture
	sky_texture[5] = loadTexture(image);; //load the texture
	delete image; 

	glEnable(GL_TEXTURE_2D); //enable 2D texturing
	//glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	//glEnable(GL_TEXTURE_GEN_T);

	     image = loadBMP("sun.bmp");
	    _textureId[0] = loadTexture(image);
	    delete image;    

	    image = loadBMP("earth.bmp");
	    _textureId[1] = loadTexture(image);
	    delete image;

	image = loadBMP("Moon.bmp");
	    _textureId[2] = loadTexture(image);
	    delete image;

	    image = loadBMP("mars.bmp");
	    _textureId[3] = loadTexture(image);
	    delete image;

	    image = loadBMP("venus.bmp");
	    _textureId[4] = loadTexture(image);
	    delete image;

	    image = loadBMP("Neptune.bmp");
	    _textureId[5] = loadTexture(image);
	    delete image;


	    glEnable(GL_LIGHTING);
	    
	    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };  // point light
	    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	    
	    
	    glEnable(GL_LIGHT0);
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	    
	    GLfloat global_ambient[] = { 0.2,  0.2, 0.2, 1.0 };
	    
	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	    
	    glEnable(GL_COLOR_MATERIAL);
	    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	    
	    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	    GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	    
	    
	    glMaterialfv(GL_FRONT,GL_SPECULAR, material_specular);
	    glMaterialfv(GL_FRONT,GL_AMBIENT, material_ambient);
	    glMateriali(GL_FRONT,GL_SHININESS, 3);
	    
	    glShadeModel(GL_SMOOTH);
	}

int main (int argc, char ** argv)
{

    GLenum type;
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    type = GLUT_RGB;
    type |= GLUT_DOUBLE;
    type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
    glutInitDisplayMode(type);
    glutCreateWindow("Ders 2");
    
    glClearColor(0.0, 0.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);  //Derinlik 
    
    
    glMatrixMode(GL_PROJECTION);
    gluPerspective(55, 800/600, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    
    setupLight();    //Işıklandırma ayarları, ve texture yükleme 
    timerCallback(0);
    glutKeyboardFunc(Key);
    glutSpecialFunc(SpecialKey);
    glutDisplayFunc(Draw);
    glutMainLoop();
    
    return 0;
}

