#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() 
{
    ifstream infile("data/dictionary.txt");
    vector<string> filtered_words;
    string word;

    if(!infile.is_open()) {

        cout << "Error: Could not open file." << endl;
        return 1;
    }

    // Read file line by line and filter out words < 3 letters
    while (getline(infile, word)) 
    {
        if (word.length() >= 3) {
            filtered_words.push_back(word);
        }
    }

    infile.close();

    ofstream outfile("filtered.txt");

    if(!outfile.is_open()) 
    {
        cout << "Error: Could not create output file." << endl;
        return 1;
    }

    for (const auto& w : filtered_words) 
    {
        outfile << w << "\n";
    }
    outfile.close();
    cout << "Saved as 'filtered.txt'" << endl;
    return 0;
}
