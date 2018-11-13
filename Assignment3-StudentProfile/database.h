/* database.h */

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
