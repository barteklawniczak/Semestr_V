/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi 
//  uk³adu wspó³rzednych

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
double PI = M_PI;
int model = 1;
double tab1[N][N][3];
double tab2[N][N][3];
double tab3[N][N][3];
double tab4[N][N][3];
double tab5[N][N][3];
double tab6[N][N][3];
double tab7[N][N][3];
double tab8[N][N][3];
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
point3 tablicaKolorow[N][N];
float R = 1;
float r = 0.3;

GLfloat losujKolor(int a)
{
	if (a == 1)
		return 0.0f;
	else
		return 1.0f;
}

/*************************************************************************************/

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych



void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0, 5.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0, 5.0 };
	//  pocz¹tek i koniec obrazu osi y

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

}

/*************************************************************************************/

void Torus()
{
	Sleep(10);
	switch (model)
	{
	case 1:
		glBegin(GL_POINTS);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				glVertex3dv(tab1[i][j]);
				glVertex3dv(tab2[i][j]);
				glVertex3dv(tab3[i][j]);
				glVertex3dv(tab4[i][j]);
				glVertex3dv(tab5[i][j]);
				glVertex3dv(tab6[i][j]);
				glVertex3dv(tab7[i][j]);
				glVertex3dv(tab8[i][j]);
			}
		}
		glEnd();
		break;

	case 2:
		for (int i = 0; i < N - 1; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				glBegin(GL_LINES);
				glVertex3dv(tab1[i][j]);
				glVertex3dv(tab1[i + 1][j]);
				glVertex3dv(tab1[i][j]);
				glVertex3dv(tab1[i][j + 1]);
				glVertex3dv(tab1[i][j]);
				glVertex3dv(tab1[i + 1][j + 1]);

				glVertex3dv(tab2[i][j]);
				glVertex3dv(tab2[i + 1][j]);
				glVertex3dv(tab2[i][j]);
				glVertex3dv(tab2[i][j + 1]);
				glVertex3dv(tab2[i][j]);
				glVertex3dv(tab2[i + 1][j + 1]);

				glVertex3dv(tab3[i][j]);
				glVertex3dv(tab3[i + 1][j]);
				glVertex3dv(tab3[i][j]);
				glVertex3dv(tab3[i][j + 1]);
				glVertex3dv(tab3[i][j]);
				glVertex3dv(tab3[i + 1][j + 1]);

				glVertex3dv(tab4[i][j]);
				glVertex3dv(tab4[i + 1][j]);
				glVertex3dv(tab4[i][j]);
				glVertex3dv(tab4[i][j + 1]);
				glVertex3dv(tab4[i][j]);
				glVertex3dv(tab4[i + 1][j + 1]);

				glVertex3dv(tab5[i][j]);
				glVertex3dv(tab5[i + 1][j]);
				glVertex3dv(tab5[i][j]);
				glVertex3dv(tab5[i][j + 1]);
				glVertex3dv(tab5[i][j]);
				glVertex3dv(tab5[i + 1][j + 1]);

				glVertex3dv(tab6[i][j]);
				glVertex3dv(tab6[i + 1][j]);
				glVertex3dv(tab6[i][j]);
				glVertex3dv(tab6[i][j + 1]);
				glVertex3dv(tab6[i][j]);
				glVertex3dv(tab6[i + 1][j + 1]);

				glVertex3dv(tab7[i][j]);
				glVertex3dv(tab7[i + 1][j]);
				glVertex3dv(tab7[i][j]);
				glVertex3dv(tab7[i][j + 1]);
				glVertex3dv(tab7[i][j]);
				glVertex3dv(tab7[i + 1][j + 1]);

				glVertex3dv(tab8[i][j]);
				glVertex3dv(tab8[i + 1][j]);
				glVertex3dv(tab8[i][j]);
				glVertex3dv(tab8[i][j + 1]);
				glVertex3dv(tab8[i][j]);
				glVertex3dv(tab8[i + 1][j + 1]);
				glEnd();
			}
		}
		break;
	case 3:
		for (int i = 0; i < N / 2 - 1; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab1[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab1[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab1[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab1[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab1[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab1[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab2[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab2[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab2[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab2[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab2[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab2[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab3[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab3[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab3[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab3[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab3[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab3[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab4[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab4[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab4[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab4[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab4[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab4[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab5[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab5[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab5[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab5[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab5[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab5[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab6[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab6[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab6[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab6[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab6[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab6[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab7[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab7[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab7[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab7[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab7[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab7[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab8[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab8[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab8[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab8[i + 1][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab8[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab8[i + 1][j + 1]);
				glEnd();
			}
		}
		for (int i = N / 2 - 1; i < N - 1; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab1[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab1[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab1[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab1[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab1[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab1[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab2[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab2[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab2[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab2[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab2[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab2[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab3[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab3[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab3[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab3[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab3[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab3[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab4[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab4[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab4[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab4[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab4[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab4[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab5[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab5[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab5[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab5[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab5[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab5[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab6[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab6[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab6[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab6[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab6[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab6[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab7[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab7[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab7[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab7[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab7[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab7[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab8[i][j]);
				glColor3fv(tablicaKolorow[i + 1][j]);
				glVertex3dv(tab8[i + 1][j]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab8[i + 1][j + 1]);
				glColor3fv(tablicaKolorow[i][j]);
				glVertex3dv(tab8[i][j]);
				glColor3fv(tablicaKolorow[i][j + 1]);
				glVertex3dv(tab8[i][j + 1]);
				glColor3fv(tablicaKolorow[i + 1][j + 1]);
				glVertex3dv(tab8[i + 1][j + 1]);
				glEnd();
			}
		}
		break;
	}
}

/*************************************************************************************/

void spinTorus()
{

	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}

/*************************************************************************************/

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	Torus();

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania



	glutSwapBuffers();
	//

}

/*************************************************************************************/

void keys(unsigned char key, int x, int y)
{
	// 1- punkty, 2- siatka, 3 - wype³nione trójk¹ty
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene();
}

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna 

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji 

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej            

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)            

	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                    

	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej

}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



void main(void)
{

	srand(time(NULL));
	double u, v;
	for (int i = 0; i < N; i++)
	{
		u = double(i) / (N - 1);
		for (int j = 0; j < N; j++)
		{
			v = double(j) / (N - 1);
			tab1[i][j][0] = (R + r*cos(2 * PI*v))*cos(2 * PI*u)-5;
			tab1[i][j][1] = (R + r*cos(2 * PI*v))*sin(2 * PI*u);
			tab1[i][j][2] = r*sin(2 * PI*v);
			tablicaKolorow[i][j][0] = losujKolor(rand() % 2);
			tablicaKolorow[i][j][1] = losujKolor(rand() % 2);
			tablicaKolorow[i][j][2] = losujKolor(rand() % 2);

			tab2[i][j][0] = (R + r*cos(2 * PI*v))*cos(2 * PI*u)-3.7;
			tab2[i][j][1] = r*sin(2 * PI*v);
			tab2[i][j][2] = (R + r*cos(2 * PI*v))*sin(2 * PI*u);
		}
	}
	double tabpom[N][N][3];
	for (int k = 0; k < 6; k++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tabpom[i][j][0] = tab2[i][j][0] + (k+1)*1.3;
				if (k % 2 == 0)
				{
					tabpom[i][j][1] = tab1[i][j][1];
					tabpom[i][j][2] = tab1[i][j][2];
				}
				else
				{
					tabpom[i][j][1] = tab2[i][j][1];
					tabpom[i][j][2] = tab2[i][j][2];
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
				}
			}
		}
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("£añcuch torusów");

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem
	// gdy zajdzie potrzba przeryswania okna 

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna

	glutKeyboardFunc(keys);

	glutIdleFunc(spinTorus);

	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/