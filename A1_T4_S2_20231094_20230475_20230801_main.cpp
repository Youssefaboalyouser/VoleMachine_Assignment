#include "A1_T4_S2_20231094_20230475_20230801.cpp"
#include <iostream>
using namespace std;
int main()
{
    cout << ">>> VOLE MACHINE SIMULATOR <<<*\n";
    VOLEMACHINE machine;
    string choice;

    while (true)
    {
        cout << "\n(1) Upload instructions file and run\n(2) Display memory\n(3) Reset Memory\n(4) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1")
        {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            machine.load_file(filename);

            // Run only if the file was loaded successfully
            ifstream testFile(filename);
            if (testFile)
            {
                machine.run();
            }
            testFile.close();
        }
        else if (choice == "2")
        {
            machine.display();
        }
        else if (choice == "3")
        {
            machine.registers = Registers();
            machine.memory = Memory();
            cout << "+++>> Memory and Register have been reset" << endl;
        }
        else if (choice == "4")
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
