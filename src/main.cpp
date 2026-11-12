
#include <termios.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>

#include "mylib.h"

using namespace std;

class Employees {
 private:
  string name;

 public:
  void setName(string n) { name = n; }

  string getName() { return name; }
};

char getch_linux() {
  char buf = 0;  // Variable to store the input character

  struct termios old = {0};  // Structure to save current terminal settings

  // Save the current terminal settings
  tcgetattr(0, &old);

  // Disable Canonical Mode (do not wait for Enter key)
  old.c_lflag &= ~ICANON;

  // Disable Echo so typed characters are not displayed
  old.c_lflag &= ~ECHO;

  // Require at least one character to be read
  old.c_cc[VMIN] = 1;

  // No timeout while waiting for input
  old.c_cc[VTIME] = 0;

  // Apply the modified settings immediately
  tcsetattr(0, TCSANOW, &old);

  // Read a single character immediately from the keyboard
  read(0, &buf, 1);

  // Re-enable Canonical Mode
  old.c_lflag |= ICANON;

  // Re-enable Echo
  old.c_lflag |= ECHO;

  // Restore the terminal to its original settings
  tcsetattr(0, TCSADRAIN, &old);

  // Return the character that was read
  return buf;
}
void enterEmployees(Employees emp[], int &employeeCount) {
  employeeCount = 0;

  cout << "\033[2J\033[H";

  display(5, 3, "Enter Employee Names:");
  display(5, 4, "Press ESC to return to menu");

  for (int i = 0; i < 20; i++) {
    string n;
    char key;

    cout << "\nEnter employee " << i + 1 << ": " << flush; 
    // you have to press ESC twice to check whether you inputed an arrrow key or not
    while (true) {
      key = getch_linux();

      if (key == '\033') {
        char next = getch_linux();

        if (next == '[' || next == 'O') {
          getch_linux();
          continue;
        }

        return;
      }

      if (key == '\n' || key == '\r') {
        cout << endl;
        break;
      }

      if (key == 127) {
        if (!n.empty()) {
          n.pop_back();
          cout << "\033[1D \033[1D" << flush;
        }
        continue;
      }

      n += key;
      cout << key << flush;
    }

    if (!n.empty()) {
      emp[i].setName(n);
      employeeCount++;
    }
  }
}
void showMenu() {
  cout << "\033[2J\033[H";

  setColor("yellow");
  display(3, 3, "->");

  display(5, 3, "Menu");

  setColor("white");

  display(5, 4, "Employees");
  display(5, 5, "Screen 1");
  display(5, 6, "Exit");
}

int main() {
  Employees emp[20];

  int employeeCount = 0;
  int count1 = 0;

  showMenu();

  while (true) {
    char key = getch_linux();

    if (key == '\033') {
      char bracket = getch_linux();
      char arrow = getch_linux();

      if (bracket == '[') {
        if (arrow == 'B') {
          if (count1 == 0) {
            setColor("white");
            display(3, 3, "\033[2K");
            display(3, 3, "  Menu");

            setColor("yellow");
            display(3, 4, "\033[2K");
            display(3, 4, "->Employees");

            count1++;

          } else if (count1 == 1) {
            setColor("white");
            display(3, 4, "\033[2K");
            display(3, 4, "  Employees");

            setColor("yellow");
            display(3, 5, "\033[2K");
            display(3, 5, "->Screen 1");

            count1++;

          } else if (count1 == 2) {
            setColor("white");
            display(3, 5, "\033[2K");
            display(3, 5, "  Screen 1");

            setColor("yellow");
            display(3, 6, "\033[2K");
            display(3, 6, "->Exit");

            count1 = 3;

          } else if (count1 == 3) {
            setColor("white");
            display(3, 6, "\033[2K");
            display(3, 6, "  Exit");

            setColor("yellow");
            display(3, 3, "\033[2K");
            display(3, 3, "->Menu");

            count1 = 0;
          }
        } else if (arrow == 'A') {
          if (count1 == 3) {
            setColor("white");
            display(3, 6, "\033[2K");
            display(3, 6, "  Exit");

            setColor("yellow");
            display(3, 5, "\033[2K");
            display(3, 5, "->Screen 1");

            count1 = 2;

          } else if (count1 == 2) {
            setColor("white");
            display(3, 5, "\033[2K");
            display(3, 5, "  Screen 1");

            setColor("yellow");
            display(3, 4, "\033[2K");
            display(3, 4, "->Employees");

            count1 = 1;

          } else if (count1 == 1) {
            setColor("white");
            display(3, 4, "\033[2K");
            display(3, 4, "  Employees");

            setColor("yellow");
            display(3, 3, "\033[2K");
            display(3, 3, "->Menu");

            count1 = 0;

          } else if (count1 == 0) {
            setColor("white");
            display(3, 3, "\033[2K");
            display(3, 3, "  Menu");

            setColor("yellow");
            display(3, 6, "\033[2K");
            display(3, 6, "->Exit");

            count1 = 3;
          }
        }else if(arrow=='H'){
            setColor("white");
            display(3, 4, "\033[2K");
            display(3, 4, "  Employees");
            display(3, 5, "\033[2K");
            display(3, 5, "  Screen 1");
            display(3, 6, "\033[2K");
            display(3, 6, "  Exit");
            setColor("yellow");
            display(3, 3, "\033[2K");
            display(3, 3, "->Menu");
            count1=0;
            
        }else if (arrow=='F'){
            setColor("white");
            display(3, 4, "\033[2K");
            display(3, 4, "  Employees");
            display(3, 5, "\033[2K");
            display(3, 5, "  Screen 1");
            display(3, 3, "\033[2K");
            display(3, 3, "  Menu");
            setColor("yellow");
            display(3, 6, "\033[2K");
            display(3, 6, "->Exit");
            count1=3;
        }
      }
    } else if (key == '\n' || key == '\r') {
      setColor("white");
      if (count1 == 1) {
        enterEmployees(emp, employeeCount);

        showMenu();

        count1 = 0;
      } else if (count1 == 2) {
        cout << "\033[2J\033[H";

        display(5, 3, "Employee Names:");

        if (employeeCount == 0) {
          cout << "\nNo employees entered yet.";
        } else {
          for (int i = 0; i < employeeCount; i++) {
            cout << "\n    " << i + 1 << ": " << emp[i].getName();
          }
        }

        display(5, 22, "Press ESC to return to menu...");

        while (true) {
          char key = getch_linux();

          if (key == '\033') {
            break;
          }
        }

        showMenu();
        count1 = 0;
      } else if (count1 == 3) {
        cout << "\033[2J\033[H" << flush;
        return 0;
      }
    }
  }

  return 0;
}
