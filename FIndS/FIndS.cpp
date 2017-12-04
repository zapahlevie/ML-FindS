// FIndS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "iomanip"
#include "string"

using namespace std;

const char separator = ' ';
const int colWidth = 11;
const int numWidth = 5;
const int maxData = 10;
const int attr = 7;
const int maxHypo = 2;
string fact[maxData][attr];
string dataTest[maxData][attr];
string hypothesis[maxHypo][attr];

template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(separator) << t;
}

void greeting() {
	cout << "\nWILL YOU ENJOY SPORT???\n";
}

void showFact() {
	cout << "\nCurrent Facts :\n";
	if (fact[0][0] == "") {
		cout << "No data\n";
	}
	else {
		printElement("| No", numWidth);
		printElement("| Sky", colWidth);
		printElement("| AirTemp", colWidth);
		printElement("| Humidity", colWidth);
		printElement("| Wind", colWidth);
		printElement("| Water", colWidth);
		printElement("| Forecast", colWidth);
		printElement("| Enjoy", colWidth);
		printElement("|", colWidth);
		cout << endl;
	}
	for (int i = 0; i < maxData; i++) {
		if (fact[i][0] == "") {
			break;
		}
		printElement("| " + to_string(i+1), numWidth);
		for (int y = 0; y < attr; y++) {
			printElement("| " + fact[i][y], colWidth);
		}
		printElement("|", colWidth);
		cout << endl;
	}
	cout << endl;
}

void ask(string type, int data, int index, string q, string a1, string a2) {
	int answer;
	do {
		cout << q << " :\n";
		cout << "1. " << a1 << "\n";
		cout << "2. " << a2 << "\n";
		cout << "Answer : ";
		cin >> answer;
		switch (answer) {
		case 1:
			if (type == "train") {
				fact[data][index] = a1;
			}
			else{
				dataTest[data][index] = a1;
			}
			break;
		case 2:
			if (type == "train") {
				fact[data][index] = a2;
			}
			else{
				dataTest[data][index] = a2;
			}
			break;
		default:
			break;
		}
	} while (answer != 1 && answer != 2);
}

void printGroup(string groupby) {
	int num = 0;
	cout << "Target == "<< groupby << "\n";
	for (int i = 0; i < maxData; i++) {
		if (fact[i][0] == "") {
			break;
		}
		if (fact[i][attr-1] == groupby) {
			num++;
			printElement(num, numWidth);
			for (int y = 0; y < attr; y++) {
				printElement(fact[i][y], colWidth);
			}
			cout << endl;
		}
	}
}

void generalizeHypo(int num, string target) {
	int data = 0;
	for (int i = 0; i < maxData; i++) {
		if (fact[i][0] == "") {
			break;
		}
		if (fact[i][attr-1] == target) {
			data++;
			if (data == 1) {
				hypothesis[num][0] = fact[i][0];
				hypothesis[num][1] = fact[i][1];
				hypothesis[num][2] = fact[i][2];
				hypothesis[num][3] = fact[i][3];
				hypothesis[num][4] = fact[i][4];
				hypothesis[num][5] = fact[i][5];
				hypothesis[num][6] = fact[i][6];
			}
			else {
				for (int y = 0; y < attr-1; y++) {
					if (hypothesis[num][y] != fact[i][y]) {
						hypothesis[num][y] = "?";
					}
				}
			}
			cout << "H" << num <<" = {" << hypothesis[num][0];
			for (int y = 1; y < attr-1; y++) {
				cout << ", " << hypothesis[num][y];
			}
			cout << "}\n";
		}
	}
}

void printHypo(int num, string text) {
	cout << "H" << num <<" = {" << hypothesis[num][0];
	for (int i = 1; i < attr-1; i++) {
		cout << ", " << hypothesis[num][i];
	}
	cout << "} = " << text << "\n";
}

void findS() {
	printGroup("Yes");
	generalizeHypo(0, "Yes");
	cout << endl;
	printGroup("No");
	generalizeHypo(1, "No");
	cout << "\nHypothesis :\n";
	printHypo(0, "Yes");
	printHypo(1, "No");
}

void testData(string dataTest[maxData][attr], int index) {
	bool status = false;
	for (int i = 0; i < maxHypo; i++) {
		for (int y = 0; y < attr - 1; y++) {
			if (hypothesis[i][y] != "?" && hypothesis[i][y] != dataTest[index][y]) {
				break;
			}
			else if (y == attr - 2) {
				status = true;
				cout << "This data will will result : " << hypothesis[i][attr - 1];
			}
		}
	}
	if (status == false) {
		cout << "This data can't be determined";
	}
}

int main()
{
	char target;
	int data = 0;
	bool again = false;
	do {
		greeting();
		showFact();
		ask("train", data, 0, "Sky Condition", "Sunny", "Rainy");
		ask("train", data, 1, "Air temperature condition", "Warm", "Cold");
		ask("train", data, 2, "Humidity condition", "Normal", "High");
		ask("train", data, 3, "Wind Condition", "Normal", "Strong");
		ask("train", data, 4, "Water Condition", "Warm", "Cool");
		ask("train", data, 5, "Forecast Condition", "Same", "Change");
		ask("train", data, 6, "Enjoy sport", "Yes", "No");
		data++;
		cout << "Insert another data(y/n)??? ";
		cin >> target;
	} while (target == 'y' || target == 'Y');
	cout << "\nGetting hypothesis using Find-S Algorithm...\n";
	showFact();
	findS();

	cout << "\nWould you like to test a data?";
	cin >> target;
	data = 0;
	while (target == 'y' || target == 'Y') {
		ask("test", data, 0, "Sky Condition", "Sunny", "Rainy");
		ask("test", data, 1, "Air temperature condition", "Warm", "Cold");
		ask("test", data, 2, "Humidity condition", "Normal", "High");
		ask("test", data, 3, "Wind Condition", "Normal", "Strong");
		ask("test", data, 4, "Water Condition", "Warm", "Cool");
		ask("test", data, 5, "Forecast Condition", "Same", "Change");
		testData(dataTest, data);
		data++;
		cout << "\n\nInsert another data(y/n)??? ";
		cin >> target;
	}
    return 0;
}