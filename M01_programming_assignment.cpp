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
    last_name = lname;
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

  std::string get_name() {
    std::string name = this->first_name + " " + this->last_name;
    return name;
  }

  int get_age() {
    return age;
  }

  Gender get_gender() {
    return gender;
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

  // TODO [] fix this
  //std::ostream& operator<<(std::ostream& out, const Participant& participant) {
  //  return out << participant.get_name() << '\n';
  //}
  
  
  void display() {
    std::cout << "name: " << get_name() << '\n';
  }

private:
  std::string first_name;
  std::string last_name;
  int age;
  Gender gender;
};


std::string get_first_name() {
  std::string first_name;
  std::cout << "Enter your first name: ";
  std::cin >> first_name;
  if (!std::isupper(first_name[0]))
    first_name[0] = std::toupper(first_name[0]);
  return first_name;
}

std::string get_last_name() {
  std::string last_name;
  std::cout << "Enter your last name: ";
  std::cin >> last_name;
  if (!std::isupper(last_name[0]))
    last_name[0] = std::toupper(last_name[0]);
  return last_name;
}

int get_age(Participant& participant) {
  int age;
  std::cout << "Enter " << participant.get_name() << "'s age: ";
  std::cin >> age;
  return age;
}

Gender get_gender(Participant& participant) {
  while (true) {
    char gender;
    std::cout << "Enter " << participant.get_name() << "'s you gender [m/f]: ";
    std::cin >> gender;
    gender = std::tolower(gender);
    if (gender == 'm') {
      return Male;
    } else if (gender == 'f') {
      return Female;
    } else {
      std::cerr << "Input was invalid. Please enter a [m] for male and [f] for female. Try again.\n";
    }
  }
}

int main() {
  static std::vector<Participant> participants;
  int option = 0;
  while (option != 4) {
    std::cout << "1. Add a New Participant\n"
              << "2. Collect Survey for Participant\n"
              << "3. Display Participants\n"
              << "4. Quit\n\n"
              << "Please enter a command to continue: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch(option) {
      case 1:
        {
          Participant new_participant;
          new_participant.set_firstname(get_first_name());
          new_participant.set_lastname(get_last_name());
          new_participant.set_age(get_age(new_participant));
          new_participant.set_gender(get_gender(new_participant));
          participants.push_back(new_participant);
          std::cout << '\n';
          break;
        }
      case 2:
       // if (participants.is_empty()) {
       //   std::cerr << "You must first add participants. Press one to add a new participant\n";
       //   break;
       // } else {
       //   break;
       // }
        break;
      case 3:
        if (participants.empty()) {
          std::cerr << "You must first add participants. Press one to add a new participant\n";
        } else {
          for (auto &participant : participants) {
            participant.display();
          }
        }
        break;
      case 4:
        break;
      default:
        std::cerr << "Input is not a valid option. Please select again..\n";
        break;
    }
  }
}

//class Participants {
//public:
//  Participants() {
//    static std::vector<Participant> participants = {};
//  }
//  void display_participants();
//  //void delete_a_participant(Participant participant_to_be_deleted) {
//  //  auto it = std::find(participants.begin(), participants.end(), participant_to_be_deleted);
//  //  if (it != participants.end()) {
//  //    participants.erase(it);
//  //  } else {
//  //    std::cerr << "User is not found\n";
//  //  }
//  //}
//  void add_a_participant(Participant new_participant) {
//    participants.push_back(new_participant);
//  }
//
//  //bool is_empty() {
//  //  if (this->participants.empty())
//  //    return true;
//  //  else 
//  //    return false;
//  //}
//private:
//  static std::vector<Participant> participants;
//};
