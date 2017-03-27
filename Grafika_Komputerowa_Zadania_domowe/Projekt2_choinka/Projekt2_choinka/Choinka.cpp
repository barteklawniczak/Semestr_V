/*************************************************************************************/
// Troch? bardziej skomplikowany program wykorzystuj?cy funkcje biblioteki OpenGL
/*************************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <ctime>
/*************************************************************************************/

// Funkcaja okre?laj?ca, co ma by? rysowane 
// (zawsze wywo?ywana, gdy trzeba przerysowa? scen?)

using namespace std;
long long int steps; // ilosc krokow
double tablica[4][6];
int wiersz;
/*************************************************************************************/

void Choinka(double x, double y)
{
	double x_przed, y_przed;
	for (int i = steps; i > 0; i--)
	{
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		wiersz = rand() % 4;
		x_przed = x;
		y_przed = y;
		x = tablica[wiersz][0] * x_przed + tablica[wiersz][1] * y_przed + tablica[wiersz][2];
		y = tablica[wiersz][3] * x_przed + tablica[wiersz][4] * y_przed + tablica[wiersz][5];
	}
}

/*************************************************************************************/
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);			//ustawienie koloru na zielony
	double x = 1; int y = 1;//mozna zmienic te wartosci
	Choinka(x,y);
	glFlush();
}
/*************************************************************************************/



// Funkcja ustalaj?ca stan renderowania

void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn?trza okna - ustawiono na szary
}
/*************************************************************************************/
// Funkcja s?u??ca do kontroli zachowania proporcji rysowanych obiekt?w
// niezale?nie od rozmiar?w okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szeroko?? i wysoko?? okna) s?
// przekazywane do funkcji za ka?dym razem, gdy zmieni si? rozmiar okna
{
	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okre?laj?cej proporcj? wymiar?w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko?ciokna okna urz?dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre?lenie uk?adu wsp?rz?dnych obserwatora

	glLoadIdentity();
	// Okre?lenie przestrzeni ograniczaj?cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp?czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okre?lenie okna obserwatora. 
	// Pozwala to zachowa? w?a?ciwe proporcje rysowanego obiektu
	// Do okre?lenia okna obserwatora s?u?y funkcja glOrtho(...)

	if (horizontal <= vertical)

		glOrtho(-50.0, 50.0, -50.0 / AspectRatio, 75.0 / AspectRatio, 1.0, -1.0);
	else

		glOrtho(-50.0*AspectRatio, 50.0*AspectRatio, -50.0, 75.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre?lenie uk?adu wsp?rz?dnych    

	glLoadIdentity();
}
/*************************************************************************************/
// G??wny punkt wej?cia programu. Program dzia?a w trybie konsoli

void main(void)
{
	srand(time(NULL));
	cout << "Wpisz ilosc krokow algorytmu: "; cin >> steps;

	tablica[0][0] = -0.67;				//zapelnienie tablicy danymi wspolczynnikami
	tablica[0][1] = -0.02;
	tablica[0][2] = 0;
	tablica[0][3] = -0.18;
	tablica[0][4] = 0.81;
	tablica[0][5] = 10;
	tablica[1][0] = 0.40;
	tablica[1][1] = 0.40;
	tablica[1][2] = 0;
	tablica[1][3] = -0.10;
	tablica[1][4] = 0.40;
	tablica[1][5] = 0;
	tablica[2][0] = -0.40;
	tablica[2][1] = -0.40;
	tablica[2][2] = 0;
	tablica[2][3] = -0.10;
	tablica[2][4] = 0.40;
	tablica[2][5] = 0;
	tablica[3][0] = -0.10;
	tablica[3][1] = 0;
	tablica[3][2] = 0;
	tablica[3][3] = 0.44;
	tablica[3][4] = 0.44;
	tablica[3][5] = -2;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy?wietlania
	// GLUT_SINGLE - pojedynczy bufor wy?wietlania
	// GLUT_RGBA - model kolor?w RGB

	glutCreateWindow("Choinka");
	// Utworzenie okna i okre?lenie tre?ci napisu w nag??wku okna

	glutDisplayFunc(RenderScene);
	// Okre?lenie, ?e funkcja RenderScene b?dzie funkcj? zwrotn? (callback)
	// Biblioteka GLUT b?dzie wywo?ywa?a t? funkcj? za ka?dym razem, gdy
	// trzeba b?dzie przerysowa? okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj? zwrotn? odpowiedzialn? za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy?ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst?pieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}
/*************************************************************************************/