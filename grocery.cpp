#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void frequency(vector<string> grocery) {
	//Count amount of x item
	string item;
	cout << "Enter item name: " << endl;//user enters item (case sensitive)
	cin >> item;
	//count function returns amount found in vector
	cout << count(grocery.begin(), grocery.end(), item) << endl;
}

void listGroceries(vector<string> grocery, int create) {
	//create a tempList to copy grocery and make changes without affecting grocery vector
	//returnList is the list that we end up printing out
	vector <string> tempList;
	vector <string> returnList;

	//copy list into tempList
	for (int i = 0; i < grocery.size(); i++) {
		//creates a new string of "Item Number"
		tempList.push_back(grocery[i] + " " + (to_string(count(grocery.begin(), grocery.end(), grocery[i]))));
	}

	//checks if item is in return list, if not, the push it to it.
	for (int i = 0; i < tempList.size(); i++) {
		if (count(returnList.begin(), returnList.end(), tempList[i]) == 0) {
			returnList.push_back(tempList[i]);
		}
	}

	if (create == 0) {//if 0, just print list as usual
		//Prints return list
		for (int i = 0; i < returnList.size(); i++) {
			cout << returnList[i] << endl;
		}
	}
	else if(create == 1) {//if 1, instead create a backup file.
		ofstream file("frequency.dat");
		if (file.is_open()) {
			for (int i = 0; i < returnList.size(); i++) {
				file << returnList[i] << endl;
			}
		}
		file.close();
	}
}

void listHistogram(vector<string> grocery) {
	//create a tempList to copy grocery and make changes without affecting grocery vector
	//returnList is the list that we end up printing out
	vector <string> tempList;
	vector <string> returnList;
	string tempStars = "";

	//Loop through grocery vector
	for (int i = 0; i < grocery.size(); i++) {
		//loops through the count of grocery[i] and appends stars every iteration
		for (int j = 0; j < count(grocery.begin(), grocery.end(), grocery[i]); j++) {
			tempStars.append("*");
		}
		//Pushes new string consisting of item and the stars
		tempList.push_back(grocery[i] + " " + tempStars);

		//reset stars back to an empty string for the next loop
		tempStars = "";
	}

	//checks if item is in return list, if not, the push it to it.
	for (int i = 0; i < tempList.size(); i++) {
		if (count(returnList.begin(), returnList.end(), tempList[i]) == 0) {
			returnList.push_back(tempList[i]);
		}
	}

	//prints return list
	for (int i = 0; i < returnList.size(); i++) {
		cout << returnList[i] << endl;
	}
}

int main() {
	//create grocery vector and load in provided file.
	vector <string> groceryList;
	ifstream file("CS210_Project_Three_Input_File.txt");
	string line;
	if (file.is_open()) {
		while (getline(file, line))
		{
			groceryList.push_back(line);
		}
		file.close();
	}
	else {
		cout << "womp womp" << endl;
	}
	//remember to close the file!
	file.close();

	listGroceries(groceryList, 1);

	//menu for the user
	int option = 0;
	while (option != 4) {
		cout << "1) Show how many of x item there is." << endl;
		cout << "2) Return list of items and their frequency." << endl;
		cout << "3) Return list of items as a histogram." << endl;
		cout << "4) Quit menu." << endl;
		cin >> option;
		switch (option) {
		case 1:
			frequency(groceryList);
			break;
		case 2:
			listGroceries(groceryList,0);
			break;
		case 3:
			listHistogram(groceryList);
			break;
		case 4:
			break;
		default:
			cout << "This option doesn't exist, try again." << endl;
			break;
		}
	}
	return 0;
}