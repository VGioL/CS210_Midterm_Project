
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class CSVReader {
public:
    static vector<vector<string>> readCSV(const string& filename) {
        ifstream file(filename);
        vector<vector<string>> data;
        string line, word;

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return data;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;
            while (getline(ss, word, ',')) {
                row.push_back(word);
            }
            data.push_back(row);
        }
        file.close();
        return data;
    }
};

struct School
{
private:
    string name;
    string address;
    string city;
    string state;
    string country;
    School* next;
};

class SchoolList
{
    School* head;
    School* tail;
public:
    void insertFirst(School school)
    {

    }

    void insertLast(School school)
    {

    }

    void deleteByName(string name)
    {

    }

    School* findByName(string name)
    {

    }

    void display()
    {

    }
};

int main()
{

    return 0;
}