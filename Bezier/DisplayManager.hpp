#ifndef DIPLAYMANAGER_HPP_
#define DIPLAYMANAGER_HPP_

#include "BSpline.hpp"

#include <GL\glut.h>
#include <vector>
	
enum MENU_TYPE{NEW_CURVE,MOVE_POINT,INSERT_POINT, DELETE_POINT, CLOSE_CURVE, INCREASE_DEGREE, DECREASE_DEGREE, CLEAR_WINDOW, EXIT};

class DisplayManager{
private:
	int width_,height_,posX_,posY_;
	int activeCurve_;
	std::vector<BSpline *> listOfSplines_;

	bool insertPoint_,deletePoint_,movePoint_,closeCurve_;
public:
	DisplayManager(int width, int height):width_(width),height_(height),posX_(0),posY_(0),activeCurve_(0),insertPoint_(false),deletePoint_(false),movePoint_(false),closeCurve_(false){ 
		listOfSplines_.push_back(new BSpline()); 
	}
	DisplayManager(int width, int height, int posX, int posY):width_(width),height_(height),posX_(posX),posY_(posY),activeCurve_(0),insertPoint_(false),deletePoint_(false),movePoint_(false),closeCurve_(false){ 
		listOfSplines_.push_back(new BSpline()); 
	}

	inline int getWidth(){ return width_; }
	inline int getHeight(){ return height_; }
	inline int getPosX(){ return posX_; }
	inline int getPosY(){ return posY_; }

	void displayFunc();
	void reshapeFunc(int x, int y);
	void mouseFunc(int button,int state, int x, int y);
	void keyboardFunc(unsigned char key, int x, int y);
	void moveFunc(int x,int y);
	void passiveMoveFunc(int x, int y);
	void menuFunc(int menu);

	void displayGrid();
	void displayPoint(int x,int y);
	void displayArrayPoints(BSpline& spline);
	void displayLine(int x1,int y1, int x2, int y2);
	void displayCurve(BSpline& spline);

	void clearWindow();
};

#endif