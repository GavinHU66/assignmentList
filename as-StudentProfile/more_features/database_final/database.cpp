/* database.cpp */
#include "database.h"

bool Database::add_profile(string id, string name, string phone){
  if ( studentData.count(id) > 0 ){ // if he is already existed
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

  // if the student exits
  if ( studentData.count(id) > 0 ){

    // delete him from the student profile data
    studentData.erase(id);

    // to find this student by matching his uid in class profile data
    map < string , vector<Grade> > :: iterator itrMap;
    for ( itrMap = classData.begin() ; itrMap != classData.end() ; itrMap++ ){
      
      // now we are in a specific class, say comp2123, the searching inside the student enrolled in this course
      vector <Grade> :: iterator itrVectorGrade;
      for ( itrVectorGrade = (*itrMap).second.begin() ; itrVectorGrade != (*itrMap).second.end() ; itrVectorGrade++ ){

        // now his is found, by his uid
        if ( (*itrVectorGrade).studentID == id ){
          // delete this student from the enrolled students i.e., from <Grade> of comp2123
          (*itrMap).second.erase(itrVectorGrade);
          break;
        }
      }
    }
    return true;
  }

  // if the student does not exit, then show "Record Not Exists" and return false
  else {
    cout << "Record Not Exists" << endl;
    return false;
  }
}

bool Database::add_grade(string id, string class_id, double grade){

  // if this student exists in the student profile database and  he also enrolled in comp2123
  if ( studentData.count(id) > 0 ){
    vector <Grade> :: iterator itrVectorGrade;
    bool his_is_newguy = true;
    for ( itrVectorGrade = classData[class_id].begin() ; itrVectorGrade != classData[class_id].end() ; itrVectorGrade++ ){
      if ( (*itrVectorGrade).studentID == id ){ // student record in this course existed before -> then updated
        (*itrVectorGrade).studentID = id;
        (*itrVectorGrade).classID = class_id;
        (*itrVectorGrade).mark = grade;
        cout << "Grade Updated" << endl;
        his_is_newguy = false;
        break;
      }
    }
    if ( his_is_newguy ){ // if student did not ever enrolled in comp2123 before
        Grade g;
        g.studentID = id;
        g.classID = class_id;
        g.mark = grade;
        classData[class_id].push_back(g);
    }
    return true;
  } 
  
  // if his does not exist, show "Student Not Exists" and return false
  else {
    cout << "Student Not Exists" << endl;
    return false;
  }
}

// del_grade to delete his grade or himself?
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
    
  double min , max , avg;
  double count=0;
  double sum = 0;

  map < double , string > tempMap;
  vector <Grade> :: iterator itrVectorGrade;
  
  min = (*classData[class_id].begin()).mark;
  max = (*classData[class_id].begin()).mark;

  for ( itrVectorGrade = classData[class_id].begin() ; itrVectorGrade != classData[class_id].end() ; itrVectorGrade++ ){
    string tmpString = "";
    
    map < string , Profile > :: iterator itrSystem; // searching the name
    for ( itrSystem = studentData.begin() ; itrSystem != studentData.end() ; itrSystem++ ){
      if ( (*itrSystem).first ==  (*itrVectorGrade).studentID ){
        tmpString += (*itrSystem).second.name;
        break;
      }
    }
    tmpString += " ";
    tmpString += (*itrVectorGrade).studentID;
    tempMap[(*itrVectorGrade).mark] = tmpString;

    if ( (*itrVectorGrade).mark <= min ) { min = (*itrVectorGrade).mark; }
    if ( (*itrVectorGrade).mark >= max ) { max = (*itrVectorGrade).mark; }

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