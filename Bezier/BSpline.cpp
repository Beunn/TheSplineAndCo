#include "BSpline.hpp"

void BSpline::insertPoint(int atX, int atY){
	float dist = 0.0;	
	float dist_min=999;
	float dist2 =0.0;
	int indice = 0;
	int i;

	for(i = 0; i < nbPoints_; ++i){
		dist=sqrt(double((atY - pointsList[i].second)*(atY - pointsList[i].second) + (atX - pointsList[i].first)*(atX - pointsList[i].first)));
		if(dist<dist_min){
			dist_min=dist;
			indice=i;
		}
	}

	if(indice != 0) 
		dist=sqrt(double( (atY - pointsList[i-1].second)*(atY -pointsList[i-1].second) + (atX - pointsList[i-1].first)*(atX -pointsList[i-1].first)));
	if(indice != 0) 
		dist2=sqrt(double( (atY - pointsList[i+1].second)*(atY - pointsList[i+1].second) + (atX -pointsList[i+1].first)*(atX - pointsList[i+1].first)));

	if(dist < dist2 && dist != dist_min){
		for(i = nbPoints_; i > indice; --i){
			pointsList[i].first=pointsList[i-1].first;
			pointsList[i].second=pointsList[i-1].second;
		}
		pointsList[i].first = atX;
		pointsList[i].second = atY;
	}
	else if(dist2 != dist_min){
		for(i = nbPoints_; i > indice+1 ; --i){
			pointsList[i].first=pointsList[i-1].first;
			pointsList[i].second=pointsList[i-1].second;
		}
		pointsList[i].first=atX;
		pointsList[i].second=atY;
	}
	nbPoints_++;
}

void BSpline::removePoint(int atX, int atY){
	int exist = alreadyExist(atX,atY);
	if(exist != 0) {
		for(int i= exist; i < nbPoints_-1; ++i){
			pointsList[i].first=pointsList[i+1].first;
			pointsList[i].second=pointsList[i+1].second;
		}

		nbPoints_--;
	}
}

void BSpline::insertNewPoint(int x ,int y){
	int exist = alreadyExist(x,y) ;
	if(exist != 0){
		// pour pondérer un point
		for(int i = nbPoints_; i > exist+1; --i){
			pointsList[i].first=pointsList[i-1].first;
			pointsList[i].second=pointsList[i-1].second;
		}
		pointsList[exist+1].first = pointsList[exist].first;
		pointsList[exist+1].second = pointsList[exist].second;

	}
	else {
		pointsList[nbPoints_].first = x;
		pointsList[nbPoints_].second = y;
	}
	nbPoints_++;
}

int BSpline::alreadyExist(int x,int y){
	int exist = 0;
	for(int i = 0; i < nbPoints_; ++i){
		if(x > pointsList[i].first-5 && x < pointsList[i].first+5 && y > pointsList[i].second-5 && y < pointsList[i].second+5)
			exist = i;
	}
	return exist;
}

void BSpline::closeCurve(){
	pointsList[nbPoints_] = pointsList[0];
	nbPoints_++;
}
void BSpline::movePoint(int x, int y){
	int indice=-1;
	for(int i = 0; i < nbPoints_; ++i){
		if(sqrt(double((y - pointsList[i].second)*(y - pointsList[i].second) + (x - pointsList[i].first)*(x - pointsList[i].first))) < 50)
			indice=i;
	}

	if(indice != -1){
		pointsList[indice].first = x;
		pointsList[indice].second = y;
	}
}

int BSpline::factorial(int number){
	int mult=1;
	for(int i=1;i<=number;i++)  
		mult*=i;
	return mult;
}

int BSpline::combination(int n, int p){
	if(p==0) 
		return 1;
	return factorial(n)/(factorial(p)*factorial(n-p));
}

float BSpline::N(int i,int k,int nb_noeud,float t){
	float res=0,d1,d2;
	if(k==1){
		if((nodalValues[i] <= t) && (t < nodalValues[i+1])) 
			return 1;
		else 
			return 0;
	}

	d1 = nodalValues[i+k-1] - nodalValues[i] ;
	d2 = nodalValues[i+k] - nodalValues[i+1] ;
	if (d1)
		res += (t-nodalValues[i]) / d1 *  N(i, k-1, nb_noeud, t);
	if (d2)
		res += (nodalValues[i+k]-t) / d2 * N(i+1, k-1, nb_noeud, t);

	return res;
}

int BSpline::nodalVector(){
	int n = nbPoints_-1;
	int t_max = n - degree_ + 2;
	int i,ind = 0;

	for(i = 0; i < degree_; ++i) 
		nodalValues[i] = 0;
	ind = degree_-1;

	for(i = 1; i < t_max; ++i) 
		nodalValues[i+ind] = i;
	ind += t_max;

	for(i = 0; i < degree_; ++i)
		nodalValues[i+ind] = t_max;
	ind += degree_;

	return ind;
}

void BSpline::calculateSplinePoints(){
	float pas = 0.02;
	nbPas_ = ((float)1/(float)pas)+1; 
	int n = nbPoints_-1;
	int t_max = n - degree_ + 2;
	int i,tt=0;

	nbKnots_= nodalVector(); 

	for(i = 0;i < nbPoints_; ++i){
		for(tt = 0;tt <= nbPas_; ++tt){
			float t = ((float)tt/(float)nbPas_)*t_max;
			tab[i][tt] = N(i,degree_,nbKnots_,t);
		}
	}

	for(tt = 0; tt <= nbPas_; ++tt){
		float somme = 0.0;
		for(i = 0; i<= n; ++i) 
			somme += pointsList[i].first*tab[i][tt];
		curveSpline[tt].first = somme;
		somme=0.0;
		for(i = 0; i <= n; ++i) 
			somme+=pointsList[i].second*tab[i][tt];
		curveSpline[tt].second = somme;		
	}
}