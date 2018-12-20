/* database_main.cpp */
#include "database.h"

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