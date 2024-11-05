#include "VoleMachine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// ============================== Registers Class ==============================
// The Registers class manages a set of 16 registers, identified by hexadecimal keys "0" to "F".
Registers::Registers()
{
    // Initialize each register with a default value of "00"
    registers = {
        {"0", "00"}, {"1", "00"}, {"2", "00"}, {"3", "00"}, {"4", "00"}, {"5", "00"}, {"6", "00"}, {"7", "00"}, {"8", "00"}, {"9", "00"}, {"A", "00"}, {"B", "00"}, {"C", "00"}, {"D", "00"}, {"E", "00"}, {"F", "00"}};
}
// Returns the value of a specified register
string Registers::get(const string &reg)
{
    if (registers.find(reg) != registers.end())
    {
        return registers[reg];
    }
    throw invalid_argument("Invalid register: " + reg);
}
// Sets a specific register to a given value
void Registers::set(const string &reg, const string &value)
{
    if (registers.find(reg) != registers.end())
    {
        registers[reg] = value;
    }
    else
    {
        throw invalid_argument("Invalid register: " + reg);
    }
}
// Displays the current state of all registers
void Registers::display() const
{
    cout << "Registers:\n";
    cout << "====================\n";
    for (const auto &reg : registers)
    {
        cout << reg.first << ": " << reg.second << "  ";
    }
    cout << endl;
}
// Checks if a given character corresponds to a valid register
bool Registers::is_valid_register(char reg) const
{
    return registers.find(string(1, reg)) != registers.end();
}

// ============================== Memory Class ==============================
// The Memory class represents memory locations with addresses from "00" to "FF".

Memory::Memory()
{
    // Initialize each memory location to "00" in hexadecimal format
    for (int i = 0; i <= 0xFF; ++i)
    {
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << i;
        memory[ss.str()] = "00";
    }
}
// Retrieves the value at a specific memory address
string Memory::get(const string &addr)
{
    if (memory.find(addr) != memory.end())
    {
        return memory[addr];
    }
    throw invalid_argument("Invalid memory address: " + addr);
}
// Sets a value at a specific memory address
void Memory::set(const string &addr, const string &value)
{
    if (memory.find(addr) != memory.end())
    {
        memory[addr] = value;
    }
    else
    {
        throw invalid_argument("Invalid memory address: " + addr);
    }
}
// Displays the current state of memory
void Memory::display() const
{
    cout << "Memory:\n";
    cout << "====================\n";
    int count = 0;
    for (const auto &mem : memory)
    {
        cout << mem.first << ": " << mem.second << "  ";
        if (++count % 8 == 0)
            cout << endl;
    }
}
// Checks if a given address is valid in memory
bool Memory::is_valid_memory(const string &addr) const
{
    return memory.find(addr) != memory.end();
}

// ============================== CU (Control Unit) Class ==============================
// The CU class interprets and executes instructions, coordinating between the Registers and Memory.
CU::CU(Registers &regs, Memory &mem) : registers(regs), memory(mem) {}
// Executes an instruction based on its opcode
void CU::execute_instruction(const string &instruction, unsigned int &address)
{
    char opcode = instruction[0];
    // Executes specific instructions based on the opcode
        // Examples include loading values, storing values, arithmetic, and bitwise operations
    switch (opcode)
    {
    case '1':
        load_memory_to_register(instruction);
        break;
    case '2':
        load_immediate_to_register(instruction);
        break;
    case '3':
        store_register_to_memory(instruction);
        break;
    case '4':
        move_between_registers(instruction);
        break;
    case '5':
        add_registers(instruction);
        break;
    case '6':
        immediate_floating_addition(instruction);
        break;
    case '7':
        bitwise_or(instruction);
        break;
    case '8':
        bitwise_and(instruction);
        break;
    case '9':
        bitwise_Xor(instruction);
        break;
    case 'A':
        rotatefunction(instruction);
        break;
    case 'B':
        jump_to(instruction, address);
        break;
    case 'C':
        halt();
        break;
    case 'D':
        jump_to_v2(instruction, address);
        break;
    case '0':
        cout << "There is no Insturction at memroy address: " << address << endl;
        cout << "Program counter now in: " << address << " memory address" << endl;
        halt();
        break;
    default:
        cout << "Unknown opcode: " << opcode << endl;
    }
}

// Implementing each instruction method (e.g., loading memory to a register)

void CU::load_memory_to_register(const string &instruction)
{
    string reg = instruction.substr(1, 1);
    string addr = instruction.substr(2, 2);
    if (registers.is_valid_register(reg[0]) && memory.is_valid_memory(addr))
    {
        registers.set(reg, memory.get(addr));
        cout << "Loaded memory[" << addr << "] into register R" << reg << "\n";
        registers.display();
        memory.display();
    }
    else
    {
        cout << "Invalid register or memory address!\n";
    }
}

void CU::load_immediate_to_register(const string &instruction)
{
    string reg = instruction.substr(1, 1);
    string value = instruction.substr(2, 2);
    if (registers.is_valid_register(reg[0]))
    {
        registers.set(reg, value);
        cout << "Loaded immediate " << value << " into register R" << reg << "\n";
        registers.display();
        memory.display();
    }
    else
    {
        cout << "Invalid register!\n";
    }
}

void CU::store_register_to_memory(const string &instruction)
{
    string reg = instruction.substr(1, 1);
    string addr = instruction.substr(2, 2);
    if (registers.is_valid_register(reg[0]) && memory.is_valid_memory(addr))
    {
        memory.set(addr, registers.get(reg));
        cout << "Stored register R" << reg << " into memory[" << addr << "]\n";
        registers.display();
        memory.display();
    }
    else
    {
        cout << "Invalid register or memory address!\n";
    }
}

void CU::move_between_registers(const string &instruction)
{
    string src = instruction.substr(2, 1);
    string dest = instruction.substr(3, 1);
    if (registers.is_valid_register(src[0]) && registers.is_valid_register(dest[0]))
    {
        registers.set(dest, registers.get(src));
        cout << "Moved value from R" << src << " to R" << dest << "\n";
        registers.display();
        memory.display();
    }
    else
    {
        cout << "Invalid register!\n";
    }
}
// Adds values in two registers and stores the result in another register
void CU::add_registers(const string &instruction)
{
    string reg1 = instruction.substr(2, 1);
    string reg2 = instruction.substr(3, 1);
    string dest = instruction.substr(1, 1);

    if (registers.is_valid_register(reg1[0]) && registers.is_valid_register(reg2[0]) && registers.is_valid_register(dest[0]))
    {
        // Convert hex values from registers to integers
        unsigned int value1 = stoi(registers.get(reg1), nullptr, 16);
        unsigned int value2 = stoi(registers.get(reg2), nullptr, 16);

        // Perform addition and apply modulo 256 to handle overflow
        unsigned int sum = (value1 + value2) % 256;

        // Convert the sum back to hexadecimal with two-digit format
        stringstream ss;
        ss << uppercase << hex << setw(2) << setfill('0') << sum;

        // Store the result in the destination register
        registers.set(dest, ss.str());

        cout << "Added R" << reg1 << " and R" << reg2 << " (modulo 256), result put in R" << dest << " as " << ss.str() << "\n";
        registers.display();
        memory.display();
    }
    else
    {
        cout << "Invalid register!\n";
    }
}
// Performs a floating-point addition using specific bits for mantissa and exponent
void CU::immediate_floating_addition(const string &instruction)
{
    string dest = instruction.substr(1, 1);
    string Reg1 = instruction.substr(2, 1);
    string Reg2 = instruction.substr(3, 1);
    if (!(registers.is_valid_register(dest[0]) && registers.is_valid_register(Reg1[0]) && registers.is_valid_register(Reg2[0])))
    {
        cout << "Invalid register in immediate floating addition!" << endl;
        return;
    }
    int bias = 4;
    auto hex_to_bin = [](const string &hex)
    {
        return bitset<8>(stoi(hex, nullptr, 16)).to_string();
    };
    auto binToFloat = [bias](const string &bin)
    {
        int sign_bit = bin[0] - '0';
        int exponent = stoi(bin.substr(1, 3), nullptr, 2) - bias;
        float mantissa = 0.0;
        for (int i = 0; i < 4; ++i)
            if (bin[4 + i] == '1')
                mantissa += pow(2, -(i + 1));
        return pow(-1, sign_bit) * (1 + mantissa) * pow(2, exponent);
    };
    auto float_to_bin = [bias](float value)
    {
        string res(8, '0');
        res[0] = (value < 0) ? '1' : '0';
        value = fabs(value);
        int exponent = 0;
        while (value >= 2)
        {
            value /= 2;
            exponent++;
        }
        while (value < 1)
        {
            value *= 2;
            exponent--;
        }
        res.replace(1, 3, bitset<3>(exponent + bias).to_string());
        float mantissa = value - 1;
        for (int i = 0; i < 4; ++i)
        {
            if (mantissa >= pow(2, -(i + 1)))
            {
                res[4 + i] = '1';
                mantissa -= pow(2, -(i + 1));
            }
        }
        return res;
    };
    auto bin_to_hex = [](const string &bin)
    {
        int hex_result = bitset<8>(bin).to_ulong();
        stringstream ss;
        ss << uppercase << hex << setw(2) << setfill('0') << hex_result;
        return ss.str();
    };
    float srcFloat_one = binToFloat(bin_to_hex(registers.get(Reg1)));
    float srcFloat_tow = binToFloat(hex_to_bin(registers.get(Reg2)));
    float resultFloat = srcFloat_one + srcFloat_tow;
    string result_in_hex = bin_to_hex(float_to_bin(resultFloat));
    registers.set(dest, result_in_hex);
    cout << "Added floating-point values of R" << Reg1 << " and R" << Reg2 << ", result stored in R" << dest << " as " << result_in_hex << endl;
    registers.display();
    memory.display();
}

// Handles jump instructions to change the program counter
void CU::jump_to(const string &instruction, unsigned int &address)
{
    string reg = instruction.substr(1, 1);
    string addr = instruction.substr(2, 2);

    if (registers.get(reg) == registers.get("0"))
    {
        address = stoi(addr, nullptr, 16) - 1;
    }
    cout <<"program counter at memory address: " << address << "will execut what inside!" <<endl;
    registers.display();
    memory.display();
}

void CU::jump_to_v2(const string &instruction, unsigned int &address)
{
    string reg = instruction.substr(1, 1);
    string addr = instruction.substr(2, 2);

    if (registers.get(reg) > registers.get("0"))
    {
        address = stoi(addr, nullptr, 16) - 1;
    }
    cout <<"program counter at memory address: " << address << "will execut what inside!" <<endl;
    registers.display();
    memory.display();
};


// Bitwise operations like OR, AND, XOR between register values
void CU::bitwise_or(const string &instruction)
{
    bitwise_operation(instruction, '|');
    registers.display();
    memory.display();
}

void CU::bitwise_and(const string &instruction)
{
    bitwise_operation(instruction, '&');
    registers.display();
    memory.display();
}

void CU::bitwise_Xor(const string &instruction)
{
    bitwise_operation(instruction, '^');
    registers.display();
    memory.display();
}

void CU::bitwise_operation(const string &instruction, char op)
{
    string dest = instruction.substr(1, 1);
    string reg1 = instruction.substr(2, 1);
    string reg2 = instruction.substr(3, 1);

    if (registers.is_valid_register(reg1[0]) && registers.is_valid_register(reg2[0]) && registers.is_valid_register(dest[0]))
    {
        unsigned int value1 = stoi(registers.get(reg1), nullptr, 16);
        unsigned int value2 = stoi(registers.get(reg2), nullptr, 16);

        unsigned int result;
        switch (op)
        {
        case '|':
            result = value1 | value2;
            break;
        case '&':
            result = value1 & value2;
            break;
        case '^':
            result = value1 ^ value2;
            break;
        }

        stringstream result_stream;
        result_stream << uppercase << hex << result;
        registers.set(dest, result_stream.str());

        cout << "Applied bitwise " << (op == '|' ? "OR" : (op == '&' ? "AND" : "XOR"))
             << " on R" << reg1 << " and R" << reg2 << ", stored result in R" << dest << "\n";
    }
    else
    {
        cout << "Invalid register!\n";
    }
}


// Rotates the value in a register by a specified number of steps
void CU::rotatefunction(const string &instruction)
{
    string reg = instruction.substr(1, 1);
    int steps = stoi(instruction.substr(2, 3)); // 50
    string value = rotateHexValue(reg, steps);
    cout << "In Register R" << reg << "make Rotate by" << steps << "steps" << endl;
    registers.set(reg, value);
    registers.display();
    memory.display();
}

string CU::rotateHexValue(string reg, int steps)
{
    auto hexToBinary = [](const string &hexStr)
    {
        unsigned int num = stoi(hexStr, nullptr, 16);
        string bin = bitset<32>(num).to_string();
        // Remove leading zeros
        bin.erase(0, bin.find_first_not_of('0'));
        return bin;
    }; // error is here
    auto binaryToHex = [](const string &bin)
    {
        int hexValue = bitset<8>(bin).to_ulong();
        stringstream ss;
        ss << uppercase << hex << setw(2) << setfill('0') << hexValue;
        return ss.str();
    };
    string binaryValue = hexToBinary(registers.get(reg));
    int binaryLength = binaryValue.length();
    steps %= binaryLength;
    string rotatedPart = binaryValue.substr(binaryLength - steps);
    reverse(rotatedPart.begin(), rotatedPart.end());
    string rotatedBinaryValue = rotatedPart + binaryValue.substr(0, binaryLength - steps);
    return binaryToHex(rotatedBinaryValue);
}
// Halts the execution of the Vole Machine
void CU::halt() const
{
    cout << "Execution halted.\n";
    registers.display();
    memory.display();
    exit(1);
}

// ============================== VOLEMACHINE Class ==============================
// This class is the main interface for loading and running programs on the Vole Machine.
VOLEMACHINE::VOLEMACHINE() : control_unit(registers, memory) {}
// Loads instructions from a file into memory
void VOLEMACHINE::load_file(const string &filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Invalid file name! Returning to menu...\n";
        return; // Simply return to allow the user to choose another option
    }

    string start_address;
    cout << "Enter the starting memory address (default is 10): ";
    cin >> start_address;
    if (start_address.empty())
        start_address = "10";

    if (!memory.is_valid_memory(start_address))
    {
        cerr << "Invalid memory address!\n";
        return;
    }

    program_counter = start_address;
    unsigned int address = stoi(start_address, nullptr, 16);

    string line;
    while (getline(infile, line))
    {
        string instruction;
        for (char ch : line)
        {
            if (isalpha(ch) || isdigit(ch))
                instruction += ch;
        }

        if (instruction.size() == 4)
        {
            string first_part = instruction.substr(0, 2);
            string second_part = instruction.substr(2, 2);

            string address_hex = (stringstream() << hex << uppercase << setw(2) << setfill('0') << address).str();
            memory.set(address_hex, first_part);

            address_hex = (stringstream() << hex << uppercase << setw(2) << setfill('0') << ++address).str();
            memory.set(address_hex, second_part);

            // Track the last address written
            last_instruction_address = address;

            address++;
        }
    }

    cout << "Instructions loaded into memory starting from address " << start_address << ".\n";
}
// Runs the loaded instructions, interpreting each in sequence
void VOLEMACHINE::run()
{
    unsigned int address = stoi(program_counter, nullptr, 16);

    while (true)
    {
        // Ensure the address is within a valid memory range
        if (address > 255)
        {
            cout << "Reached the end of memory.\n";
            registers.display();
            memory.display();
            break;
        }
        // Fetch and combine instruction parts
        string addr_hex = (stringstream() << hex << uppercase << setw(2) << setfill('0') << address).str();
        string instruction_part1 = memory.get(addr_hex);
        string instruction_part2 = memory.get(
            (stringstream() << hex << uppercase << setw(2) << setfill('0') << ++address).str());
        string instruction = instruction_part1 + instruction_part2;

        // Execute the instruction
        cout << "======================================================================================================\n";
        control_unit.execute_instruction(instruction, address);

        // Check if the current address is the last one
        if (address == last_instruction_address)
        {
            cout << "Reached the last instruction in the memory.\n";
            registers.display();
            memory.display();
            break;
        }
        ++address;
    }
}
// Displays the current state of registers and memory
void VOLEMACHINE::display() const
{
    registers.display();
    memory.display();
}
