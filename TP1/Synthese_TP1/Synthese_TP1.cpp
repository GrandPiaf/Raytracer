#include "Synthese_TP1.h"
#include "Parachutist.h"

int main(){


	Parachutist para1("Hagrid", planeSpeed, planePosition, 80.0, 0.25);
	para1.computeCurve();

	Parachutist para2("Harry", planeSpeed, planePosition, 80.0, 0.31);
	para2.computeCurve();

	Parachutist para3("Humble", planeSpeed, planePosition, 80.0, 1.0);
	para3.computeCurve();

	return 0;
}