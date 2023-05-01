// rec13_start.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

//! TASK NINE
void printList(const list<unsigned>& temp_lst){
    list<unsigned>::const_iterator p = temp_lst.begin();
    for (p; p != temp_lst.end() ; p++) { cout << *p << " "; }
    cout << endl;
}
//! TASK TEN
void printListRangedFor(const list<unsigned>& temp_lst){
    for (unsigned i : temp_lst) { cout << i << " "; }
    cout << endl;
}
void printEveryOtherAuto(list<unsigned> temp_lst){
    bool print = true;
    for(auto i = temp_lst.begin(); i != temp_lst.end(); i++){
        if(print) cout << *i << " ";
        print = !print;
    }
    cout << endl;
}
//! TASK TWELVE
list<unsigned>::const_iterator findListItem(const list<unsigned>& lst, int key){
    list<unsigned>::const_iterator res = lst.begin();
    while(res != lst.end()){ if(*res == key) return res; res++;}
    return lst.end();
}
//! TASK THIRTEEN
auto findListItemAuto(list<unsigned> lst, int key){
    auto res = lst.begin();
    while(res != lst.end()){ if(*res == key) return res; res++;}
    return lst.end();
}
//!TASK FIFTEEN
bool isEvenInt(int i){ return (i%2 == 0); }

//!TASK SIXTEEN
class Thing{
public:
    bool operator()(int i){
        return isEvenInt(i);
    }
};

//!TASK NINETEEN
list<unsigned>::iterator ourFind(list<unsigned>::iterator b, list<unsigned>::iterator e, int key){
    while(b != e){
        if(*b == key) return b;
        b++;
    }
    return e;
}

//!TASK TWENTY
template<typename i>
typename list<i>::const_iterator ourFind(typename list<i>::const_iterator start,
                                       typename list<i>::const_iterator end,
                                       i toFind){
    typename list<i>::const_iterator q;
    for(q = start; q != end; q++){
        if(*q == toFind) return q;
    }
    return end;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<unsigned> vector1 = {1, 1, 15, 32,5,2,432, 3};
    for(unsigned i : vector1){ cout << i << " "; }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<unsigned> lst(vector1.begin(), vector1.end());
    for (unsigned i : lst) { cout << i << " "; }
    cout <<endl;

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vector1.begin(), vector1.end());
    cout << "Vector: ";
    for(unsigned i : vector1){ cout << i << " "; }
    cout << endl << "List: ";
    for (unsigned i : lst) { cout << i << " "; }
    cout << endl;

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vector1.size(); i+=2) {
        cout << vector1[i]<< " ";
    }
    cout << endl;

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t i = 0; i < lst.size(); i+=2) {
//        cout << lst[i] << " ";
//    }
//    cout << endl;

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    vector<unsigned>::iterator p = vector1.begin();
    for (p; p != vector1.end(); p+=2) {
        cout << *p << " ";
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    list<unsigned>::iterator q = lst.begin();
    for (q; q != lst.end(); q.operator++().operator++()) {
        cout << *q << " ";
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (unsigned i : lst) { cout << i << " "; }
    cout << endl;

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(lst);

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRangedFor(lst);

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printEveryOtherAuto(lst);
    cout << "=======\n";

    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << "Finding 5 in lst: ";
    if (findListItem(lst, 5) != lst.end()) cout << "Found!\n";
    else cout << "Not found!\n";
    cout << "Finding 7895 in lst: ";
    if (findListItem(lst, 7895) != lst.end()) cout << "Found!\n";
    else cout << "Not found!\n";
    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << "Finding 5 in lst: ";
    if (findListItemAuto(lst, 5) != lst.end()) cout << "Found!\n";
    else cout << "Not found!\n";
    cout << "Finding 7895 in lst: ";
    if (findListItemAuto(lst, 7895) != lst.end()) cout << "Found!\n";
    else cout << "Not found!\n";

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    if(find(lst.begin(), lst.end(), 433) != lst.end())
        cout << "Value 433 has been found!\n";
    else
        cout << "Value 433 has not been found!\n";
    if(find(lst.begin(), lst.end(), 5) != lst.end())
        cout << "Value 5 has been found!\n";
    else
        cout << "Value 5 has not been found!\n";

    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    printList(lst);
    if(lst.end() != find_if(lst.begin(), lst.end(), isEvenInt))
        cout << "An even number exists in lst.\n";
    else
        cout << "No even numbers are present in lst\n";
    list<int> temp_Lst = {1,1,1,1,1,15};
    if(temp_Lst.end() != find_if(temp_Lst.begin(), temp_Lst.end(), isEvenInt))
        cout << "An even number exists in tempLst.\n";
    else
        cout << "No even numbers are present in tempLst\n";

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    //i did it
    Thing t;
    find_if(lst.begin(), lst.end(), t);

    cout << "=======\n";

    // 17. Lambda
    cout << "Task 17:\n";

    find_if(lst.begin(), lst.end(), [] (int a) { return a%2 == 0; } );

    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* temp = new int[vector1.size()];
    copy(lst.begin(), lst.end(), temp);
    for(int i = 0; i < vector1.size(); i++){
        cout << temp[i] << " ";
    }
    cout << endl;

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    if(ourFind(lst.begin(), lst.end(), 433) != lst.end() )
        cout << "Value 433 has been found!\n";
    else
        cout << "Value 433 has not been found!\n";
    if(ourFind(lst.begin(), lst.end(), 5) != lst.end())
        cout << "Value 5 has been found!\n";
    else
        cout << "Value 5 has not been found!\n";


    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    find(lst.begin(), lst.end(), 433);

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream myFile;
    myFile.open("pooh-nopunc.txt");
    if (!myFile) {
        cerr << "file failed to open";
        exit(1);
    }
    vector<string> myCol;
    string cursor;
    while(myFile >> cursor){
        if(find(myCol.begin(), myCol.end(), cursor) == myCol.end()){
            myCol.push_back(cursor);
        }
    }
    myFile.close();
    for(string i : myCol){
        cout << i << " ";
    }


    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "\n\n\nTask 22:\n\n\n";
    set<string> mySet;
    ifstream roundTwo;
    roundTwo.open("pooh-nopunc.txt");
    if (!roundTwo) {
        cerr << "file failed to open";
        exit(1);
    }
    string pointer;
    while(roundTwo >> pointer){
        mySet.insert(pointer);
    }
    roundTwo.close();
    for(string i : mySet){
        cout << i << " ";
    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    ifstream mapFile;
    mapFile.open("pooh-nopunc.txt");
    if(!mapFile) {cerr << "file not found"; exit(1);}

    string key;
    int position = 1;
    while(mapFile >> key){
        wordMap[key].push_back(position);
        position++;
    }

    for(auto i: wordMap){
        cout << "\"" << i.first <<  "\": ";
        for(int l : i.second){
            cout << l << " ";
        }
        cout << endl;
    }
    cout << "=======\n";
}
