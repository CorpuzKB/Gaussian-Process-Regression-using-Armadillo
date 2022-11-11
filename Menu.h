#pragma once
#include <armadillo>
#include "Gaussian_Process.h"

using namespace arma;

class Menu {
public:
	std::string db_path;
	std::string db_head[7] = { "RON 100", "RON 97", "RON 95", "RON 91", "DIESEL", "DIESEL PLUS", "KEROSENE" };
	int dayNum;
	int forecastNum;
	struct Date { int d, m, y; };
	const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Mat<double> Dataset, Parameters;
	Gaussian_Process models[7];
	Date dt1, dt2; time_t now;

	Menu();
	void addEntry();
	void banner();
	int countLeapYears(Date d);
	int getDifference(Date dt1, Date dt2);
	void predict();
};
