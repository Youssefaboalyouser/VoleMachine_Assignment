#include "VoleMachine.cpp"
#include <iostream>
using namespace std;

int main()
{
    cout << ">>> VOLE MACHINE SIMULATOR <<<\n";
    VOLEMACHINE machine;  // Instantiate a VOLEMACHINE object
    string choice;

    while (true)
    {
        cout << "\n(1) Upload instructions file and run\n(2) Display memory\n(3) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1")
        { //  Load instructions file and run
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            machine.load_file(filename);

            // Run only if the file was loaded successfully
            ifstream testFile(filename);
            if (testFile) {
                machine.run();
            }
            testFile.close();
        }
        else if (choice == "2")
        { // Display memory
            machine.display();
        }
        else if (choice == "3")
        {
            cout << "\n======>>> GOOD BYE <<<======" << endl;
            return 0;
        }
        else
        {
            cout << "Error: Please enter a valid choice!\n";
        }
    }
}

