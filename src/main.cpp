#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

int main() {

	int choice = -1;
	while (choice != 0)
	{
		cout << "========== SORTIFY ==========\n";
		cout << "1. Sort by..?\n";
		cout << "2. Run Merge Sort\n";
		cout << "3. Run Quick Sort\n";
		cout << "4. Run both and compare\n";
		cout << "5. Show top N tracks\n";
		cout << "0. Exit\n";

		cout << "> ";
		cin >> choice;
	}
	return 0;
}