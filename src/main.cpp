#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

int main() {

	string sortBy = "Popularity";

	int choice = -1;
	while (choice != 0)
	{
		cout << "========== SORTIFY ==========\n";
		cout << "Currently sorting by: " << sortBy << "\n";
		cout << "1. Sort by..?\n";
		cout << "2. Run Merge Sort\n";
		cout << "3. Run Quick Sort\n";
		cout << "4. Run both and compare\n";
		cout << "5. Show top N tracks\n";
		cout << "0. Exit\n";

		cout << "> ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			choice = -1;
		}

		if (choice == 1)
		{
			char letter;
			cout << "a) Popularity  b) Danceability  c) Energy  d) Tempo  e) Duration\n";
			cout << " Choose a letter: ";
			cin >> letter;

			if (letter == 'a')
			{
				sortBy = "Popularity";
			}

			else if (letter == 'b')
			{
				sortBy = "Danceability";
			}

			else if (letter == 'c')
			{
				sortBy = "Energy";
			}

			else if (letter == 'd')
			{
				sortBy = "Tempo";
			}

			else if (letter == 'e')
			{
				sortBy = "Duration";
			}

			else
			{
				cout << "Invalid letter, keeping current choice.\n";
			}
		}

		else if (choice == 2)
		{
			cout << "Merge Sort: not implemented yet\n";
		}

		else if (choice == 3)
		{
			cout << "Quick Sort: not implemented yet\n";
		}

		else if (choice == 4)
		{
			cout << "Compare: not implemented yet\n";
		}

		else if (choice == 5)
		{
			cout << "Top N: not implemented yet\n";
		}

		else if (choice == 0)
		{
			cout << "Goodbye!\n";
		}

		else
		{
			cout << "Invalid choice, try again.\n";
		}
	}
	return 0;
}