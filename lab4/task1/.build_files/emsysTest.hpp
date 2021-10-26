// A header file to parse the test program file for the simple ALU in lab 4
//
// author: stf
#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

typedef struct {
        std::string op_str;
        uint8_t expected;
        uint8_t opcode;
        uint8_t a;
        uint8_t b;
} test_op_t;

class emsysTest {
        public:
                emsysTest(std::string progfilename) {
                        _progfilename = progfilename;
                        _progfile = std::ifstream(_progfilename); 
                        parse();
                }

                std::vector<std::string> getTokens(std::string in) {
                        std::vector<std::string> token_list;
                        std::istringstream iss(in);
                        std::string token;
                        while (std::getline(iss, token, ' '))
                        {
                                token_list.push_back(token);
                        }
                        return token_list;
                }

                bool opcheck(std::string in) {
                        if ( _opcodes.find(in) == _opcodes.end() ) {
                                return false;
                        } else {
                                return true;
                        }
                }

                void parse() {
                        std::string istr;
                        unsigned lineno = 0;
                        while(std::getline(_progfile, istr)) {
                                fprintf(stdout, "Parsing line %d: %s\n", lineno, istr.c_str());
                                
                                // Get tokens
                                std::vector<std::string> tok = getTokens(istr);
                                test_op_t o;
                                if(opcheck(tok[1])){ 
                                        o.expected = atoi(tok[0].c_str());
                                        o.opcode = _opcodes[tok[1]];
                                        o.op_str = tok[1];
                                        o.a = atoi(tok[2].c_str());
                                        if(tok.size() > 3)
                                                o.b = atoi(tok[3].c_str());
                                        else
                                                o.b = 0;
                                        fprintf(stdout, "\t PARSED: op[%d] %d %d\n", o.opcode, o.a, o.b);
                                        _instr.push(o);
                                        _expected.push(o);
                                } else {
                                        fprintf(stderr, "ERROR on line %d: Unknown opcode %s\n\n\n",lineno, tok[0].c_str());
                                        exit(1);
                                }

                                lineno++;
                        }
                }

                // Get the number of instructions loaded
                unsigned size() { return _instr.size(); }
                unsigned expected_size() { return _expected.size(); }

                // Pop the next instruction
                test_op_t pop() {
                        test_op_t t;
                        if(size() > 0) {
                              t = _instr.front();
                              _instr.pop();
                        } else {
                                t.expected = 0;
                                t.opcode = 0;
                                t.a = 0;
                                t.b = 0;
                        }
                        return t;
                }

                // Pop the next expected value
                test_op_t pop_expected() {
                        test_op_t t;
                        if(expected_size() > 0) {
                              t = _expected.front();
                              _expected.pop();
                        } else {
                                t.expected = 0;
                                t.opcode = 0;
                                t.a = 0;
                                t.b = 0;
                        }
                        return t;
                }

        private:
                std::string _progfilename;
                std::ifstream _progfile;
                std::map<std::string, uint8_t> _opcodes { {"ADD", 0}, {"SUB", 1}, {"SR1", 2}, {"SL1", 3},{"AND", 4}, {"OR", 5}, };
                std::queue<test_op_t> _instr;
                std::queue<test_op_t> _expected;
};
