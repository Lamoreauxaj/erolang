#ifndef SCOPE_H
#define SCOPE_H
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include "parser.h"
#include "lib/variable.h"
using namespace std;

const int VAR_SIZE = 16;

enum DataLocation {
    DATA_SEGMENT, // store global and captured variables
    STACK // all other local variables
};

struct Data {
    DataLocation loc;
    int pos;
    string label;
    VarType default_type;
    string default_value;

    Data() {}
    // used for stack variables
    Data(DataLocation loc, int pos) : loc(loc), pos(pos), label(), default_type(UNDEFINED), default_value("0") {}
    // used for data segment variables
    Data(DataLocation loc, string label) : loc(loc), pos(0), label(label), default_type(UNDEFINED), default_value("0") {}
    // used for data segment variables with default value
    Data(DataLocation loc, string label, VarType default_type, string default_value) : loc(loc), pos(0), label(label), default_type(default_type), default_value(default_value) {}
    string tostring() {
        string res = "(Data ";
        if (loc == 0) res += "DATA_SEGMENT";
        else res += "STACK";
        res += " " + to_string(pos) + " " + label + ")";
        return res;
    }
};

extern map<Node*, int> node_scopes;
// store variable locations
extern map<int, map<string, int>> scope_levels;
extern map<int, Data> data_locs;
// additional information
extern map<int, int> parent_scope;
extern map<int, int> root_scope;
// size of stack of root scopes
extern map<int, int> stack_size;

void scope_variables(Stmts *stmts);

#endif