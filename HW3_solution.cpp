//HW3
//Due: 11:59PM, September 6 (Friday)
/*
 I made some minor revision.
 You should use this HW3 version and ignore the previous version.
 
 The file HW3_Sample_Disply is my console display for the main funciton I provided.
 You are required to follow the same output format using my main funciton.
 Note that, during grading, other sample main functions can be used.
 
 Notice that there is one space in "CIS554 1 3".
 However, there are 2 space between "CIS554" and "CSE674".
 Moreover, there is a blank line at the beginning when each print function is invoked.
 */
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
    string name;
    int section;
    int credits;
    course() {}
    course(string n, int s, int c) { name = n; section = s; credits = c; }
    bool operator<(course c) { return (name < c.name); }
    bool operator==(course c) { return (name == c.name); }
};

void add_student(map<int, map<int, list<course> * >> &DB, int id);
void remove_student(map<int, map<int, list<course> * >> &DB, int id);
void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
//All courses in the list should be sorted according to name (increasing order)
void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id);
void print_DB(map<int, map<int, list<course> * >> &DB);

int main() {
    map<int, map<int, list<course> *>> DB;
    add_student(DB, 11111);
    
    course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);
    
    cout<<"---->>>courses semester 20171 ------------"<<endl;
    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);

    drop_course(DB, 20171, 11111, C1);
    cout<<"---->>>after drop ------------------------"<<endl;
    print_student_semester_courses(DB, 20171, 11111);

    add_course(DB, 20172, 11111, C2);
    add_course(DB, 20172, 11111, C4);
    add_course(DB, 20172, 11111, C3);
    add_course(DB, 20172, 11111, C1);
    cout<<"---->>>after add 20172 -------------------"<<endl;
    print_student_semester_courses(DB, 20172, 11111);
    print_student_all_courses(DB, 11111);

    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C4);
    add_course(DB, 20171, 11112, C3);
    add_course(DB, 20171, 11112, C1);
    cout<<"---->>>courses semester 20171 ------------"<<endl;
    print_student_semester_courses(DB, 20171, 11112);

    add_course(DB, 20172, 11112, C2);
    add_course(DB, 20172, 11112, C4);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C1);
    cout<<"---->>>courses semester 20172 ------------"<<endl;
    print_student_semester_courses(DB, 20172, 11112);
    print_student_all_courses(DB, 11112);
    
    cout<<"---->>>all information in database---------"<<endl;
    print_DB(DB);
    remove_student(DB, 11111);
    cout<<"after remove student 11111"<<endl;
    print_DB(DB);
    getchar();
    getchar();
    return 0;
}

void add_student(map<int, map<int, list<course> * >> &DB, int id) {
    DB[id][0] = nullptr;
    
}
void remove_student(map<int, map<int, list<course> * >> &DB, int id) {
    DB.erase(id);
}


void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c) {
    if(DB[id][semester] != nullptr){
        DB[id][semester]->push_back(c);
    }
    else{
        DB[id][semester] = new list<course>;
        DB[id][semester]->push_back(c);
    }
}

void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c) {
    auto iterend = DB[id][semester]->end();
    for(auto iter = DB[id][semester]->begin(); iter != iterend; ++iter){
        if (c.name == iter->name) {
            DB[id][semester]->erase(iter);
        }
    }
}

void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id) {
    cout<<"name: \t"<<"section: \t"<<"credits: \t"<<"ID:"<<id<<endl;
    auto iterend = DB[id][semester]->end();
    for (auto iter = DB[id][semester]->begin(); iter != iterend ; ++iter) {
        
        cout<<iter->name<<"\t\t"<<iter->section<<"\t\t\t"<<iter->credits<<endl;
    }
    
}

void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id) {
    cout<<"-->> 2017 1st semester --------------------"<<endl;
    print_student_semester_courses(DB, 20171, id);
    cout<<"-->> 2017 2nd semester --------------------"<<endl;
    print_student_semester_courses(DB, 20172, id);
}

void print_DB(map<int, map<int, list<course> * >> &DB) {
    for (auto multiinter = DB.begin(); multiinter != DB.end(); ++multiinter) {
        cout<<"name: \t"<<"section: \t"<<"credits: \t"<<"ID:"<<multiinter->first<<endl;
        auto inneriter = multiinter->second.begin();
        inneriter++;
        for (auto interiter = inneriter; interiter != multiinter->second.end(); ++interiter) {
            cout<<"-->> "<<interiter->first<<" semester ---------------------------"<<endl;
            for (auto iter = interiter->second->begin(); iter != interiter->second->end(); ++iter) {
                cout<<iter->name<<"\t\t"<<iter->section<<"\t\t\t"<<iter->credits<<endl;
            }
        }
    }
    
    
}

//check before add(do nothing),delete(nothing there do nothing)
