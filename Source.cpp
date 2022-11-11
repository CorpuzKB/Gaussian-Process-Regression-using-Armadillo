#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <armadillo>
#include "Kernels.h"
#include "Gaussian_Process.h"
#include "Menu.h"

using namespace arma;

int main()
{
	Menu menu;
	int choice, fcn;
	bool run = true;

	while (run) {
		menu.banner();
		std::cin >> choice;
		switch (choice) {
		case 1:
			menu.addEntry();
			break;
		case 2:
			cout << "\nInput how many days to predict from today's date: "; std::cin >> fcn;
			menu.forecastNum = fcn;
			menu.predict();
			cout << endl;
			break;
		case 3:
			run = false;
			break;
		default:
			cout << "Invalid input, please input again: ";
		}
	}
}

