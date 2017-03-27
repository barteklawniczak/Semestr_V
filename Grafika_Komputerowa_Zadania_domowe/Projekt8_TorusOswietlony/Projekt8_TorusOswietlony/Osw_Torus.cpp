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
double tabN1[N][N][3];
double tabN2[N][N][3];
double tabN3[N][N][3];
double tabN4[N][N][3];
double tabN5[N][N][3];
double tabN6[N][N][3];
double tabN7[N][N][3];
double tabN8[N][N][3];
static GLfloat theta1[] = { 0.0, 0.0, 0.0 };
float R = 1;
float r = 0.3;

//////////////////
typedef float point3[3];
static GLfloat	fi[2] = { 5.76f, 1.05f }, theta[2] = { 4.68f, 4.68f };// k¹ty obrotu, elewacja i azymut DODANE
static GLfloat	pix2angle_x = 0.0, pix2angle_y = 0.0;	// przelicznik pikseli na stopnie
float lightsR = 10.0;	//Promien sfery swiatel	DOD
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
static GLfloat phi = 0.0;   // k¹t obrotu obiektu
static GLfloat pix2angle;     // przelicznik pikseli na stopnie
static GLint status = 0;       // stan klawiszy myszy 
static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;		// poprzednia pozycja kursora myszy
static int delta_x = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹ // i poprzedni¹ kursora myszy 
static int delta_y = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
//////////////////
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
		for (int i = 0; i < N / 2 - 1; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN1[i][j]);
				glVertex3dv(tab1[i][j]);
				glNormal3dv(tabN1[i + 1][j]);
				glVertex3dv(tab1[i + 1][j]);
				glNormal3dv(tabN1[i][j + 1]);
				glVertex3dv(tab1[i][j + 1]);
				glNormal3dv(tabN1[i + 1][j]);
				glVertex3dv(tab1[i + 1][j]);
				glNormal3dv(tabN1[i][j + 1]);
				glVertex3dv(tab1[i][j + 1]);
				glNormal3dv(tabN1[i + 1][j + 1]);
				glVertex3dv(tab1[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN2[i][j]);
				glVertex3dv(tab2[i][j]);
				glNormal3dv(tabN2[i + 1][j]);
				glVertex3dv(tab2[i + 1][j]);
				glNormal3dv(tabN2[i][j + 1]);
				glVertex3dv(tab2[i][j + 1]);
				glNormal3dv(tabN2[i + 1][j]);
				glVertex3dv(tab2[i + 1][j]);
				glNormal3dv(tabN2[i][j + 1]);
				glVertex3dv(tab2[i][j + 1]);
				glNormal3dv(tabN2[i + 1][j + 1]);
				glVertex3dv(tab2[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN3[i][j]);
				glVertex3dv(tab3[i][j]);
				glNormal3dv(tabN3[i + 1][j]);
				glVertex3dv(tab3[i + 1][j]);
				glNormal3dv(tabN3[i][j + 1]);
				glVertex3dv(tab3[i][j + 1]);
				glNormal3dv(tabN3[i + 1][j]);
				glVertex3dv(tab3[i + 1][j]);
				glNormal3dv(tabN3[i][j + 1]);
				glVertex3dv(tab3[i][j + 1]);
				glNormal3dv(tabN3[i + 1][j + 1]);
				glVertex3dv(tab3[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN4[i][j]);
				glVertex3dv(tab4[i][j]);
				glNormal3dv(tabN4[i + 1][j]);
				glVertex3dv(tab4[i + 1][j]);
				glNormal3dv(tabN4[i][j + 1]);
				glVertex3dv(tab4[i][j + 1]);
				glNormal3dv(tabN4[i + 1][j]);
				glVertex3dv(tab4[i + 1][j]);
				glNormal3dv(tabN4[i][j + 1]);
				glVertex3dv(tab4[i][j + 1]);
				glNormal3dv(tabN4[i + 1][j + 1]);
				glVertex3dv(tab4[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN5[i][j]);
				glVertex3dv(tab5[i][j]);
				glNormal3dv(tabN5[i + 1][j]);
				glVertex3dv(tab5[i + 1][j]);
				glNormal3dv(tabN5[i][j + 1]);
				glVertex3dv(tab5[i][j + 1]);
				glNormal3dv(tabN5[i + 1][j]);
				glVertex3dv(tab5[i + 1][j]);
				glNormal3dv(tabN5[i][j + 1]);
				glVertex3dv(tab5[i][j + 1]);
				glNormal3dv(tabN5[i + 1][j + 1]);
				glVertex3dv(tab5[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN6[i][j]);
				glVertex3dv(tab6[i][j]);
				glNormal3dv(tabN6[i + 1][j]);
				glVertex3dv(tab6[i + 1][j]);
				glNormal3dv(tabN6[i][j + 1]);
				glVertex3dv(tab6[i][j + 1]);
				glNormal3dv(tabN6[i + 1][j]);
				glVertex3dv(tab6[i + 1][j]);
				glNormal3dv(tabN6[i][j + 1]);
				glVertex3dv(tab6[i][j + 1]);
				glNormal3dv(tabN6[i + 1][j + 1]);
				glVertex3dv(tab6[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN7[i][j]);
				glVertex3dv(tab7[i][j]);
				glNormal3dv(tabN7[i + 1][j]);
				glVertex3dv(tab7[i + 1][j]);
				glNormal3dv(tabN7[i][j + 1]);
				glVertex3dv(tab7[i][j + 1]);
				glNormal3dv(tabN7[i + 1][j]);
				glVertex3dv(tab7[i + 1][j]);
				glNormal3dv(tabN7[i][j + 1]);
				glVertex3dv(tab7[i][j + 1]);
				glNormal3dv(tabN7[i + 1][j + 1]);
				glVertex3dv(tab7[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN8[i][j]);
				glVertex3dv(tab8[i][j]);
				glNormal3dv(tabN8[i + 1][j]);
				glVertex3dv(tab8[i + 1][j]);
				glNormal3dv(tabN8[i][j + 1]);
				glVertex3dv(tab8[i][j + 1]);
				glNormal3dv(tabN8[i + 1][j]);
				glVertex3dv(tab8[i + 1][j]);
				glNormal3dv(tabN8[i][j + 1]);
				glVertex3dv(tab8[i][j + 1]);
				glNormal3dv(tabN8[i + 1][j + 1]);
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
				glVertex3dv(tab1[i][j]);
				glNormal3dv(tabN1[i + 1][j]);
				glVertex3dv(tab1[i + 1][j]);
				glNormal3dv(tabN1[i + 1][j + 1]);
				glVertex3dv(tab1[i + 1][j + 1]);
				glNormal3dv(tabN1[i][j]);
				glVertex3dv(tab1[i][j]);
				glNormal3dv(tabN1[i][j + 1]);
				glVertex3dv(tab1[i][j + 1]);
				glNormal3dv(tabN1[i + 1][j + 1]);
				glVertex3dv(tab1[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN2[i][j]);
				glVertex3dv(tab2[i][j]);
				glNormal3dv(tabN2[i + 1][j]);
				glVertex3dv(tab2[i + 1][j]);
				glNormal3dv(tabN2[i + 1][j + 1]);
				glVertex3dv(tab2[i + 1][j + 1]);
				glNormal3dv(tabN2[i][j]);
				glVertex3dv(tab2[i][j]);
				glNormal3dv(tabN2[i][j + 1]);
				glVertex3dv(tab2[i][j + 1]);
				glNormal3dv(tabN2[i + 1][j + 1]);
				glVertex3dv(tab2[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN3[i][j]);
				glVertex3dv(tab3[i][j]);
				glNormal3dv(tabN3[i + 1][j]);
				glVertex3dv(tab3[i + 1][j]);
				glNormal3dv(tabN3[i + 1][j + 1]);
				glVertex3dv(tab3[i + 1][j + 1]);
				glNormal3dv(tabN3[i][j]);
				glVertex3dv(tab3[i][j]);
				glNormal3dv(tabN3[i][j + 1]);
				glVertex3dv(tab3[i][j + 1]);
				glNormal3dv(tabN3[i + 1][j + 1]);
				glVertex3dv(tab3[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN4[i][j]);
				glVertex3dv(tab4[i][j]);
				glNormal3dv(tabN4[i + 1][j]);
				glVertex3dv(tab4[i + 1][j]);
				glNormal3dv(tabN4[i + 1][j + 1]);
				glVertex3dv(tab4[i + 1][j + 1]);
				glNormal3dv(tabN4[i][j]);
				glVertex3dv(tab4[i][j]);
				glNormal3dv(tabN4[i][j + 1]);
				glVertex3dv(tab4[i][j + 1]);
				glNormal3dv(tabN4[i + 1][j + 1]);
				glVertex3dv(tab4[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN5[i][j]);
				glVertex3dv(tab5[i][j]);
				glNormal3dv(tabN5[i + 1][j]);
				glVertex3dv(tab5[i + 1][j]);
				glNormal3dv(tabN5[i + 1][j + 1]);
				glVertex3dv(tab5[i + 1][j + 1]);
				glNormal3dv(tabN5[i][j]);
				glVertex3dv(tab5[i][j]);
				glNormal3dv(tabN5[i][j + 1]);
				glVertex3dv(tab5[i][j + 1]);
				glNormal3dv(tabN5[i + 1][j + 1]);
				glVertex3dv(tab5[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN6[i][j]);
				glVertex3dv(tab6[i][j]);
				glNormal3dv(tabN6[i + 1][j]);
				glVertex3dv(tab6[i + 1][j]);
				glNormal3dv(tabN6[i + 1][j + 1]);
				glVertex3dv(tab6[i + 1][j + 1]);
				glNormal3dv(tabN6[i][j]);
				glVertex3dv(tab6[i][j]);
				glNormal3dv(tabN6[i][j + 1]);
				glVertex3dv(tab6[i][j + 1]);
				glNormal3dv(tabN6[i + 1][j + 1]);
				glVertex3dv(tab6[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN7[i][j]);
				glVertex3dv(tab7[i][j]);
				glNormal3dv(tabN7[i + 1][j]);
				glVertex3dv(tab7[i + 1][j]);
				glNormal3dv(tabN7[i + 1][j + 1]);
				glVertex3dv(tab7[i + 1][j + 1]);
				glNormal3dv(tabN7[i][j]);
				glVertex3dv(tab7[i][j]);
				glNormal3dv(tabN7[i][j + 1]);
				glVertex3dv(tab7[i][j + 1]);
				glNormal3dv(tabN7[i + 1][j + 1]);
				glVertex3dv(tab7[i + 1][j + 1]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3dv(tabN8[i][j]);
				glVertex3dv(tab8[i][j]);
				glNormal3dv(tabN8[i + 1][j]);
				glVertex3dv(tab8[i + 1][j]);
				glNormal3dv(tabN8[i + 1][j + 1]);
				glVertex3dv(tab8[i + 1][j + 1]);
				glNormal3dv(tabN8[i][j]);
				glVertex3dv(tab8[i][j]);
				glNormal3dv(tabN8[i][j + 1]);
				glVertex3dv(tab8[i][j + 1]);
				glNormal3dv(tabN8[i + 1][j + 1]);
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

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}*/

/*************************************************************************************/

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)



void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	if (status == 1) {	// jeœli lewy klawisz myszy wciœniêty	
		theta[0] -= delta_x*pix2angle_x;
		//Ograniczenie dla azymutu
		if (theta[0] <= 0)
			theta[0] += 2 * PI;
		if (theta[0] >= 2 * PI)
			theta[0] -= 2 * PI;

		fi[0] -= delta_y*pix2angle_y;
		//Ograniczenie dla elewacji
		if (fi[0] <= 0)
			fi[0] += 2 * PI;
		if (fi[0] >= 2 * PI)
			fi[0] -= 2 * PI;
	}
	else if (status == 2) {	// jeœli prawy klawisz myszy wciœniêty
		theta[1] -= delta_x*pix2angle_x;
		//Ograniczenie dla azymutu
		if (theta[1] <= 0)
			theta[1] += 2 * PI;
		if (theta[1] >= 2 * PI)
			theta[1] -= 2 * PI;

		fi[1] -= delta_y*pix2angle_y;
		//Ograniczenie dla elewacji
		if (fi[1] <= 0)
			fi[1] += 2 * PI;
		if (fi[1] >= 2 * PI)
			fi[1] -= 2 * PI;
	}

	else if (status == 4) {
		gluLookAt(10.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	else if (status == 5) {
		gluLookAt(10.0, 10.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	else if (status == 6) {
		gluLookAt(0.0, 10.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie po³o¿enia obserwatora

	GLfloat lights_positions[4] = { 0 };
	lights_positions[0] = lightsR * cos(theta[0]) * cos(fi[0]);
	lights_positions[1] = lightsR * sin(fi[0]);
	lights_positions[2] = lightsR * sin(theta[0]) * cos(fi[0]);
	lights_positions[3] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, lights_positions);
	//Aktualizacja pozycji swiatla 0

	lights_positions[0] = lightsR * cos(theta[1]) * cos(fi[1]);
	lights_positions[1] = lightsR * sin(fi[1]);
	lights_positions[2] = lightsR * sin(theta[1]) * cos(fi[1]);
	lights_positions[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_POSITION, lights_positions);
	//Aktualizacja pozycji swiatla 1

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej powy¿ej
	/*glRotatef(theta1[0], 1.0, 0.0, 0.0);

	glRotatef(theta1[1], 0.0, 1.0, 0.0);

	glRotatef(theta1[2], 0.0, 0.0, 1.0);
	*/
	//Renderowanie torusów
	Torus();

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

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

// Funkcja ustalaj¹ca stan renderowania

void Mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;        // jako pozycji poprzedniej
		status = 1;         // wciœniêty zosta³ lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;        // jako pozycji poprzedniej
		status = 2;			//wciœniêty zosta³ prawy klawisz myszy
	}
	else
		status = 0;         // nie zosta³ wciœniêty ¿aden klawisz
}

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy

	x_pos_old = x;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

	delta_y = y - y_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy

	y_pos_old = y;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}


void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

	// Definicja materia³u z jakiego zrobiony jest przedmiot
	//-------------------------------------------------------
	GLfloat mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego                

	GLfloat mat_shininess = { 100.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni


	// Definicja Ÿród³a œwiat³a
	//-------------------------------------------------------
	GLfloat light_position[2][4] = { { -10.0, -10.0, -10.0, 1.0 }, { -10.0, -10.0, -10.0, 1.0 } };
	// po³o¿enie Ÿród³a

	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[2][4] = { { 1.0, 0.5, 0.0, 0.0 }, { 0.0, 0.5, 1.0, 1.0 } };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[2][4] = { { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.7f, 0.7f, 1.0f, 1.0f } };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0f };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_linear = { 0.001f };
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_quadratic = { 0.001f };
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	// Ustawienie patrametrów materia³u 
	//-------------------------------------------------------
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// Ustawienie parametrów Ÿród³a œwiat³a
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

	// Ustawienie opcji systemu oœwietlania sceny 
	//-------------------------------------------------------
	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny 
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_LIGHT1);     // w³¹czenie Ÿród³a o numerze 1
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora 
}


/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle_x = 360.0*0.0125 / (float)horizontal; // przeliczenie pikseli na stopnie
	pix2angle_y = 360.0*0.0125 / (float)vertical;	//DOdANE ^->

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej

	gluPerspective(70, 1.0, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



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

	glutCreateWindow("Oswietlenie torusów dwoma zrodlami swiatla");

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem
	// gdy zajdzie potrzba przeryswania okna 

	//	glutKeyboardFunc(keys);	WYKOMENYOWANIE

	glutSpecialFunc(specKeys);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna     

	glutMouseFunc(Mouse);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie ruchu myszy

	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/