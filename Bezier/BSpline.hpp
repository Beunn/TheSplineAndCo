#ifndef BSPLINE_HPP_
#define BSPLINE_HPP_

#include <vector>

#define MAX_POINTS 200

class BSpline{
private:
	std::vector<std::pair<float,float>> pointsList;
	std::vector<std::pair<float,float>> curveSpline;
	
	std::vector<std::vector<float>> tab;

	std::vector<int> nodalValues;

	int nbPoints_,degree_,nbKnots_;	
	float nbPas_;

public:
	BSpline():pointsList(MAX_POINTS),curveSpline(MAX_POINTS),tab(MAX_POINTS,std::vector<float>(MAX_POINTS)),nodalValues(MAX_POINTS),
		nbKnots_(0),nbPoints_(0),degree_(4),nbPas_(0){}

	inline int getPointsSize(){ return nbPoints_; }
	inline int getCurvePointsSize(){ return nbPas_;}

	inline std::pair<float, float>& getPoint(int index){ return pointsList[index]; }
	inline std::pair<float,float>& getCurvePoint(int index){ return curveSpline[index]; }

	inline int getDegree(){ return degree_; }

	inline void increaseDegree(){ degree_++; }
	inline void decreaseDegree(){ if (degree_ > 2) degree_--; }

	int factorial(int number);
	int combination(int n ,int p);

	float N(int i,int k,int nbKnots,float t);
	int nodalVector();
	void calculateSplinePoints();

	int alreadyExist(int x,int y);

	void insertPoint(int atX, int atY);
	void removePoint(int atX, int atY);
	void insertNewPoint(int x ,int y);
	void closeCurve();
	void movePoint(int x, int y);
};

#endif