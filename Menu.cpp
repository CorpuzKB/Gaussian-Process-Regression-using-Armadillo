#include "Menu.h"

Menu::Menu()
{
	db_path = "Manila Petroleum Price Dataset.csv";
	Dataset.load(db_path, arma::csv_ascii);
	Parameters.load("Parameters.csv", arma::csv_ascii);
}

void Menu::addEntry() {
	std::ofstream file; double prices[7]; std::string date = "no date"; bool yes = true; std::string choice;
	int dd, mm, yy, days; double phpvsusd;

	do {
		cout << "\nTo input a new entry on the database. The program needs the following Data:\n";
		cout << "\t1) Date\n\t2) USD-PHP conversion on the given date\n\t3) Price for the following products\n\n";
		cout << "Date (mm dd yyyy): "; std::cin >> mm >> dd >> yy;
		cout << "USD-PHP: "; std::cin >> phpvsusd;
		days = getDifference({ 16,12,2020 }, { dd,mm,yy });

		for (int i = 0; i < 7; i++) {
			cout << db_head[i] + ": "; std::cin >> prices[i];
		}

		file.open(db_path, ios::app);
		file << days << "," << phpvsusd << "," << prices[0] << "," << prices[1] << ","
			<< prices[2] << "," << prices[3] << "," << prices[4] << ","
			<< prices[5] << "," << prices[6] << endl;
		file.close();


		cout << "Do you want to enter another data? [Y/N]: "; std::cin >> choice;
		if (choice == "Y") { yes = true; }
		if (choice == "N") { yes = false; break; }
	} while (yes == true);
}

void Menu::predict() {
	cout << "\n\nComputing mean predictions...";

	now = time(0);
	tm* ltm = localtime(&now);
	int d = ltm->tm_mday;
	int m = 1 + ltm->tm_mon;
	int y = 1900 + ltm->tm_year;
	dt1 = { 16, 12, 2020 };
	dt2 = { d, m, y };
	dayNum = getDifference(dt1, dt2) + forecastNum;

	Mat<double> X_train = Dataset.cols(uvec{ 0, 1 }), X_testC1, X_testC2, X_test;
	X_testC1 = linspace(1, dayNum, dayNum);
	interp1(Dataset.col(0), Dataset.col(1), linspace(Dataset.col(0).min(), Dataset.col(0).max(), dayNum), X_testC2, "nearest");
	X_test = join_cols(X_testC1, X_testC2);
	X_test.reshape(dayNum, 2);

	for (int i = 2; i < 9; i++) {
		Mat<double> y_train = Dataset.col(i);
		vec params = Parameters.col(i - 2);
		params = exp(params);
		models[i - 2].init(params, db_head[i - 2]);
		models[i - 2].mean = mean(mean(y_train));
		models[i - 2].std = stddev(y_train).max();
		y_train = (y_train - models[i - 2].mean) / models[i - 2].std;
		models[i - 2].RegressionModel(X_test, X_train, y_train);

		models[i - 2].predict_mean = models[i - 2].predict_mean * models[i - 2].std + models[i - 2].mean;
		models[i - 2].predict_std = models[i - 2].predict_std * models[i - 2].std;
		cout << endl << "Processed: " << db_head[i - 2];
	}

	system("CLS");
	cout << "\t\t\t=============================================================================\n";
	cout << "\t\t\t\t Data Science Application - Fuel Pricing Prediction Program\n";
	cout << "\t\t\t=============================================================================\n";

	cout << "\t\t\t\t\t\tDate:\t" << ctime(&now);
	cout << "\t\t\t=============================================================================\n\n";
	cout << "\t\t\t" << forecastNum << " Days Forecast in PHP:\n\n";
	cout << "\t\t\t\t\t";

	for (int i = 0; i < forecastNum; i++) {
		cout << "Day " << i + 1 << "\t";
	}

	for (int i = 0; i < 7; i++) {
		cout << "\t\t\t\n";
		cout << "\t\t\t" << models[i].name << "\n";
		cout << "\t\t\tMean:\t\t";
		for (int j = dayNum - forecastNum; j < dayNum; j++) {
			cout << round((models[i].predict_mean(j)) * 100) / 100 << "\t";
		}
		cout << "\n\t\t\tStd Error +-:\t";
		for (int j = dayNum - forecastNum; j < dayNum; j++) {
			cout << round((models[i].predict_std(j)) * 100) / 100 << "\t";
		}
		cout << "\n";
	}
	system("pause");
	return;
}

void Menu::banner() {
	system("CLS");
	cout << "\t\t\t=============================================================================\n";
	cout << "\t\t\t\t Data Science Application - Fuel Pricing Prediction Program\n";
	cout << "\t\t\t=============================================================================\n\n";

	cout << "[1] Input data into the dataset\n";
	cout << "[2] Predict Fuel Pricing\n";
	cout << "[3] Exit\n";
	cout << "Input: ";

}

int Menu::countLeapYears(Date d) {
	int years = d.y;
	if (d.m <= 2)
		years--;

	return years / 4
		- years / 100
		+ years / 400;
}

int Menu::getDifference(Date dt1, Date dt2) {
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	return (n2 - n1);
}