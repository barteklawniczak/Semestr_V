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
int licznik_u = 0;
int licznik_d = 0;
//////////////////////////////////////////////////
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
// inicjalizacja po�o�enia obserwatora
static GLfloat theta1 = 0.0;   // k�t obrotu obiektu
static GLfloat phi = 0.0;   // k�t obrotu obiektu
static GLfloat R2 = 0.0;
static GLfloat pix2angle;     // przelicznik pikseli na stopnie
static GLint status = 0;       // stan klawiszy myszy 
// 0 - nie naci�ni�to �adnego klawisza
// 1 - naci�ni�ty zosta� lewy klawisz
// 2 - naci�ni�ty zosta� prawy klawisz
static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;		// poprzednia pozycja kursora myszy
static int c_pos_old = 0;
static int delta_x = 0;        // r�nica pomi�dzy pozycj� bie��c�
// i poprzedni� kursora myszy 
static int delta_y = 0;        // r�nica pomi�dzy pozycj� bie��c�
// i poprzedni� kursora myszy 
static int delta_c = 0;
/////////////////////////////////////////////////
GLfloat losujKolor(int a)
{
	if (a == 1)
		return 0.0f;
	else
		return 1.0f;
}

/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych



void Axes(void)
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

}

/*************************************************************************************/

void Torus()
{
	Sleep(10);
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

	glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}

/*************************************************************************************/

// Funkcja "bada" stan myszy i ustawia warto�ci odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		status = 1;          // wci�ni�ty zosta� lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		c_pos_old = y;
		status = 2;
	}
	else
		status = 0;          // nie zosta� wci�ni�ty �aden klawisz 
}


/*************************************************************************************/
// Funkcja "monitoruje" po�o�enie kursora myszy i ustawia warto�ci odpowiednich 
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy

	x_pos_old = x;            // podstawienie bie��cego po�o�enia jako poprzednie

	delta_y = y - y_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy

	y_pos_old = y;            // podstawienie bie��cego po�o�enia jako poprzednie

	delta_c = y - c_pos_old;

	c_pos_old = y;

	glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba
// przerysowa� scen�)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	Torus();

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania



	glutSwapBuffers();
	//

}

/*************************************************************************************/

void keys(unsigned char key, int x, int y)
{
	// 1- punkty, 2- siatka, 3 - wype�nione tr�jk�ty
	if (key == 'u')
	{
		licznik_u++;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tab5[i][j][1] += 0.05;
				if (licznik_u >= 6)
				{
					if (licznik_u < 35)
					{
						tab4[i][j][1] += 0.02*tab6[i][j][0];
						tab4[i][N - j - 1][1] += 0.005;
						tab4[i][j][0] -= 0.0035;

						tab6[i][j][1] -= 0.023*tab4[i][j][0];
						tab6[i][N - j - 1][1] += 0.005;
						tab6[i][j][0] += 0.0035;
					}
					else
					{
						tab4[i][j][1] += 0.05;
						tab6[i][j][1] += 0.05;

						tab3[i][j][1] += 0.05;
						tab7[i][j][1] += 0.05;

						if (licznik_u >= 41)
						{
							if (licznik_u < 76)
							{
								tab2[i][j][1] += 0.02*tab6[i][j][0]-0.01;
								tab2[i][N - j - 1][1] += 0.005;
								tab2[i][j][0] -= 0.0035;

								tab8[i][j][1] -= 0.023*tab4[i][j][0]+0.01;
								tab8[i][N - j - 1][1] += 0.005;
								tab8[i][j][0] += 0.0035;
							}
							else
							{
								tab1[i][j][1] += 0.05;
								tab2[i][j][1] += 0.05;
								tab8[i][j][1] += 0.05;
							}
						}
					}
				}
			}
		}
	}
	RenderScene();
}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s�
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  

	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 

	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            

	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                    

	glLoadIdentity();
	// Czyszcenie macierzy bie��cej

}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



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
			tab1[i][j][0] = (R + r*cos(2 * PI*v))*cos(2 * PI*u) - 5;
			tab1[i][j][1] = (R + r*cos(2 * PI*v))*sin(2 * PI*u);
			tab1[i][j][2] = r*sin(2 * PI*v);
			tablicaKolorow[i][j][0] = losujKolor(rand() % 2);
			tablicaKolorow[i][j][1] = losujKolor(rand() % 2);
			tablicaKolorow[i][j][2] = losujKolor(rand() % 2);

			tab2[i][j][0] = (R + r*cos(2 * PI*v))*cos(2 * PI*u) - 3.7;
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
				tabpom[i][j][0] = tab2[i][j][0] + (k + 1)*1.3;
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

	glutCreateWindow("�a�cuch torus�w");

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem
	// gdy zajdzie potrzba przeryswania okna 

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna

	glutKeyboardFunc(keys);

	glutMouseFunc(Mouse);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie ruchu myszy

//	glutIdleFunc(spinTorus);

	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/