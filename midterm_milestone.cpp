
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
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
    string name;
    string address;
    string city;
    string state;
    string county;
    /*School* next;*/
    School* left = nullptr;
    School* right = nullptr;
};

/*class SchoolList
{
    School* head = nullptr;
    School* tail = nullptr;
    int length = 0;
public:
    void insertFirst(School* school)
    {
        if (head == nullptr) // empty list
        {
            head = school;
            tail = school;
            length++;
        }
        else
        {
            School* temp = head;
            head = school;
            head->next = temp;
            length++;
        }
    }

    void insertLast(School* school)
    {
        if (head == nullptr) // empty list
        {
            head = school;
            tail = school;
            length++;
        }
        else
        {
            School* temp = tail;
            tail = school;
            temp->next = school;
            length++;
        }
    }

    void deleteByName(string name)
    {
        School* curr = head;
        for (int i = 0; i < length - 1; i++)
        {
            if (curr->next->name == name)
            {
                School* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
            }
            else
            {
                curr = curr->next;
            }

        }

    }

    School* findByName(string name)
    {
        School* curr = head;
        for (int i = 0; i < length; i++)
        {
            if (curr->name == name)
            {
                return curr;
            }
            else
            {
                curr = curr->next;
            }

        }
        return nullptr;
    }

    void display()
    {
        School* curr = head;
        for (int i = 0; i < length; i++)
        {

            cout << curr->name << ": " <<
            curr->address << ", " <<
            curr->city << " " <<
            curr->state << ", " <<
            curr->county << endl;

            curr = curr->next;
        }

    }
};*/


/// BST

class SchoolBST
{
    School* root = nullptr;

public:
    void insert(School* school)
    {
        if (root == nullptr)
        {
            root = school;
        }
        else
        {
            insertHelper(root, school);
        }
    }
private:
    void insertHelper(School* currNode, School* school)
    {
        if (currNode != nullptr)
        {
            if (school->name < currNode->name)
            {
                if (currNode->left == nullptr)
                {
                    currNode->left = school;
                    return;
                }
                currNode = currNode->left;
            }
            else
            {
                if (currNode->right == nullptr)
                {
                    currNode->right = school;
                    return;
                }
                currNode = currNode->right;
            }
            insertHelper(currNode, school);
        }
    }

public:
    School* findByName(string school)
    {
        return findByNameHelper(root, school);
    }
private:
    School* findByNameHelper(School* currNode, string school)
    {
        if (currNode == nullptr)
        {
            return nullptr;
        }

        if (school == currNode->name)
        {
            return currNode;
        }

        if (school < currNode->name)
        {
            currNode = currNode->left;
        }
        else
        {
            currNode = currNode->right;
        }

        return findByNameHelper(currNode, school);

    }

public:
    void displayInOrder()
    {
        stack<School*> visited;


    }

    void displayPreOrder()
    {
        cout << "Preorder" << endl;
        stack<School*> visited;
        visited.push(root);
        /*displayPreOrderHelper(&visited);*/
        while (visited.size() != 0)
        {
            School* curr = visited.top();
            if (curr != nullptr) {
                cout << curr->name << endl;
                visited.pop();
                visited.push(curr->right);
                visited.push(curr->left);
            }
            else
            {
                visited.pop();
            }
        }
    }
/*private:
    void displayPreOrderHelper(stack<School*>* visited)
    {
        School* curr = visited->top();
        if (curr != nullptr) {
            cout << curr->name;
            visited->pop();
            visited->push(curr->right);
            visited->push(curr->left);
            displayPreOrderHelper(visited);
            displayPreOrderHelper(visited);
        }
        else
        {
            visited->pop();
        }
    }*/

    void displayPostOrder()
    {
        stack<School*> visited;


    }

};




int main()
{
    // transpose .CVS to vector, and transpose vector to SchoolList object
    CSVReader reader;
    vector<vector<string>> vector = reader.readCSV("midterm_milestone.csv");
    SchoolBST bst;
    for(int i = 1; i < vector.size(); i++) // for every row except header row
    {
        School *newSchool = new School();
        newSchool->name = vector[i][0];
        newSchool->address = vector[i][1];
        newSchool->city = vector[i][2];
        newSchool->state = vector[i][3];
        newSchool->county = vector[i][4];
        bst.insert(newSchool);
    }

    bool running = true;
    int input = 0;
    string schoolName;
    while (running) {
        cout << "Enter 1 to search for a school by name." << endl;
        cout << "Enter 2 to delete a school by name." << endl;
        cout << "Enter 0 to end program and see full list of schools." << endl;
        // TODO parse input for int?
        cin >> input; // get input from user

        if (input == 0)
        {
            running = false;
        }
        else if (input == 1) // search for school by name
        {
            bool runningSearch = true;
            while (runningSearch)
            {
                cout << "Enter a school name to search or 0 to quit: ";
                getline(cin, schoolName); // get input from user
                if (schoolName == "0")
                {
                    runningSearch = false;
                }
                else if (schoolName == "") {
                    //cout << "Invalid input, try again." << endl;
                }
                else
                {
                    School* foundSchool = bst.findByName(schoolName);
                    if (foundSchool == nullptr)
                    {
                        cout << "School not found." << endl;
                    }
                    else
                    {
                        cout << foundSchool->name << " found at: " << endl;
                        cout << foundSchool->address << ", " << foundSchool->city << " " << foundSchool->state << ", " << foundSchool->county << endl;
                        runningSearch = false;
                    }
                }
            }

        }
        else if (input == 2) // delete school by name
        {
            bool runningDelete = true;
            while (runningDelete)
            {
                cout << "Enter a school name to delete or 0 to quit: ";
                getline(cin, schoolName); // get input from user
                if (schoolName == "0")
                {
                    break;
                }
                else if (schoolName == "")
                {
                    //cout << "Invalid input, try again." << endl;
                }
                else
                {
                    //bst.deleteByName(schoolName);

                    runningDelete = false;
                }
            }
        }
        else
        {
            cout << "Invalid input. try again." << endl;
        }
        cout << endl;
    }

    //bst.displayInOrder();
    bst.displayPreOrder();
    //bst.displayPostOrder();

    return 0;
}
