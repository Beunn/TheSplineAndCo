/************************************************************************/
/*																        */
/*			Auteurs : COULAIS Benoit, GABORIAUD Pierre				    */
/*			Date :  Avril 2014						                    */
/*			Matière : Maths									            */
/*			objet: B_Spline						      	                */
/*																        */
/************************************************************************/
#include "DisplayManager.hpp"


DisplayManager * displayManager = new DisplayManager(800,800,100,100);

void keyboardFunc(unsigned char key, int x, int y){
	displayManager->keyboardFunc(key,x,y); 
}

void mouseFunc(int button,int state,int x,int y){
	displayManager->mouseFunc(button,state,x,y);
}

void reshapeFunc(int width, int height){
	displayManager->reshapeFunc(width,height);
}

void displayFunc(){
	displayManager->displayFunc();
}

void moveFunc(int x, int y ){
	displayManager->moveFunc(x,y);
}

void passiveMoveFunc(int x,int y){
	displayManager->passiveMoveFunc(x,y);
}

void menuFunc(int menu){
	displayManager->menuFunc(menu);
}

int main( int argc, char *argv[] ){	
	glutInit(&argc,argv);	
	glutInitWindowPosition(displayManager->getPosX(),displayManager->getPosY());
	glutInitWindowSize(displayManager->getWidth(),displayManager->getHeight());

	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("curves de bezier et B-Spline"); 
	glutReshapeFunc(reshapeFunc);
	glutMouseFunc (mouseFunc);
	glutKeyboardFunc(keyboardFunc);
	glutDisplayFunc(displayFunc);
	glutMotionFunc(moveFunc);
	glutPassiveMotionFunc(passiveMoveFunc);

	/* Création d'un Menu */
	int menu = glutCreateMenu(menuFunc);

	glutAddMenuEntry ("Nouvelle spline  (N)",NEW_CURVE);
	glutAddMenuEntry ("Déplacer  (D)",MOVE_POINT);
	glutAddMenuEntry ("Inserer  (I)",INSERT_POINT);
	glutAddMenuEntry ("Supprimer  (S)",DELETE_POINT);	
	glutAddMenuEntry ("Fermer la curve  (F)",CLOSE_CURVE);	
	glutAddMenuEntry ("Augmenter le degrée (+)",INCREASE_DEGREE);
	glutAddMenuEntry ("Diminuer le degrée (-)",DECREASE_DEGREE);	
	glutAddMenuEntry ("Nettoyer la fenêtre (C)",CLEAR_WINDOW);
	glutAddMenuEntry ("Quitter  (Q)",EXIT);	
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}