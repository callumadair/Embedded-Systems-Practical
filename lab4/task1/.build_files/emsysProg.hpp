// A header file to parse the program file for the simple ALU in lab 4
//
// author: stf

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

typedef struct {
        uint8_t opcode;
        uint8_t a;
        uint8_t b;
} op_t;

class emsysProg {
        public:
                emsysProg(std::string progfilename) {
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
                                op_t o;
                                if(opcheck(tok[0])){ 
                                        o.opcode = _opcodes[tok[0]];
                                        o.a = atoi(tok[1].c_str());
                                        if(tok.size() > 2)
                                                o.b = atoi(tok[2].c_str());
                                        else
                                                o.b = 0;
                                        fprintf(stdout, "\t PARSED: op[%d] %d %d\n", o.opcode, o.a, o.b);
                                        _instr.push(o);
                                } else {
                                        fprintf(stderr, "ERROR on line %d: Unknown opcode %s\n\n\n",lineno, tok[0].c_str());
                                        exit(1);
                                }

                                lineno++;
                        }
                }

                // Get the number of instructions loaded
                unsigned size() { return _instr.size(); }

                // Pop the next instruction
                op_t pop() {
                        op_t t;
                        if(size() > 0) {
                              t = _instr.front();
                              _instr.pop();
                        } else {
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
                std::queue<op_t> _instr;
};
