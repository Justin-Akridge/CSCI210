#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <cassert>

//	char formatDate[80];
//	time_t currentDate = time(NULL);
//	strftime(formatDate, 80, "%F", localtime(&currentDate)); // for date and time "%F %T"
//	string inv_date(formatDate);

struct Participant {
  int id;
  std::string first_name;
  std::string last_name;
  int age;
  std::string gender;
  bool study_mor = false;
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
    gender = std::tolower(gender);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (gender == 'm') {
      participant.gender = "Male";
      done = true;
    } else if (gender == 'f') {
      participant.gender = "Female";
      done = true;
    }
    else std::cerr << "Input was invalid. Please enter a [m] for male and [f] for female. Try again.\n";
  }
}

void display(Participant& participant) {
  std::cout << "Name: " << participant.first_name + " " << participant.last_name
            << "\nAge: "  << participant.age << "\nGender: " << participant.gender << '\n';
}

int main() {
  static int number_of_participants = 0;
  std::vector<Participant> participants;
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

      std::ofstream participants_file;
      //[] TODO: read and write files in binary for faster speeds.
      participants_file.open("participant.dat", std::ios::app);
      if (!participants_file) {
        std::cerr << "Error: Cannot open file!\n";
      }
      participants_file << new_participant;
      participants_file.close();
    } else if (option == 2) {
      std::ifstream input_file("participant.dat");
      if (input_file.fail()) {
        std::cerr << "The file does not exist!\n";
        return 1;
      }
      Participant participant;
      while (input_file >> participant) {
        participants.push_back(participant);
      }
      input_file.close();
    }

    // User needs to pick a participant to have take the survey
    for (auto &participant : participants) {
      display(participant);
    }
    bool done = false;
    while (!done) {
      std::cout << "\nPick a participant to take the survery: ";
      int participant_chosen_id;
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
  }
}
