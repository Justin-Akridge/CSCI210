/* Program name: surverydatamanagement.cpp
 * Author: Justin Akridge 
 * Date last updated: 10/29/2023 
 * Purpose: This program keep track of participants and surveys taken
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <cassert>

struct Participant {
  int id;
  std::string first_name;
  std::string last_name;
  int age;
  std::string gender;
  bool study_mor = false;

//  friend std::ostream& operator<<(std::ostream& out, const Participant& participant) {
//    out << id << '\n' << participant.first_name << '\n' << participant.last_name << '\n' << participant.age << '\n' << participant.gender << '\n';
//    return out;
//
  friend std::ostream& operator<<(std::ostream& out, const Participant& participant) {
    out << participant.id << '\n' << participant.first_name << '\n' << participant.last_name << '\n' << participant.age << '\n' << participant.gender << '\n';
    return out;
  }
  friend std::istream& operator>>(std::istream& in, Participant& participant) {
    in >> participant.id >> participant.first_name >> participant.last_name >> participant.age >> participant.gender;
    return in;
  }
};

void set_first_name(Participant& participant) {
  std::cout << "Enter your first name: ";
  std::cin >> participant.first_name;
  if (!std::isupper(participant.first_name[0]))
    participant.first_name[0] = std::toupper(participant.first_name[0]);
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void set_last_name(Participant& participant) {
  std::cout << "Enter your last name: ";
  std::cin >> participant.last_name;
  if (!std::isupper(participant.last_name[0]))
    participant.last_name[0] = std::toupper(participant.last_name[0]);
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void set_age(Participant& participant) {
  bool done = false;
  while (!done) {
    std::string name = participant.first_name + " " + participant.last_name; 
    std::cout << "Enter " << name << "'s age: ";
    std::string input_age;
    std::cin >> input_age;
    bool is_valid_number = true;
    for (const auto &digit: input_age) {
      if (!std::isdigit(digit))
        is_valid_number = false; 
    }
    if (is_valid_number) {
      participant.age = std::stoi(input_age);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      done = true;
    } else {
      std::cerr << "Invalid input. Input must be an integer\n";
    }
  }
}


void set_gender(Participant& participant) {
  bool done = false;
  while (!done) {
    char gender;
    std::cout << "Enter " << participant.first_name + " " + participant.last_name << "'s gender [m/f]: ";
    std::cin >> gender;
    gender = std::toupper(gender);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (gender == 'M' || gender == 'F') {
      participant.gender = gender;
      done = true;
    } else {
      std::cerr << "Input was invalid. Please enter a [m] for male and [f] for female. Try again.\n";
    }
  }
}

void display(Participant& participant) {
  std::cout << "Name: " << participant.first_name + " " << participant.last_name
            << "\nAge: "  << participant.age << "\nGender: " << participant.gender << '\n';
}

bool validate_input(char input) {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (!std::islower(input)) {
    input = std::tolower(input);
  }
  if (input == 'y' || input == 'n') {
    return true;
  } else {
    return false;
  }
}

void take_study_mor_survery(int id) {
  char input; 
  bool has_headaches = false;
  bool done = false;
  while (!done) {
    std::cout <<"Did you have any headaches using StudyMor? [y/n]: ";
    std::cin >> input;
    if (validate_input(input)) {
      done = true;
    } else {
      std::cerr << "Input is invalid. Please enter a [y] for yes and [n] for no\n";
    }
  }
  if (input == 'y') {
    has_headaches = true;
  }

  bool has_constipation = false;
  done = false;
  while (!done) {
    std::cout <<"Did you have any constipation using StudyMor? [y/n]: ";
    std::cin >> input;
    if (validate_input(input)) {
      done = true;
    } else {
      std::cerr << "Input is invalid. Please enter a [y] for yes and [n] for no\n";
    }
  }
  if (input == 'y') {
    has_constipation = true;
  }

  bool has_difficulty_sleeping = false;
  done = false;
  while (!done) {
    std::cout <<"Did you experience any difficulty sleeping while using StudyMor? [y/n]: ";
    std::cin >> input;
    if (validate_input(input)) {
      done = true;
    } else {
      std::cerr << "Input is invalid. Please enter a [y] for yes and [n] for no\n";
    }
  }
  if (input == 'y') {
    has_difficulty_sleeping = true;
  }

  std::vector<std::string> side_effects;
  std::cout << "List any other potential side effects, you experienced using StudyMor\nSide effects: ";
  std::string side_effect;
  while (std::cin >> side_effect) {
    side_effects.push_back(side_effect);
  }

  bool likes_study_mor = false;
  done = false;
  while (!done) { 
    std::cout <<"Did you feel like you could study more using StudyMor? [y/n]: ";
    std::cin >> input;
    if (validate_input(input)) {
      done = true;
    } else {
      std::cerr << "Input is invalid. Please enter a [y] for yes and [n] for no\n";
    }
  }
  if (input == 'y') {
    likes_study_mor = true;
  }
  std::ofstream out_file;
  out_file.open("survery.dat", std::ios::app);
  if (!out_file) {
    std::cerr << "File is not found!\n";
  }

  char formatDate[80];
  time_t currentDate = time(NULL);
  strftime(formatDate, 80, "%F", localtime(&currentDate)); // for date and time "%F %T"
  std::string inv_date(formatDate);
  out_file << inv_date << has_headaches << has_constipation << has_difficulty_sleeping << likes_study_mor;
  for (auto &side_effect : side_effects) {
    out_file << side_effect;
  // [_] TODO: all variables with participant id to file "survey.dat". 
  }
}
int main() {
  static int number_of_participants = 0;
  std::vector<Participant> participants;
  std::cout << "Welcome to the Westlake Research Hospital StudyMor Study!\n\n";
  int option = 0;
  while (option != 4) {
    std::cout << "1. Add a New Participant\n"
              << "2. Collect Survey for Participant\n"
              << "3. Display Participants\n"
              << "4. Quit\n\n"
              << "Please enter a command to continue: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (option == 1) {
      Participant new_participant;
      new_participant.id = number_of_participants;
      if (new_participant.id % 2 == 0) {
        new_participant.study_mor = true;
      }
      number_of_participants++;
      set_first_name(new_participant);
      set_last_name(new_participant);
      set_age(new_participant);
      set_gender(new_participant);

      participants.push_back(new_participant);

      std::cout << '\n';
      std::ofstream participants_file;
      //[] TODO: Convert to write files in binary for faster write time. Do this below.
      //participants_file.open("participant.dat", std::ios::app);
      //participants_file.write(reinterpret_cast<const char*> (&new_participant), sizeof(Participant));
      participants_file.open("participant.dat", std::ios::app);
      if (!participants_file) {
        std::cerr << "Error: Cannot open file!\n";
      }
      participants_file << new_participant;
      participants_file.close();
    } else if (option == 2) {
      //std::ifstream input_file("participant.dat");
      //if (input_file.fail()) {
      //  std::cerr << "The file does not exist!\n";
      //  return 1;
      //}

      //// [_] TODO: Convert to read binary file for faster read time. Do this below
      ////participants_file.write(reinterpret_cast<const char*> (&new_participant), sizeof(Participant));
      //Participant participant;
      //while (input_file >> participant) {
      //  participants.push_back(participant);
      //}
      //input_file.close();

      //// User needs to pick a participant to have take the survey
      //for (auto &participant : participants) {
      //  display(participant);
      //}
      bool done = false;
      int participant_chosen_id;
      while (!done) {
        std::cout << "\nPick a participant to take the survery: ";
        std::cin >> participant_chosen_id;
        Participant participant_chosen;
        for (int i = 0; i < participants.size(); i++) {
          if (participants[i].id == participant_chosen_id) {
            participant_chosen = participants[i];
            done = true;
          }
        }
        if (!done) {
          std::cerr << "Participant chosen does not exist in the list. Please enter a valid ID.\n";
        }
      }
      take_study_mor_survery(participant_chosen_id);
    } else if (option == 3) {
      for (int i = 0; i < participants.size(); i++) {
        std::string name = participants[i].first_name + " " + participants[i].last_name;
        std::cout << "ID: " << participants[i].id << "\nName: " << name << "\nAge: " << participants[i].age << "\nGender: " << participants[i].gender << '\n';
        std::cout << "Study More survey: "; 
        if (participants[i].study_mor) {
          std::cout << "Yes\n\n";
        } else {
          std::cout << "No\n\n";
        }
        std::cout << "**********************************\n\n";
      }
    }
  }
}
