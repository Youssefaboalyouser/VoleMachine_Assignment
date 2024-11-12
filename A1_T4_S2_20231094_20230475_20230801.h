#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include <iostream>
#include <map>
#include <string>
using namespace std;

// Class to represent the CPU registers
class Registers
{
public:
    Registers();                                      // Constructor to initialize registers
    string get(const string &reg);                    // Retrieve the value of a specific register
    void set(const string &reg, const string &value); // Set the value of a specific register
    void display() const;                             // Display all registers and their values
    bool is_valid_register(char reg) const;           // Check if a given register is valid

private:
    map<string, string> registers; // Map to store register names and values
};

// Class to represent the memory of the machine
class Memory
{
public:
    Memory();                                          // Constructor to initialize memory
    string get(const string &addr);                    // Retrieve the value stored at a specific memory address
    void set(const string &addr, const string &value); // Set the value at a specific memory address
    void display() const;                              // Display all memory contents
    bool is_valid_memory(const string &addr) const;    // Check if a given memory address is valid

private:
    map<string, string> memory; // Map to store memory addresses and their values
};

// Class to represent the Control Unit (CU) of the machine
class CU
{
public:
    CU(Registers &regs, Memory &mem); // Constructor to initialize the control unit with registers and memory references

    void execute_instruction(const string &instruction, unsigned int &address); // Execute an instruction and update the address

    // Instruction-specific methods
    void load_memory_to_register(const string &instruction);           // Load a value from memory into a register
    void load_immediate_to_register(const string &instruction);        // Load an immediate value into a register
    void store_register_to_memory(const string &instruction);          // Store a register's value into memory
    void move_between_registers(const string &instruction);            // Move a value from one register to another
    void add_registers(const string &instruction);                     // Add the values of two registers and store the result in a destination register
    void immediate_floating_addition(const string &instruction);       // Perform an immediate floating-point addition
    void jump_to(const string &instruction, unsigned int &address);    // Jump to a specified memory address
    void jump_to_v2(const string &instruction, unsigned int &address); // Conditional jump based on a specified condition
    void bitwise_or(const string &instruction);                        // Perform a bitwise OR operation between two registers
    void bitwise_and(const string &instruction);                       // Perform a bitwise AND operation between two registers
    void bitwise_Xor(const string &instruction);                       // Perform a bitwise XOR operation between two registers
    void rotatefunction(const string &instruction);                    // Rotate the bits of a register
    string rotateHexValue(string reg, int steps);                      // Helper function to rotate a hexadecimal value by a given number of steps
    void bitwise_operation(const string &instruction, char op = '|');  // Perform a generic bitwise operation based on the provided operator
    void halt() const;                                                 // Halt the execution of the machine

private:
    Registers &registers; // Reference to the registers object
    Memory &memory;       // Reference to the memory object
};

// Class to represent the entire VOLE Machine
class VOLEMACHINE
{
public:
    VOLEMACHINE();                          // Constructor to initialize the VOLE machine
    void load_file(const string &filename); // Load instructions from a file into memory
    void run();                             // Run the loaded instructions
    void display() const;                   // Display the current state of registers and memory
    Registers registers;                    // Registers object
    Memory memory;                          // Memory object

private:
    CU control_unit;                       // Control Unit object
    unsigned int last_instruction_address; // Address of the last instruction loaded into memory
    string program_counter;                // Starting address of instructions
};

#endif //  VOLEMACHINE_H
