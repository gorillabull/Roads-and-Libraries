// asdf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>	


using namespace std;



vector<string> split_string(string input_string);
void dfs(long long  start, vector<vector<long long >>& list, vector<bool>& visited, long long & count);



int  main()
{
	//ofstream fout(getenv("OUTPUT_PATH"));

	long long  q;
	cin >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (long long  q_itr = 0; q_itr < q; q_itr++) {
		string nmC_libC_road_temp;
		getline(cin, nmC_libC_road_temp);

		vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

		long long  n = stoi(nmC_libC_road[0]);

		long long  m = stoi(nmC_libC_road[1]);

		long long  c_lib = stoi(nmC_libC_road[2]);

		long long  c_road = stoi(nmC_libC_road[3]);

		
		vector<vector<long long >> cities(m);
		for (long long  i = 0; i < m; i++) {
			cities[i].resize(2);

			for (long long  j = 0; j < 2; j++) {
				cin >> cities[i][j];
			}
			
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
		//mycode mycode mycode mycode mycode mycode mycode mycode mycode mycode mycode 

		vector<vector<long long >> list(n + 1);
		vector<bool> visited(n + 1);

		//convert list from imput to adjacency list 
		for (size_t i = 0; i < cities.size(); i++)
		{
			list[cities[i][0]].push_back(cities[i][1]);
			list[cities[i][1]].push_back(cities[i][0]);
		}

		long long  sum = 0;
		long long  ct = 0; //for counting separate graphs in tree 
		long long  result2 = 0;
		for (size_t i = 1; i <= n; i++)
		{
			if (!visited[i])
			{
				long long  count = 0;
				dfs(i, list, visited, count);
				if (count!=0)
				{
					result2 += ((count - 1 )* c_road) + c_lib;
				}
				ct++;
				//cout << "count " << count << " graphs  " << ct << endl;
			}
		}

		long long  result = 0; 
		if (c_lib <= c_road)
		{
			result = n * c_lib;
		}
		else
		{
			result = result2;
		}


		cout << result << endl;;
		//long long  result = roadsAndLibraries(n, c_lib, c_road, cities);

		//fout << result << "\n";
	}

	//fout.close();

	return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
		return x == y and x == ' ';
		});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}



void dfs(long long  start, vector<vector<long long >>& list, vector<bool>& visited, long long & count) {
	if (!visited[start])
	{
		count++;
	}

	visited[start] = true;

	for (long long  i = 0; i < list[start].size(); i++)
	{
		if (!visited[list[start][i]])
		{
			dfs(list[start][i], list, visited, count);
		}
	}

}

