#include "DisplayManager.hpp"

void DisplayManager::displayFunc(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width_,0,height_,-1.0,1.0);
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	displayGrid();

	for(int i = 0; i < listOfSplines_.size(); ++i){
		BSpline * tmp = listOfSplines_[i];
		tmp->calculateSplinePoints();

		displayArrayPoints(*tmp);
		displayCurve(*tmp);
	}

	glFlush();
}

void DisplayManager::displayLine(int x1,int y1, int x2, int y2){
	glBegin(GL_LINES);
		glVertex2f (x1,y1); 
		glVertex2f (x2,y2);
	glEnd();
}

void DisplayManager::displayPoint(int x,int y){
	glColor3ub(50,50, 255);
	displayLine(x-5,y-5,x+5,y+5);
	displayLine(x+5,y-5,x-5,y+5);
}

void DisplayManager::displayArrayPoints(BSpline& spline){	
	glColor3ub(250,50, 255);
	glBegin(GL_LINE_STRIP);
	for(int i= 0; i<spline.getPointsSize(); i++)
		glVertex2f(spline.getPoint(i).first, spline.getPoint(i).second);
	glEnd();
	for(int i= 0; i<spline.getPointsSize(); i++) 
		displayPoint(spline.getPoint(i).first,spline.getPoint(i).second);
}

void DisplayManager::displayGrid(){
	glColor3ub(200,200,200);
	for(int i=0;i<width_;i+=20){
		displayLine(i,0,i,width_);
	}

	for(int i=0;i<height_;i+=20)
		displayLine(0,i,height_,i);
}

void DisplayManager::displayCurve(BSpline& spline){
	glColor3ub(250,0, 0);	
	glBegin(GL_LINE_STRIP);
	for(int i= 0; i<spline.getCurvePointsSize(); i++)
		glVertex2f(spline.getCurvePoint(i).first, spline.getCurvePoint(i).second);
	glEnd();
}

void DisplayManager::reshapeFunc(int x, int y){
	glViewport(0,0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	width_ = x;
	height_ = y;
}

void DisplayManager::mouseFunc(int button,int state, int x, int y){
	if (button==GLUT_LEFT_BUTTON){
		if(state==GLUT_UP)
			movePoint_=false;	

		if (state==GLUT_DOWN){			
			if(!movePoint_){
				if(insertPoint_){
					listOfSplines_[activeCurve_]->insertPoint(x,height_ - y);
					insertPoint_=false;
				}
				else {
					if(deletePoint_){
						listOfSplines_[activeCurve_]->removePoint(x,height_ - y);
						deletePoint_=false;
					}
					else
						listOfSplines_[activeCurve_]->insertNewPoint(x,height_ - y);				
				}
			}
		}
	}
	glutPostRedisplay();
}

void DisplayManager::keyboardFunc(unsigned char key, int x, int y){
	switch (key){
	case 'i':
		insertPoint_ = true;
		break;
	case 's':
		deletePoint_ = true;
		break;
	case 'd':
		movePoint_ = true;
		break;
	case 'q':
		exit(-1);
		break;
	case 'n':	
		listOfSplines_.push_back(new BSpline());
		activeCurve_++;
		break;
	case 'f':
		listOfSplines_[activeCurve_]->closeCurve();
		glutPostRedisplay();
		break;
	case '+':
		listOfSplines_[activeCurve_]->increaseDegree();
		glutPostRedisplay();
		break;
	case '-':
		listOfSplines_[activeCurve_]->decreaseDegree();
		glutPostRedisplay();
		break;
	case 'c':
		clearWindow();
		glutPostRedisplay();
		break;
	case 27:	
		clearWindow();	
		exit(-1);		
		break;
	default:
		break;
	}
}

void DisplayManager::moveFunc(int x,int y){
	if(movePoint_){
		listOfSplines_[activeCurve_]->movePoint(x, height_- y);		
		glutPostRedisplay();
	}
}

void DisplayManager::passiveMoveFunc(int x, int y){
	int x1,y1;
	x1 = x - width_ / 2;
	y1 = -(y - height_ / 2);

	char buf[50];
	sprintf_s(buf,"     - Cursor Position -  [ %i ; %i ]",x1,y1);
	glutSetWindowTitle(buf);
}

void DisplayManager::menuFunc(int item){
	switch (item)
	{
	case NEW_CURVE :
		listOfSplines_.push_back(new BSpline());
		activeCurve_++;
		break;
	case MOVE_POINT :
		movePoint_ = true;
		break;		
	case INSERT_POINT :
		insertPoint_ = true;
		break;
	case DELETE_POINT :
		deletePoint_ = true;
		break;
	case CLOSE_CURVE :
		listOfSplines_[activeCurve_]->closeCurve();
		break;
	case INCREASE_DEGREE :
		listOfSplines_[activeCurve_]->increaseDegree();
		break;
	case DECREASE_DEGREE :
		listOfSplines_[activeCurve_]->decreaseDegree();
		break;
	case CLEAR_WINDOW :
		clearWindow();
		break;
	case EXIT:
		clearWindow();
		exit(-1);
	default:
		break;
	}
	glutPostRedisplay();
}

void DisplayManager::clearWindow(){	
	for(int i = 0; i < listOfSplines_.size(); ++i){
		delete listOfSplines_[i];
	}
	listOfSplines_.clear();
	activeCurve_ = 0;
	listOfSplines_.push_back(new BSpline());
}