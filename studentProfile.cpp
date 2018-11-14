/* database.h */
#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef struct profile_t {
  //Define variable to store a student profile
  string studentID;
  string name;
  string phoneNumber;
} Profile;

typedef struct grade_t {
  //Define variables to store the grade for a student in a specific class
  string studentID;
  string classID;
  double mark;
} Grade;

class Database {
private:
  // studentID : profile
  map < string , Profile > studentData;
  // classID : grade
  map < string , Grade > classData;


public:
  bool add_profile(string id, string name, string phone);
  bool del_profile(string id);
  bool add_grade(string id, string class_id, double grade);
  bool del_grade(string id, string class_id);
  //Display data
  void display_profiles();
  void display_grades(string class_id);

};

/* database.cpp */

bool Database::add_profile(string id, string name, string phone){
  if ( studentData.count(id) > 0 ){ // if he is alreadt existed
    studentData[id].studentID = id;
    studentData[id].name = name;
    studentData[id].phoneNumber = phone;
    cout << "Profile Updated" << endl;
  } else {
    Profile tempProfile;
    tempProfile.studentID = id;
    tempProfile.name = name;
    tempProfile.phoneNumber = phone;
    studentData[id] = tempProfile;
  }
  return true;
}

bool Database::del_profile(string id){
  if ( studentData.count(id) > 0 ){
    studentData.erase(id);
    if ( classData.count(id) > 0){
      classData.erase(id);
    }
    return true;
  } else {
    cout << "Record Not Exists" << endl;
    return false;
  }
}

bool Database::add_grade(string id, string class_id, double grade){
  if ( studentData.count(id) > 0 ){
    if ( classData.count(id) > 0 ){
      classData[id].studentID = id;
      classData[id].classID = class_id;
      classData[id].mark = grade;
      cout << "Grade Updated" << endl;
    } else {
      Grade tempGrade;
      tempGrade.studentID = id;
      tempGrade.classID = class_id;
      tempGrade.mark = grade;
      classData[id] = tempGrade;
    }
    return true;
  } else {
    cout << "Student Not Exists" << endl;
    return false;
  }
}

bool Database::del_grade(string id, string class_id){
  if ( classData.count(id) > 0 ){
    classData.erase(id);
    return true;
  } else {
    cout << "Record Not Exists" << endl;
    return false;
  }
}

//Display data
void Database::display_profiles(){
  map < string , Profile > :: iterator itr;
  for ( itr = studentData.begin() ; itr != studentData.end() ; itr++ ){
    cout << (*itr).second.name << " " << (*itr).second.studentID << " " << (*itr).second.phoneNumber << endl;
  }
}

void Database::display_grades(string class_id){
  double min , max , avg , count = 0;
  double sum = 0;
  string name;
  map < string , Grade > :: iterator itrClass;
  map < string , Profile > :: iterator itrSystem;

  for ( itrClass = classData.begin() ; itrClass != classData.end() ; itrClass++ ){

    if ( (*itrClass).second.classID == class_id ) {
      for ( itrSystem = studentData.begin() ; itrSystem != studentData.end() ; itrSystem++ ){
        if ( (*itrSystem).second.studentID == (*itrClass).second.studentID ){
          name = (*itrSystem).second.name;
        }
      }
      if ( itrClass == classData.begin()){
        min = (*itrClass).second.mark;
        max = (*itrClass).second.mark;
      }
      if ( (*itrClass).second.mark < min ) { min = (*itrClass).second.mark; }
      if ( (*itrClass).second.mark > max ) { max = (*itrClass).second.mark; }
      cout << name << " " << (*itrClass).second.studentID << " " << (*itrClass).second.mark << endl;
      sum += (*itrClass).second.mark;
      count++ ;
    }
  }
  avg = sum / count;
  cout << "Min" << " " << min << endl;
  cour << "Max" << " " << max << endl;
  cout << "Average" << " " << avg << endl;
}

/* database_main.cpp */

int main() {
  string command, command_type;
  string id, name, phone, class_id;
  double grade;

  Database database;

  while(cin >> command >> command_type) {
    if(command_type == "profile") {
      if (command == "create") {
        cin >> id >> name >> phone;
        database.add_profile(id, name, phone);
      } else if (command == "delete") {
        cin >> id;
        database.del_profile(id);
      } else if (command == "display") {
        database.display_profiles();
      }
    } else if (command_type == "grade") {
      if (command == "create") {
        cin >> id >> class_id >> grade;
        database.add_grade(id, class_id, grade);
      } else if (command == "delete") {
        cin >> id >> class_id;
        database.del_grade(id, class_id);
      } else if (command == "display") {
        cin >> class_id;
        database.display_grades(class_id);
      }
    }
  }
}
