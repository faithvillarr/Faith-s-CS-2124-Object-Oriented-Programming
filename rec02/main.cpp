#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Chemical{
    int num_carbon;
    int num_hydrogen;
    vector<string> c_names;
};

void display_chemical(const Chemical& chem ){
    cout << "C" << chem.num_carbon << "H" << chem.num_hydrogen << " ";
    for (const string& s : chem.c_names){
        cout<< s << " ";
    }
    cout << endl;
}

void display_chem_vec(const vector<Chemical>& c_vec){
    for (const Chemical& c : c_vec){
        display_chemical(c);
    }
}

void insert_chemical(const Chemical& curr_chem, vector<Chemical>& all_chems){
    bool present = false;
    for (size_t t = 0; t < all_chems.size(); t++){
        if (all_chems[t].num_carbon == curr_chem.num_carbon && all_chems[t].num_hydrogen == curr_chem.num_hydrogen) {
            present = true;
            for(const string& s: curr_chem.c_names){
                all_chems[t].c_names.push_back(s);
            }
        }
    }
    if(!present){
        all_chems.push_back(curr_chem);
    }
}


void store_chem_in_vec(ifstream& c_file, vector<Chemical>& chemicals){
    char c, h;
    int n_carbon, n_hydrogen;
    string name;
    Chemical temp_chem;
    while(c_file >> name >> c >> n_carbon >> h >> n_hydrogen){
        temp_chem.c_names.push_back(name);
        temp_chem.num_carbon = n_carbon;
        temp_chem.num_hydrogen = n_hydrogen;
        insert_chemical(temp_chem, chemicals);
        temp_chem.c_names.clear();
    }

}

void open_user_file(ifstream& chem_file){
    string file_name;
    do{
        cout << "Please enter a file name: ";
        cin >> file_name;
        
        chem_file.open(file_name);
        if (!chem_file) {
            file_name.clear();
        }
    }while (!chem_file);
}

void sort_by_carbon(vector<Chemical>& chem_vec){
    for(size_t i = 0 ; i < chem_vec.size(); ++i){
        for(size_t j = 0; j < chem_vec.size()-1; ++j) {
            if(chem_vec[j].num_carbon > chem_vec[j+1].num_carbon){
                swap(chem_vec[j], chem_vec[j+1]);
            }else if(chem_vec[j].num_carbon == chem_vec[j+1].num_carbon){
                if(chem_vec[j].num_hydrogen > chem_vec[j+1].num_hydrogen){
                    swap(chem_vec[j], chem_vec[j+1]);
                }
            }
        }
    }

}

int main() {
    ifstream chem_file;
    open_user_file(chem_file);

    vector<Chemical> chemicals;
    cout << endl << "Unsorted:"<< endl;
    store_chem_in_vec(chem_file, chemicals);
    display_chem_vec(chemicals);

    cout << endl << "Sorted:"<< endl;
    sort_by_carbon(chemicals);
    display_chem_vec(chemicals);
    chem_file.close();

}

