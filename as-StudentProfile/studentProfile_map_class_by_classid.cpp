/* database.h */
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
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
  // class_id : grade
  map < string , vector <Grade> > classData;


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
    string name = studentData[id].name;
    studentData.erase(id);
    map < string , vector<Grade> > :: iterator itrMap;
    for ( itrMap = classData.begin() ; itrMap != classData.end() ; itrMap++ ){
      vector <Grade> :: iterator itrVectorGrade;
      for ( itrVectorGrade = (*itrMap).second.begin() ; itrVectorGrade != (*itrMap).second.end() ; itrVectorGrade++ ){
        if ( (*itrVectorGrade).studentID == id ){
          (*itrMap).second.erase(itrVectorGrade);
          break;
        }
      }
    }
    return true;
  } else {
    cout << "Record Not Exists" << endl;
    return false;
  }
}

bool Database::add_grade(string id, string class_id, double grade){
  if ( studentData.count(id) > 0 ){
    if ( classData.count(class_id) > 0 ){
      vector <Grade> :: iterator itrVectorGrade;
      for ( itrVectorGrade = classData[class_id].begin() ; itrVectorGrade != classData[class_id].end() ; itrVectorGrade++ ){
        if ( (*itrVectorGrade).studentID == id ){ // student record in this course existed before -> then updated
          (*itrVectorGrade).studentID = id;
          (*itrVectorGrade).classID = class_id;
          (*itrVectorGrade).mark = grade;
          cout << "Grade Updated" << endl;
          break;
        }
        if ( itrVectorGrade == classData[class_id].end() ){ // if record is new
          Grade g;
          g.studentID = id;
          g.classID = class_id;
          g.mark = grade;
          classData[class_id].push_back(g);
        }
        return true;
      }
    }
  } else {
    cout << "Student Not Exists" << endl;
    return false;
  }
}

bool Database::del_grade(string id, string class_id){
  if ( classData.count(class_id) > 0 ){
    vector <Grade> :: iterator itrVectorGrade;
    for ( itrVectorGrade = classData[class_id].begin() ; itrVectorGrade != classData[class_id].end() ; itrVectorGrade++ ){
      if ( (*itrVectorGrade).studentID == id ){
        classData[class_id].erase(itrVectorGrade);
        break;
      }
    }
    return true;
  } else {
    cout << "Record Not Exists" << endl;
    return false;
  }
}


//Display data
void Database::display_profiles(){
  vector < string > v;
  map < string , Profile > :: iterator itr;
  vector < string > :: iterator itr2;
  for ( itr = studentData.begin() ; itr != studentData.end() ; itr++ ){
    string information = "";
    information += (*itr).second.name;
    information += " ";
    information += (*itr).second.studentID;
    information += " ";
    information += (*itr).second.phoneNumber;
    v.push_back(information);
  }
  sort ( v.begin() , v.end() );
  for ( itr2 = v.begin() ; itr2 != v.end() ; itr2++ ){
    cout << (*itr2) << endl;
  }
}

void Database::display_grades(string class_id){
  double min , max , avg , count = 0;
  double sum = 0;
  string name;
  map < double , string > tempMap;
  vector < Grade > :: iterator itrVectorGrade;
//   cout << "HERE " << endl;

  for (  itrVectorGrade = classData[class_id].begin() ; itrVectorGrade != classData[class_id].end() ; itrVectorGrade++ ){

    if ( itrVectorGrade == classData[class_id].begin() ){
      min = (*itrVectorGrade).mark;
      max = (*itrVectorGrade).mark;
    }

    string information = "";
    map < string , Profile > :: iterator itrSystem; // searching the name
    for ( itrSystem = studentData.begin() ; itrSystem != studentData.end() ; itrSystem++ ){
      if ( (*itrSystem).first ==  (*itrVectorGrade).studentID ){
        string name = (*itrSystem).second.name;
      }
    }
    information += name;
    information += " ";
    information += (*itrVectorGrade).studentID;
    cout << "HERE " << information << endl;
    tempMap[ (*itrVectorGrade).mark ] = information;

    if ( (*itrVectorGrade).mark < min ) { min = (*itrVectorGrade).mark; }
    if ( (*itrVectorGrade).mark > max ) { max = (*itrVectorGrade).mark; }

    sum += (*itrVectorGrade).mark;
    count++ ;
  }

  map < double , string > :: iterator tempMapitr;
  for ( tempMapitr = tempMap.begin() ;  tempMapitr != tempMap.end() ; tempMapitr++ ){
    cout << (*tempMapitr).second << " " << (*tempMapitr).first << endl;
  }

  avg = sum / count;
  cout << "Min" << " " << min << endl;
  cout << "Max" << " " << max << endl;
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
