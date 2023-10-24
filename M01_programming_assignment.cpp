#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <cassert>

enum Gender {Male, Female};

class Participant {
public:
  void set_firstname(std::string fname) {
    first_name = fname;
  }

  void set_lastname(std::string lname) {
    first_name = lname;
  }

  void set_age(int init_age) {
    age = init_age;
  }

  void set_gender(Gender gender) {
    assert(gender == Female || gender == Male);
    if (gender == Female) 
      gender = Female;
    else
      gender = Male;
  }

  bool operator==(Participant const& participant) {
    if (this->first_name == participant.first_name &&
        this->last_name  == participant.last_name  &&
        this->age        == participant.age        &&
        this->gender     == participant.gender) {
      return true;
    } else {
      return false;
    }
  }

private:
  std::string first_name;
  std::string last_name;
  int age;
  std::string gender;
};

class Participants {
public:
  Participants() {
    static std::vector<Participant> participants = {};
  }
  void display_participants();
  void delete_a_participant(Participant participant_to_be_deleted) {
    auto it = std::find(this->participants.begin(), this->participants.end(), participant_to_be_deleted);
    if (it != participants.end()) {
      participants.erase(it);
    } else {
      std::cerr << "User is not found\n";
    }
  }
  void add_a_participant(Participant new_participant) {
    participants.push_back(new_participant);
  }

  //bool is_empty() {
  //  if (this->participants.empty())
  //    return true;
  //  else 
  //    return false;
  }
private:
  static std::vector<Participant> participants;
};

std::string get_first_name() {
  std::string first_name;
  std::cout << "Enter your first name: ";
  std::cin >> first_name;
  return first_name;
}

std::string get_last_name() {
  std::string last_name;
  std::cout << "Enter your last name: ";
  std::cin >> last_name;
  return last_name;
}

int get_age() {
  int age;
  std::cout << "Enter you age: ";
  std::cin >> age;
  return age;
}

Gender get_gender() {
  while (true) {
    char gender;
    std::cout << "Enter your gender male or female [m/f]: ";
    std::cin >> gender;
    gender = gender - '0';
    if (gender == 'm') {
      return Male;
    } else if (gender == 'f') {
      return Female;
    } else {
      std::cerr << "Input was invalid. Please try again.\n";
    }
  }
}

int main() {
  Participants participants;
  int option = 0;
  while (option != 4) {
    std::cout << "1 New participant\n"
              << "2 Collect survey\n"
              << "3 Display participants\n"
              << "4 Quit\n";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch(option) {
      case 1:
        {
          Participant new_participant;
          new_participant.set_firstname(get_first_name());
          new_participant.set_lastname(get_last_name());
          new_participant.set_age(get_age());
          new_participant.set_gender(get_gender());
          participants.add_a_participant(new_participant);
          break;
        }
      case 2:
       // if (participants.is_empty()) {
       //   std::cerr << "You must first add participants. Press one to add a new participant\n";
       //   break;
       // } else {
          break;
       // }
        break;
      case 3:
        break;
      case 4:
        break;
      default:
        std::cerr << "Input is not a valid option. Please select again..\n";
        break;
    }
  }
}
