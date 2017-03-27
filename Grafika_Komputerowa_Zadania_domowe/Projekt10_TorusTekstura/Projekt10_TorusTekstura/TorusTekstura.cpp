/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/
#define _USE_MATH_DEFINES
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <gl/gl.h>
#include <gl/glut.h>
using namespace std;

#define N 50
typedef float point3[3];
typedef float point2[2];
double PI = M_PI;
int model = 1;
float skala = 1.0f;
double tab1[N][N][3];
double tab2[N][N][3];
double tab3[N][N][3];
double tab4[N][N][3];
double tab5[N][N][3];
double tab6[N][N][3];
double tab7[N][N][3];
double tab8[N][N][3];
double tabN1[N][N][3];
double tabN2[N][N][3];
double tabN3[N][N][3];
double tabN4[N][N][3];
double tabN5[N][N][3];
double tabN6[N][N][3];
double tabN7[N][N][3];
double tabN8[N][N][3];
point2 tex[N][N];
/*point2 tex2[N][N];
point2 tex3[N][N];
point2 tex4[N][N];
point2 tex5[N][N];
point2 tex6[N][N];
point2 tex7[N][N];
point2 tex8[N][N];*/
static GLfloat theta1[] = { 0.0, 0.0, 0.0 };
float R = 1;
float r = 0.3;

//////////////////
static GLfloat	fi[2] = { 5.76f, 1.05f }, theta[2] = { 4.68f, 4.68f };// k�ty obrotu, elewacja i azymut DODANE
static GLfloat	pix2angle_x = 0.0, pix2angle_y = 0.0;	// przelicznik pikseli na stopnie
static GLfloat pix2angley;
float lightsR = 10.0;	//Promien sfery swiatel	DOD
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
static GLfloat phi = 0.0;   // k�t obrotu obiektu
static GLfloat pix2angle;     // przelicznik pikseli na stopnie
static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;		// poprzednia pozycja kursora myszy
static int delta_x = 0;        // r�nica pomi�dzy pozycj� bie��c� // i poprzedni� kursora myszy 
static int delta_y = 0;        // r�nica pomi�dzy pozycj� bie��c�
//////////////////
static GLint status = 0;      // stan klawiszy myszy
// 0 - nie naci�ni�to �adnego klawisza
// 1 - naci�ni�ty zosta� lewy klawisz
/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{

	/*************************************************************************************/

	// Struktura dla nag��wka pliku  TGA


#pragma pack(1)           
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)


	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;

	// Warto�ci domy�lne zwracane w przypadku b��du

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	fopen_s(&pFile, FileName, "rb");
	if (pFile == NULL)
		return NULL;

	/*************************************************************************************/

	// Przeczytanie nag��wka pliku

	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);


	/*************************************************************************************/

	// Odczytanie szeroko�ci, wysoko�ci i g��bi obrazu

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;


	/*************************************************************************************/

	// Sprawdzenie, czy g��bia spe�nia za�o�one warunki (8, 24, lub 32 bity)

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	/*************************************************************************************/

	// Obliczenie rozmiaru bufora w pami�ci


	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;


	/*************************************************************************************/

	// Alokacja pami�ci dla danych obrazu


	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}


	/*************************************************************************************/

	// Ustawienie formatu OpenGL


	switch (sDepth)

	{

	case 3:

		*ImFormat = GL_BGR_EXT;

		*ImComponents = GL_RGB8;

		break;

	case 4:

		*ImFormat = GL_BGRA_EXT;

		*ImComponents = GL_RGBA8;

		break;

	case 1:

		*ImFormat = GL_LUMINANCE;

		*ImComponents = GL_LUMINANCE8;

		break;

	};



	fclose(pFile);



	return pbitsperpixel;

}


	/*************************************************************************************/

/*void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0, 5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0, 5.0 };
	//  pocz�tek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();

}*/

/*************************************************************************************/

void Torus()
{
	Sleep(10);
	for (int i = 0; i < N / 2 - 1; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN1[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab1[i][j]);
			glNormal3dv(tabN1[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab1[i + 1][j]);
			glNormal3dv(tabN1[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab1[i][j + 1]);
			glNormal3dv(tabN1[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab1[i + 1][j]);
			glNormal3dv(tabN1[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab1[i][j + 1]);
			glNormal3dv(tabN1[i + 1][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab1[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN2[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab2[i][j]);
			glNormal3dv(tabN2[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab2[i + 1][j]);
			glNormal3dv(tabN2[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab2[i][j + 1]);
			glNormal3dv(tabN2[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab2[i + 1][j]);
			glNormal3dv(tabN2[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab2[i][j + 1]);
			glNormal3dv(tabN2[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab2[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN3[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab3[i][j]);
			glNormal3dv(tabN3[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab3[i + 1][j]);
			glNormal3dv(tabN3[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab3[i][j + 1]);
			glNormal3dv(tabN3[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab3[i + 1][j]);
			glNormal3dv(tabN3[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab3[i][j + 1]);
			glNormal3dv(tabN3[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab3[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN4[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab4[i][j]);
			glNormal3dv(tabN4[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab4[i + 1][j]);
			glNormal3dv(tabN4[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab4[i][j + 1]);
			glNormal3dv(tabN4[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab4[i + 1][j]);
			glNormal3dv(tabN4[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab4[i][j + 1]);
			glNormal3dv(tabN4[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab4[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN5[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab5[i][j]);
			glNormal3dv(tabN5[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab5[i + 1][j]);
			glNormal3dv(tabN5[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab5[i][j + 1]);
			glNormal3dv(tabN5[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab5[i + 1][j]);
			glNormal3dv(tabN5[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab5[i][j + 1]);
			glNormal3dv(tabN5[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab5[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN6[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab6[i][j]);
			glNormal3dv(tabN6[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab6[i + 1][j]);
			glNormal3dv(tabN6[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab6[i][j + 1]);
			glNormal3dv(tabN6[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab6[i + 1][j]);
			glNormal3dv(tabN6[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab6[i][j + 1]);
			glNormal3dv(tabN6[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab6[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN7[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab7[i][j]);
			glNormal3dv(tabN7[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab7[i + 1][j]);
			glNormal3dv(tabN7[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab7[i][j + 1]);
			glNormal3dv(tabN7[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab7[i + 1][j]);
			glNormal3dv(tabN7[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab7[i][j + 1]);
			glNormal3dv(tabN7[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab7[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN8[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab8[i][j]);
			glNormal3dv(tabN8[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab8[i + 1][j]);
			glNormal3dv(tabN8[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab8[i][j + 1]);
			glNormal3dv(tabN8[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab8[i + 1][j]);
			glNormal3dv(tabN8[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab8[i][j + 1]);
			glNormal3dv(tabN8[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab8[i + 1][j + 1]);
			glEnd();
		}
	}
	for (int i = N / 2 - 1; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN1[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab1[i][j]);
			glNormal3dv(tabN1[i + 1][j]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab1[i + 1][j]);
			glNormal3dv(tabN1[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab1[i + 1][j + 1]);
			glNormal3dv(tabN1[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab1[i][j]);
			glNormal3dv(tabN1[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab1[i][j + 1]);
			glNormal3dv(tabN1[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab1[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN2[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab2[i][j]);
			glNormal3dv(tabN2[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab2[i + 1][j]);
			glNormal3dv(tabN2[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab2[i + 1][j + 1]);
			glNormal3dv(tabN2[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab2[i][j]);
			glNormal3dv(tabN2[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab2[i][j + 1]);
			glNormal3dv(tabN2[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab2[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN3[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab3[i][j]);
			glNormal3dv(tabN3[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab3[i + 1][j]);
			glNormal3dv(tabN3[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab3[i + 1][j + 1]);
			glNormal3dv(tabN3[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab3[i][j]);
			glNormal3dv(tabN3[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab3[i][j + 1]);
			glNormal3dv(tabN3[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab3[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN4[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab4[i][j]);
			glNormal3dv(tabN4[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab4[i + 1][j]);
			glNormal3dv(tabN4[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab4[i + 1][j + 1]);
			glNormal3dv(tabN4[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab4[i][j]);
			glNormal3dv(tabN4[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab4[i][j + 1]);
			glNormal3dv(tabN4[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab4[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN5[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab5[i][j]);
			glNormal3dv(tabN5[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab5[i + 1][j]);
			glNormal3dv(tabN5[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab5[i + 1][j + 1]);
			glNormal3dv(tabN5[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab5[i][j]);
			glNormal3dv(tabN5[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab5[i][j + 1]);
			glNormal3dv(tabN5[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab5[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN6[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab6[i][j]);
			glNormal3dv(tabN6[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab6[i + 1][j]);
			glNormal3dv(tabN6[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab6[i + 1][j + 1]);
			glNormal3dv(tabN6[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab6[i][j]);
			glNormal3dv(tabN6[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab6[i][j + 1]);
			glNormal3dv(tabN6[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab6[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN7[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab7[i][j]);
			glNormal3dv(tabN7[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab7[i + 1][j]);
			glNormal3dv(tabN7[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab7[i + 1][j + 1]);
			glNormal3dv(tabN7[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab7[i][j]);
			glNormal3dv(tabN7[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab7[i][j + 1]);
			glNormal3dv(tabN7[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab7[i + 1][j + 1]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3dv(tabN8[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab8[i][j]);
			glNormal3dv(tabN8[i + 1][j]);
			glTexCoord2f(tex[i+1][j][0], tex[i+1][j][1]);
			glVertex3dv(tab8[i + 1][j]);
			glNormal3dv(tabN8[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab8[i + 1][j + 1]);
			glNormal3dv(tabN8[i][j]);
			glTexCoord2f(tex[i][j][0], tex[i][j][1]);
			glVertex3dv(tab8[i][j]);
			glNormal3dv(tabN8[i][j + 1]);
			glTexCoord2f(tex[i][j+1][0], tex[i][j+1][1]);
			glVertex3dv(tab8[i][j + 1]);
			glNormal3dv(tabN8[i + 1][j + 1]);
			glTexCoord2f(tex[i+1][j+1][0], tex[i+1][j+1][1]);
			glVertex3dv(tab8[i + 1][j + 1]);
			glEnd();
		}
	}
}

/*************************************************************************************/

/*void spinTorus()
{

theta[0] -= 0.5;
if (theta[0] > 360.0) theta[0] -= 360.0;

theta[1] -= 0.5;
if (theta[1] > 360.0) theta[1] -= 360.0;

theta[2] -= 0.5;
if (theta[2] > 360.0) theta[2] -= 360.0;

glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}*/

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba
// przerysowa� scen�)



void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (status == 1)                    // je�li lewy klawisz myszy wci�ni�ty
	{
		theta[0] += delta_x*pix2angle * 5;
		theta[1] += delta_y*pix2angley * 5;
	}
	if (status == 2)
	{
		viewer[2] += delta_y*pix2angley / 10;
		if (viewer[2] < 7.0) viewer[2] -= delta_y*pix2angley * 10;
		if (viewer[2] > 25.0) viewer[2] -= delta_y*pix2angley * 10;
	}
	glRotatef(theta[0], 0.0, 1.0, 0.0);
	glRotatef(theta[1], 1.0, 0.0, 0.0);
	Torus();

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

	glutSwapBuffers();
}
/*************************************************************************************/

GLfloat lookattab[3];
void specKeys(int key, int x, int y) {


	if (key == GLUT_KEY_LEFT) {
		status = 4;
	}

	if (key == GLUT_KEY_RIGHT) {
		status = 5;
	}


	if (key == GLUT_KEY_DOWN) {
		status = 6;
	}

	RenderScene(); // przerysowanie obrazu sceny
}
/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania

void Mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;        // jako pozycji poprzedniej
		status = 1;         // wci�ni�ty zosta� lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;        // jako pozycji poprzedniej
		status = 2;			//wci�ni�ty zosta� prawy klawisz myszy
	}
	else
		status = 0;         // nie zosta� wci�ni�ty �aden klawisz
}

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy

	x_pos_old = x;            // podstawienie bie��cego po�o�enia jako poprzednie

	delta_y = y - y_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy

	y_pos_old = y;            // podstawienie bie��cego po�o�enia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}


void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

	// Zmienne dla obrazu tekstury 
	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	// Definicja materia�u z jakiego zrobiony jest przedmiot
	//-------------------------------------------------------
	GLfloat mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	// wsp�czynniki ka =[kar,kag,kab] dla �wiat�a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wsp�czynniki kd =[kdr,kdg,kdb] �wiat�a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wsp�czynniki ks =[ksr,ksg,ksb] dla �wiat�a odbitego                

	GLfloat mat_shininess = { 100.0 };
	// wsp�czynnik n opisuj�cy po�ysk powierzchni


	// Definicja �r�d�a �wiat�a
	//-------------------------------------------------------
	GLfloat light_position[2][4] = { { -10.0, -10.0, -10.0, 1.0 }, { -10.0, -10.0, -10.0, 1.0 } };
	// po�o�enie �r�d�a

	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[2][4] = { { 1.0, 0.5, 0.0, 0.0 }, { 0.0, 0.5, 1.0, 1.0 } };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[2][4] = { { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.7f, 0.7f, 1.0f, 1.0f } };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0f };
	// sk�adowa sta�a ds dla modelu zmian o�wietlenia w funkcji 
	// odleg�o�ci od �r�d�a

	GLfloat att_linear = { 0.001f };
	// sk�adowa liniowa dl dla modelu zmian o�wietlenia w funkcji 
	// odleg�o�ci od �r�d�a

	GLfloat att_quadratic = { 0.001f };
	// sk�adowa kwadratowa dq dla modelu zmian o�wietlenia w funkcji
	// odleg�o�ci od �r�d�a

	// Ustawienie patrametr�w materia�u 
	//-------------------------------------------------------
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// Ustawienie parametr�w �r�d�a �wiat�a
	//-------------------------------------------------------
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse[0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position[0]);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular[1]);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position[1]);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);

	// Ustawienie opcji systemu o�wietlania sceny 
	//-------------------------------------------------------
	glShadeModel(GL_SMOOTH); // w�aczenie �agodnego cieniowania
	glEnable(GL_LIGHTING);   // w�aczenie systemu o�wietlenia sceny 
	glEnable(GL_LIGHT0);     // w��czenie �r�d�a o numerze 0
	glEnable(GL_LIGHT1);     // w��czenie �r�d�a o numerze 1
	glEnable(GL_DEPTH_TEST); // w��czenie mechanizmu z-bufora 

	// Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
	pBytes = LoadTGAImage("D9_t.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	
	// Zdefiniowanie tekstury 2-D 
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	// Zwolnienie pami�ci   
	free(pBytes);

	// W��czenie mechanizmu teksturowania
	glEnable(GL_TEXTURE_2D);

	// Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Okre�lenie sposobu nak�adania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s�
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	pix2angle = 360.0*0.1 / (float)horizontal; // przeliczenie pikseli na stopnie
	pix2angley = 360.0*0.1 / (float)vertical;

	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie��cej

	gluPerspective(70.0, 1.0, 1.0, 30.0);
	// Ustawienie parametr�w dla rzutu perspektywicznego

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielko�ci okna okna widoku (viewport) w zale�no�ci
	// relacji pomi�dzy wysoko�ci� i szeroko�ci� okna

	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(void)
{

	srand(time(NULL));
	double u, v, xu, xv, yu, yv, zu, zv, dlugosc;
	for (int i = 0; i < N; i++)
	{
		u = double(i) / (N - 1);
		for (int j = 0; j < N; j++)
		{
			v = double(j) / (N - 1);
			tex[i][j][0] = -(skala / 2) + (((float)1 / (N - 1))*j)*skala;
			tex[i][j][1] = -(skala / 2) + (((float)1 / (N - 1))*i)*skala;
			tab1[i][j][0] = (R + r*cos(2 * PI*v))*cos(2 * PI*u) - 5;
			tab1[i][j][1] = (R + r*cos(2 * PI*v))*sin(2 * PI*u);
			tab1[i][j][2] = r*sin(2 * PI*v);
			xu = -2 * PI*sin(2 * PI*u)*(r*cos(2 * PI*v) + R);
			xv = -2 * PI*r*cos(2 * PI*u)*sin(2 * PI*v);
			yu = 2 * PI*cos(2 * PI*u)*(r*cos(2 * PI*v) + R);
			yv = -2 * PI*r*sin(2 * PI*u)*sin(2 * PI*v);
			zu = 0;
			zv = 2 * PI*r*cos(2 * PI*v);
			tabN1[i][j][0] = yu*zv - zu*yv;
			tabN1[i][j][1] = zu*xv - xu*zv;
			tabN1[i][j][2] = xu*yv - yu*xv;
			dlugosc = sqrt(pow(tabN1[i][j][0], 2) + pow(tabN1[i][j][1], 2) + pow(tabN1[i][j][2], 2));
			tabN1[i][j][0] /= dlugosc;
			tabN1[i][j][1] /= dlugosc;
			tabN1[i][j][2] /= dlugosc;

			tab2[i][j][0] = (R + r*cos(2 * PI*v))*cos(2 * PI*u) - 3.7;
			tab2[i][j][1] = r*sin(2 * PI*v);
			tab2[i][j][2] = (R + r*cos(2 * PI*v))*sin(2 * PI*u);
			xu = -2 * PI*sin(2 * PI*u)*(r*cos(2 * PI*v) + R);
			xv = -2 * PI*r*cos(2 * PI*u)*sin(2 * PI*v);
			yu = 2 * PI*cos(2 * PI*u)*(r*cos(2 * PI*v) + R);
			yv = -2 * PI*r*sin(2 * PI*u)*sin(2 * PI*v);
			zu = 0;
			zv = 2 * PI*r*cos(2 * PI*v);
			tabN2[i][j][0] = yu*zv - zu*yv;
			tabN2[i][j][2] = zu*xv - xu*zv;
			tabN2[i][j][1] = xu*yv - yu*xv;
			dlugosc = sqrt(pow(tabN2[i][j][0], 2) + pow(tabN2[i][j][1], 2) + pow(tabN2[i][j][2], 2));
			tabN2[i][j][0] /= dlugosc;
			tabN2[i][j][1] /= dlugosc;
			tabN2[i][j][2] /= dlugosc;
		}
	}
	double tabpom[N][N][3];
	double tabpomN[N][N][3];
	for (int k = 0; k < 6; k++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tabpom[i][j][0] = tab2[i][j][0] + (k + 1)*1.3;
				tabpomN[i][j][0] = tabN2[i][j][0];
				if (k % 2 == 0)
				{
					tabpom[i][j][1] = tab1[i][j][1];
					tabpom[i][j][2] = tab1[i][j][2];
					tabpomN[i][j][1] = tabN1[i][j][1];
					tabpomN[i][j][2] = tabN1[i][j][2];
				}
				else
				{
					tabpom[i][j][1] = tab2[i][j][1];
					tabpom[i][j][2] = tab2[i][j][2];
					tabpomN[i][j][1] = tabN2[i][j][1];
					tabpomN[i][j][2] = tabN2[i][j][2];
				}
			}
		}
		if (k == 0)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tab3[i][j][0] = tabpom[i][j][0];
					tab3[i][j][1] = tabpom[i][j][1];
					tab3[i][j][2] = tabpom[i][j][2];
					tabN3[i][j][0] = tabpomN[i][j][0];
					tabN3[i][j][1] = tabpomN[i][j][1];
					tabN3[i][j][2] = tabpomN[i][j][2];
				}
			}
		}
		if (k == 1)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tab4[i][j][0] = tabpom[i][j][0];
					tab4[i][j][1] = tabpom[i][j][1];
					tab4[i][j][2] = tabpom[i][j][2];
					tabN4[i][j][0] = tabpomN[i][j][0];
					tabN4[i][j][1] = tabpomN[i][j][1];
					tabN4[i][j][2] = tabpomN[i][j][2];
				}
			}
		}
		if (k == 2)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tab5[i][j][0] = tabpom[i][j][0];
					tab5[i][j][1] = tabpom[i][j][1];
					tab5[i][j][2] = tabpom[i][j][2];
					tabN5[i][j][0] = tabpomN[i][j][0];
					tabN5[i][j][1] = tabpomN[i][j][1];
					tabN5[i][j][2] = tabpomN[i][j][2];
				}
			}
		}
		if (k == 3)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tab6[i][j][0] = tabpom[i][j][0];
					tab6[i][j][1] = tabpom[i][j][1];
					tab6[i][j][2] = tabpom[i][j][2];
					tabN6[i][j][0] = tabpomN[i][j][0];
					tabN6[i][j][1] = tabpomN[i][j][1];
					tabN6[i][j][2] = tabpomN[i][j][2];
				}
			}
		}
		if (k == 4)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tab7[i][j][0] = tabpom[i][j][0];
					tab7[i][j][1] = tabpom[i][j][1];
					tab7[i][j][2] = tabpom[i][j][2];
					tabN7[i][j][0] = tabpomN[i][j][0];
					tabN7[i][j][1] = tabpomN[i][j][1];
					tabN7[i][j][2] = tabpomN[i][j][2];
				}
			}
		}
		if (k == 5)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tab8[i][j][0] = tabpom[i][j][0];
					tab8[i][j][1] = tabpom[i][j][1];
					tab8[i][j][2] = tabpom[i][j][2];
					tabN8[i][j][0] = tabpomN[i][j][0];
					tabN8[i][j][1] = tabpomN[i][j][1];
					tabN8[i][j][2] = tabpomN[i][j][2];
				}
			}
		}
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutCreateWindow("Torus - tekstura");

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem
	// gdy zajdzie potrzba przeryswania okna 

	//	glutKeyboardFunc(keys);	WYKOMENYOWANIE

	//glutSpecialFunc(specKeys);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna     

	glutMouseFunc(Mouse);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie ruchu myszy

	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/