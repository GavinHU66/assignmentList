/* database.cpp */
#include "database.h"

typedef struct Q6 {
  //Define variable to store a student profile
  string studentID;
  string name;
  double mark;
} Q6;

bool operator<( const Profile & a , const Profile & b ){
  return a.name < b.name;
}

bool operator<( const Q6 & a , const Q6 & b ){
  return a.mark < b.mark;
}

bool Database::add_profile(string id, string name, string phone){

  bool exist = false;
  vector <Profile> :: iterator itr;

  for ( itr=students.begin() ; itr!=students.end() ; itr++ ){
    if ( (*itr).studentID==id ){
      exist=true;
      (*itr).studentID = id;
      (*itr).name = name;
      (*itr).phoneNumber = phone;
      cout << "Profile Updated" << endl;
      break;
    }
  }

  if (!exist){
    Profile tmp;
    tmp.studentID = id;
    tmp.name = name;
    tmp.phoneNumber = phone;
    students.push_back(tmp);
  } 

  return true;
}

bool Database::del_profile(string id){

  vector <Profile> :: iterator itr;
  vector <Grade> :: iterator itr_g;
  bool exist = false;

  for ( itr=students.begin() ; itr!=students.end() ; itr++ ){
    if ( (*itr).studentID==id ){
      exist = true;
      students.erase(itr);
      break;
    }
  }
  if (exist){
    for ( itr_g=grades.begin() ; itr_g!=grades.end() ; itr_g++ ){
      if ( (*itr_g).studentID==id ) grades.erase(itr_g);
    }
  }
  if (!exist){
    cout << "Record Not Exists" << endl;
    return false;
  }

  return true;

}

bool Database::add_grade(string id, string class_id, double grade){

  vector <Profile> :: iterator itr;
  vector <Grade> :: iterator itr_g;
  bool exist_in_u = false;
  bool exist_in_c = false;

  for ( itr=students.begin() ; itr!=students.end() ; itr++ ){
    if ( (*itr).studentID==id ){
      exist_in_u = true;
      break;
    }
  }

  if (!exist_in_u){
    cout << "Student Not Exists" << endl;
    return false;
  }

  if (exist_in_u){
    for ( itr_g=grades.begin() ; itr_g!=grades.end() ; itr_g++ ){
      if ( (*itr_g).classID==class_id && (*itr_g).studentID==id ){
        exist_in_c = true;
        (*itr_g).mark = grade;
        cout << "Grade Updated" << endl;
        break;
      }
    }
    if (!exist_in_c){
      Grade tmp;
      tmp.studentID = id;
      tmp.classID = class_id;
      tmp.mark = grade;
      grades.push_back(tmp);
    }
  }

  return true;

}

// del_grade to delete his grade but not himself
bool Database::del_grade(string id, string class_id){
    
  bool exist_in_c = false;
  vector <Grade> :: iterator itr;

  for ( itr=grades.begin() ; itr!=grades.end() ; itr++ ){
    if ( (*itr).classID==class_id && (*itr).studentID==id ){
      exist_in_c = true;
      (*itr).mark = -1;
      break;
    }
  }
  if (!exist_in_c){
    cout << "Record Not Exists" << endl;
    return false;
  }

  return true;

}

void Database::display_profiles(){

  vector <Profile> :: iterator itr;

  sort( students.begin() , students.end() );
  for ( itr=students.begin() ; itr!=students.end() ; itr++ ){
    cout << (*itr).name << " " << (*itr).studentID << " " << (*itr).phoneNumber << endl;
  }

}

void Database::display_grades(string class_id){

  vector <Q6> content;

  double mark;
  string id;
  string name;

  double min=100 , max=0 , avg;
  double count=0;
  double sum = 0;

  vector <Grade> :: iterator itr;
  vector <Q6> :: iterator itr_q6;

  for ( itr=grades.begin() ; itr!=grades.end() ; itr++ ){
    if ( (*itr).classID == class_id ){
      if ( (*itr).mark>0 ){
        if ( (*itr).mark >= max ) max = (*itr).mark;
        if ( (*itr).mark <= min ) min = (*itr).mark;
        count++;
        id = (*itr).studentID;
        mark = (*itr).mark;
        sum += mark;

        vector <Profile> :: iterator itr_p;
        for ( itr_p=students.begin() ; itr_p!=students.end() ; itr_p++ ){
          if ( (*itr_p).studentID == id ){
            name = (*itr_p).name;
          }
        }

        Q6 tmp;
        tmp.studentID = id;
        tmp.name = name;
        tmp.mark = mark;
    
        content.push_back(tmp);
      }


    }
  }

  sort( content.begin() , content.end() );

  for ( itr_q6=content.begin() ; itr_q6!=content.end() ; itr_q6++ ){
    cout << (*itr_q6).name << " " << (*itr_q6).studentID << " " << (*itr_q6).mark << endl;
  }

  avg = sum / count;

  cout << "Min" << " " << min << endl;
  cout << "Max" << " " << max << endl;
  cout << "Average" << " " << avg << endl;

}