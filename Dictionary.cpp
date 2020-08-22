#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <list>
#include <algorithm>

using namespace std;
struct Word {
	string Pos;
	string def;
}word;

bool containPos(string pos) {
	vector<string> tense = { "noun","verb","adjective","adverb","conjunction","interjection","preposition","pronoun" };
	if (find(tense.begin(), tense.end(), pos) != tense.end())
	{
		return true;
	}
	else return false;
}




int main() {
	static multimap<string, Word> wordMap;
	
	string fileline;
	ifstream file("Data.CS.SFSU.txt");
	if (file.is_open()) {
		cout << "! Opening data file... ./Data.CS.SFSU.txt" << endl;
		cout << "! Loading data..." << endl;

		while (getline(file, fileline)) {
			istringstream strLine(fileline);
			string definiton;
			string arrow = " -=>> ";
			vector<string> rawData;
			vector<Word> wordDef;
			while (getline(strLine, definiton, '|')) {
				rawData.push_back(definiton);
			}
			string tempkey = rawData[0];
			for (int i = 1; i < rawData.size(); i++) {
				string definition = rawData[i];
				word.Pos = definition.substr(0, definition.find(arrow));
				//cout << word.Pos;
				word.def = definition.substr(definition.find(arrow) + arrow.size(), definition.find(".") + 1 - word.Pos.size() - arrow.size());
				//cout << word.def << endl; //unhide these to show the words are split functional.
				wordMap.emplace(tempkey, word);
			}

		}
		/*for (const auto& p : wordMap) {
			cout << p.first << ": [" << p.second.Pos << "] " << p.second.def << "\n";
		}*/
		//unhide this to show the map did take in the data
		file.close();
		cout << "! Loading completed..." << endl;
		cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
	}

	cout << endl;
	cout << "----- DICTIONARY 340 C++----- " << endl;
	cout << endl;


	while (true) {
		cout << "Search: " << endl;
		string userInput;
		getline(cin, userInput);
		for (int i = 0; i < userInput.length(); i++) { 
			//turn input into lower case to match keys
			userInput[i] = tolower(userInput[i]);
		}
		istringstream search(userInput);
		vector<string> parameter;
		string tempkeys;
		// same as assignment 1, 
		//split input by space, and use them as parameter for else if case
		while (search >> tempkeys) {
			parameter.push_back(tempkeys);
		}

		if (parameter.size() == 1) {
			//exit statement
			if (parameter[0] == "!q") {
				cout << "  |" << endl;
				cout << "-----THANK YOU-----" << endl;
					break;
			}
			else if (wordMap.count(parameter[0]) != 0) {// im trying to write "contains(key)" but its not working. 
				cout << "  |" << endl;
				auto values = wordMap.equal_range(parameter[0]);
				for (auto itr = values.first; itr != values.second; ++itr) {
				cout << parameter[0] << " [" << itr->second.Pos << "] " << itr->second.def << endl;
				}
				cout << "  |" << endl;
			}
			else {
				cout << "  |" << endl;
				cout << "<NOT FOUND>" << endl;
				cout << "  |" << endl;
			}


		}
		else if (parameter.size() == 2) {
			if ((wordMap.count(parameter[0]) != 0) && containPos(parameter[1])){
				cout << "  |" << endl;
				auto values = wordMap.equal_range(parameter[0]);
				for (auto itr = values.first; itr != values.second; ++itr) {
					if (parameter[1] == itr->second.Pos) {
						cout << parameter[0] << " [" << itr->second.Pos << "] " << itr->second.def << endl;
					}
				}
				cout << "  |" << endl;
			}
			else if ((wordMap.count(parameter[0]) != 0) && parameter[1] =="distinct") {
				vector<string> defdist;
				cout << "  |" << endl;
				auto values = wordMap.equal_range(parameter[0]);
				for (auto itr = values.first; itr != values.second; ++itr) {
					string wholedef = ": [" + itr->second.Pos + "] " + itr->second.def;
					if (find(defdist.begin(), defdist.end(), wholedef) == defdist.end())
					{
						defdist.push_back(wholedef);
					}
				}
				for (int i = 0; i < defdist.size(); i++) {
					cout << parameter[0] << defdist[i] << endl;

				}
				if (defdist.size() == 0) {

					cout << "  |" << endl;
					cout << "<NOT FOUND" << endl;


				}
				cout << "  |" << endl;
			}
			else {
				cout << "  |" << endl;
				cout << "<NOT FOUND>" << endl;
				cout << "  |" << endl;
			}
		}
		else if (parameter.size() == 3){
			if ((wordMap.count(parameter[0]) != 0) && containPos(parameter[1]) && parameter[2] == "distinct") {
				vector<string> defdist;
				cout << "  |" << endl;
				auto values = wordMap.equal_range(parameter[0]);
				for (auto itr = values.first; itr != values.second; ++itr) {
					string wholedef = ": [" + itr->second.Pos + "] " + itr->second.def;
					if (parameter[1] == itr->second.Pos) {
						if (find(defdist.begin(), defdist.end(), wholedef) == defdist.end())
						{
							defdist.push_back(wholedef);
						}
					}

				}
				for (int i = 0; i < defdist.size(); i++) {
					cout << parameter[0] << defdist[i] << endl;
				}
				if (defdist.size() == 0) {

					cout << "  |" << endl;
					cout << "<NOT FOUND" << endl;
				
				}
				cout << "  |" << endl;
			}
			else {
				cout << "  |" << endl;
				cout << "<NOT FOUND>" << endl;
				cout << "  |" << endl;
			}
		}
		


	}

	return 0;
}
