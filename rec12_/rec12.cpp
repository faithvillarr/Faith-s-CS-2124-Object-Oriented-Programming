#include <cstdlib>
#include <iostream>
using namespace std;

class List{
    friend ostream& operator<<(ostream& os, const List& lst){
        if(lst.length == 0){ return os; }
        Node* cursor = lst.header->next;
        while(cursor->next != nullptr){
            os<< cursor->data << " ";
            cursor = cursor->next;
        }
        return os;
    }

private:
    struct Node{
        Node(double d, Node* p = nullptr, Node* n = nullptr):
                data(d), prior(p), next(n) {};
        double data;
        Node* prior = nullptr;
        Node* next = nullptr;
    };
    //List's members
    Node* header;
    Node* trailer;
    int length = 0;

public:
    /*!TASK SIX!*/
    class iterator
    {
        friend class List;
    private:
        iterator(Node* node) : my_node(node) {}
    public:
        iterator() : my_node(0) {}
        iterator& operator ++() {
            my_node = my_node->next;
            return *this;
        }
        iterator& operator --() {
            my_node = my_node->prior;
            return *this;
        }
        friend bool operator ==(const iterator& my_it, const iterator& other){
            return my_it.my_node == other.my_node;
        }
        friend bool operator !=(const iterator& my_it, const iterator& other){
            return !(my_it == other);
        }
        int operator *(){
            return my_node->data;
        }

    private:
        Node* my_node;
    };

    void remove(Node* n){
        Node* temp = n->prior;
        n->prior->next = n->next;
        n->next->prior = temp;
        delete n;
    }

    /*! TASK ONE!*/
    List(): header(new Node(0, nullptr, trailer)),
            trailer(new Node(0, header, nullptr)) {}
    void push_back(int data){
        Node* new_node = new Node(data, trailer->prior, trailer);
        trailer->prior->next = new_node;
        trailer->prior = new_node;
        length += 1;
    }
    double pop_back(){
        remove(trailer->prior);
        length -= 1;
    }
    double& front() {
        return header->next->data;
    }
    double front() const{
        return header->next->data;
    }
    double& back(){
        return trailer->prior->data;
    }
    double back() const{
        return trailer->prior->data;
    }
    size_t size() const { return length; }

    /*!TASK TWO!*/
    void push_front(int data){
        Node* new_node = new Node(data, header, header->next);
        header->next->prior = new_node;
        header->next = new_node;
        length += 1;
    }
    void pop_front(){
        remove(header->next);
        length -= 1;
    }

    /*!TASK THREE!*/
    void clear(){
        while(header->next != trailer){
            pop_front();
        }
    }

    /*!TASK FOUR!*/
    double& operator[](int index){
        Node* cursor = header->next;
        for (size_t i = 0; i < index; ++i) {
            cursor = cursor->next;
        }
        return cursor->data;
    }
    double operator[](int index) const{
        Node* cursor = header->next;
        for (size_t i = 0; i < index; ++i) {
            cursor = cursor->next;
        }
        return cursor->data;
    }
    /*!TASk FIVE!*/
    iterator begin(){
        iterator it = iterator(header->next);
        return it;
    }
    iterator end(){
        iterator it = iterator(trailer);
        return it;
    }
    /*!TASK SIX!*/
    iterator insert(iterator iter, double data){
        Node * new_node = new Node(data, iter.my_node->prior, iter.my_node);
        iter.my_node->prior->next = new_node;
        iter.my_node->prior= new_node;
        --iter;
        length +=1;
        return iter;
    }

    /*!TASK SIX!*/
    iterator erase(iterator iter){
        remove(iter.my_node);
        ++iter;
        length--;
        return iter;
    }
};




// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
void changeFrontAndBackConst(const List& theList) {
    //theList.front() = 17;
    //theList.back() = 42;
    cout <<"Shouldn't compile anyways.\n";
}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}
/*
// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}
    */

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";


    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
/*
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    */

}
