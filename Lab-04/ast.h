#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp, int& temp_count, int& label_count) const = 0;
};

// Expression node types

class ExprNode : public ASTNode {
protected:
    string node_type; // Type information (int, float, void, etc.)
public:
    ExprNode(string type) : node_type(type) {}
    virtual string get_type() const { return node_type; }
};

// Variable node (for ID references)

class VarNode : public ExprNode {
private:
    string name;
    ExprNode* index; // For array access, nullptr for simple variables

public:
    VarNode(string name, string type, ExprNode* idx = nullptr)
        : ExprNode(type), name(name), index(idx) {}
    
    ~VarNode() { if(index) delete index; }
    
    bool has_index() const { return index != nullptr; }
    
    string generate_index_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                              int& temp_count, int& label_count) const {
        if (!index) return "";
        return index->generate_code(outcode, symbol_to_temp, temp_count, label_count);
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        if (!has_index()) {
            if(symbol_to_temp.count(name)){
                return symbol_to_temp[name];
            } else {
                return name;
            }
        } else {
            string index_temp = generate_index_code(outcode, symbol_to_temp, temp_count, label_count);
            string result_temp = "t" + to_string(temp_count++);
            outcode << result_temp << " = " << name << "[" << index_temp << "]" << "\n";
            return result_temp;
        }
    }
    
    string get_name() const { return name; }
};

// Constant node

class ConstNode : public ExprNode {
private:
    string value;

public:
    ConstNode(string val, string type) : ExprNode(type), value(val) {}
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        string result_temp = "t" + to_string(temp_count++);
        outcode << result_temp << " = " << value << "\n";
        return result_temp;
    }
};

// Binary operation node

class BinaryOpNode : public ExprNode {
private:
    string op;
    ExprNode* left;
    ExprNode* right;

public:
    BinaryOpNode(string op, ExprNode* left, ExprNode* right, string result_type)
        : ExprNode(result_type), op(op), left(left), right(right) {}
    
    ~BinaryOpNode() {
        delete left;
        delete right;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // Generate code for the operands
        string left_temp = left->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        string right_temp = right->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        
        // Generate the operation with t prefixed temp variables
        string result_temp = "t" + to_string(temp_count++);
        outcode << result_temp << " = " << left_temp << " " << op << " " << right_temp << "\n";
        
        return result_temp;
    }
};

// Unary operation node

class UnaryOpNode : public ExprNode {
private:
    string op;
    ExprNode* expr;

public:
    UnaryOpNode(string op, ExprNode* expr, string result_type)
        : ExprNode(result_type), op(op), expr(expr) {}
    
    ~UnaryOpNode() { delete expr; }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        string expr_temp = expr->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        string result_temp = "t" + to_string(temp_count++);
        outcode << result_temp << " = " << op << expr_temp << "\n";

        return result_temp;
    }
};

// Assignment node

class AssignNode : public ExprNode {
private:
    VarNode* lhs;
    ExprNode* rhs;

public:
    AssignNode(VarNode* lhs, ExprNode* rhs, string result_type)
        : ExprNode(result_type), lhs(lhs), rhs(rhs) {}
    
    ~AssignNode() {
        delete lhs;
        delete rhs;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // Generate code for the right hand side
        string rhs_temp = rhs->generate_code(outcode, symbol_to_temp, temp_count, label_count);

        if(lhs->has_index()) {
            // Handle array assignments
            string index_temp = lhs->generate_index_code(outcode, symbol_to_temp, temp_count, label_count);
            outcode << lhs->get_name() << "[" << index_temp << "] = " << rhs_temp << "\n";
            return lhs->get_name() + "[" + index_temp + "]";
        } else {
            // Handle simple variable assignments matching the expected output format
            outcode << lhs->get_name() << " = " << rhs_temp << "\n";
            symbol_to_temp[lhs->get_name()] = rhs_temp;
            return lhs->get_name();
        }
    }
};

// Statement node types

class StmtNode : public ASTNode {
public:
    virtual string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                                int& temp_count, int& label_count) const = 0;
};

// Expression statement node

class ExprStmtNode : public StmtNode {
private:
    ExprNode* expr;

public:
    ExprStmtNode(ExprNode* e) : expr(e) {}
    ~ExprStmtNode() { if(expr) delete expr; }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // TODO: Implement this method
        // Should generate code for expression statements
        string expr_temp = expr->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        if (!expr_temp.empty()) {
            outcode << expr_temp << ";\n";
            return expr_temp;
        }
        return "";
    }
};

// Block (compound statement) node

class BlockNode : public StmtNode {
private:
    vector<StmtNode*> statements;

public:
    ~BlockNode() {
        for (auto stmt : statements) {
            delete stmt;
        }
    }
    
    void add_statement(StmtNode* stmt) {
        if (stmt) statements.push_back(stmt);
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // TODO: Implement this method
        // Should generate code for all statements in the block
        for (auto stmt : statements) {
            string stmt_code = stmt->generate_code(outcode, symbol_to_temp, temp_count, label_count);
            if (!stmt_code.empty()) {
                outcode << stmt_code << "\n";
            } // 
        }
        return "";
    }
};

// If statement node

class IfNode : public StmtNode {
private:
    ExprNode* condition;
    StmtNode* then_block;
    StmtNode* else_block; // nullptr if no else part

public:
    IfNode(ExprNode* cond, StmtNode* then_stmt, StmtNode* else_stmt = nullptr)
        : condition(cond), then_block(then_stmt), else_block(else_stmt) {}
    
    ~IfNode() {
        delete condition;
        delete then_block;
        if (else_block) delete else_block;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // Generate code for if-else statements according to code3.txt format
        string label_then = "L" + to_string(label_count++);
        string label_else = "L" + to_string(label_count++);
        string label_end = "L" + to_string(label_count++);

        // Generate code for the condition
        string cond_temp = condition->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        
        // Format matches code3.txt exactly - separate lines for if and goto
        outcode << "if " << cond_temp << " goto " << label_then << "\n";
        outcode << "goto " << label_else << "\n";
                            
        // Generate code for the then block
        outcode << label_then << ":\n";
        if (then_block) {
            then_block->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }

        // Add explicit goto to skip else block
        outcode << "goto " << label_end << "\n";

        // Generate code for the else block
        outcode << label_else << ":\n";
        if (else_block) {
            else_block->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }

        // End label
        outcode << label_end << ":\n";

        return "";
    }
};

// While statement node

class WhileNode : public StmtNode {
private:
    ExprNode* condition;
    StmtNode* body;

public:
    WhileNode(ExprNode* cond, StmtNode* body_stmt)
        : condition(cond), body(body_stmt) {}
    
    ~WhileNode() {
        delete condition;
        delete body;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        string label_start = "L" + to_string(label_count++);
        string label_body = "L" + to_string(label_count++);
        string label_end = "L" + to_string(label_count++);

        // Start label
        outcode << label_start << ":\n";

        // Generate code for the condition with format matching code3.txt
        string cond_temp = condition->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        outcode << "if " << cond_temp << " goto " << label_body << "\n";
        outcode << "goto " << label_end << "\n";

        // Generate code for the loop body
        outcode << label_body << ":\n";
        if (body) {
            body->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }
        
        // Jump back to the condition
        outcode << "goto " << label_start << "\n";

        // End label
        outcode << label_end << ":\n";

        return "";
    }
};

// For statement node

class ForNode : public StmtNode {
private:
    ExprNode* init;
    ExprNode* condition;
    ExprNode* update;
    StmtNode* body;

public:
    ForNode(ExprNode* init_expr, ExprNode* cond_expr, ExprNode* update_expr, StmtNode* body_stmt)
        : init(init_expr), condition(cond_expr), update(update_expr), body(body_stmt) {}
    
    ~ForNode() {
        if (init) delete init;
        if (condition) delete condition;
        if (update) delete update;
        delete body;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        string label_start = "L" + to_string(label_count++);
        string label_body = "L" + to_string(label_count++);
        string label_end = "L" + to_string(label_count++);

        // Generate code for the initialization
        if (init) {
            string init_code = init->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }

        // Condition label
        outcode << label_start << ":\n";
        if (condition) {
            string cond_temp = condition->generate_code(outcode, symbol_to_temp, temp_count, label_count);
            outcode << "if " << cond_temp << " goto " << label_body << "\n";
            outcode << "goto " << label_end << "\n";
        }

        // Loop body label
        outcode << label_body << ":\n";
        if (body) {
            body->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }
        
        // Update expression
        if (update) {
            update->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }

        // Jump back to the condition check
        outcode << "goto " << label_start << "\n";

        // End label
        outcode << label_end << ":\n";

        return "";
    }
};

// Return statement node

class ReturnNode : public StmtNode {
private:
    ExprNode* expr;

public:
    ReturnNode(ExprNode* e) : expr(e) {}
    ~ReturnNode() { if (expr) delete expr; }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // Generate code for the expression
        string expr_temp = expr ? expr->generate_code(outcode, symbol_to_temp, temp_count, label_count) : "";
        
        // Generate the return statement with the expression result
        outcode << "return " << expr_temp << "\n";
        return "";
    }
};

// Declaration node

class DeclNode : public StmtNode {
private:
    string type;
    vector<pair<string, int>> vars; // Variable name and array size (0 for regular vars)

public:
    DeclNode(string t) : type(t) {}
    
    void add_var(string name, int array_size = 0) {
        vars.push_back(make_pair(name, array_size));
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        for (const auto& var : vars) {
            if (var.second == 0) {
                // Regular variable declaration - format matches code3.txt
                outcode << "// Declaration: " << type << " " << var.first << "\n";
            } else {
                // Array declaration - format matches code3.txt
                outcode << "// Declaration: " << type << " " << var.first << "[" << var.second << "]\n";
            }
        }
        return "";
    }
    
    string get_type() const { return type; }
    const vector<pair<string, int>>& get_vars() const { return vars; }
};

// Function declaration node

class FuncDeclNode : public ASTNode {
private:
    string return_type;
    string name;
    vector<pair<string, string>> params; // Parameter type and name
    BlockNode* body;

public:
    FuncDeclNode(string ret_type, string n) : return_type(ret_type), name(n), body(nullptr) {}
    ~FuncDeclNode() { if (body) delete body; }
    
    void add_param(string type, string name) {
        params.push_back(make_pair(type, name));
    }
    
    void set_body(BlockNode* b) {
        body = b;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // Format exactly like code3.txt
        outcode << "// Function: " << return_type << " " << name << "(";
        for (size_t i = 0; i < params.size(); ++i) {
            outcode << params[i].first << " " << params[i].second;
            if (i < params.size() - 1) {
                outcode << ", ";
            }
        }
        outcode << ")\n";

        if (body) {
            body->generate_code(outcode, symbol_to_temp, temp_count, label_count);
        }

        return "";
    }
};

// Helper class for function arguments

class ArgumentsNode : public ASTNode {
private:
    vector<ExprNode*> args;

public:
    ~ArgumentsNode() {
        // Don't delete args here - they'll be transferred to FuncCallNode
    }
    
    void add_argument(ExprNode* arg) {
        if (arg) args.push_back(arg);
    }
    
    ExprNode* get_argument(int index) const {
        if (index >= 0 && index < args.size()) {
            return args[index];
        }
        return nullptr;
    }
    
    size_t size() const {
        return args.size();
    }
    
    const vector<ExprNode*>& get_arguments() const {
        return args;
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // This node doesn't generate code directly
        return "";
    }
};

// Function call node

class FuncCallNode : public ExprNode {
private:
    string func_name;
    vector<ExprNode*> arguments;

public:
    FuncCallNode(string name, string result_type)
        : ExprNode(result_type), func_name(name) {}
    
    ~FuncCallNode() {
        for (auto arg : arguments) {
            delete arg;
        }
    }
    
    void add_argument(ExprNode* arg) {
        if (arg) arguments.push_back(arg);
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        vector<string> arg_temps;
        
        // Generate code for each argument
        for (auto arg : arguments) {
            string arg_temp = arg->generate_code(outcode, symbol_to_temp, temp_count, label_count);
            arg_temps.push_back(arg_temp);
        }

        // Emit parameter passing code according to code3.txt format
        for (size_t i = 0; i < arg_temps.size(); i++) {
            outcode << "param " << arg_temps[i] << "\n";
        }

        // Generate the function call code according to code3.txt format
        string result_temp = "t" + to_string(temp_count++);
        outcode << result_temp << " = call " << func_name << ", " << arg_temps.size() << "\n";

        return result_temp;
    }
};

// Program node (root of AST)

class ProgramNode : public ASTNode {
private:
    vector<ASTNode*> units;

public:
    ~ProgramNode() {
        for (auto unit : units) {
            delete unit;
        }
    }
    
    void add_unit(ASTNode* unit) {
        if (unit) units.push_back(unit);
    }
    
    string generate_code(ofstream& outcode, map<string, string>& symbol_to_temp,
                        int& temp_count, int& label_count) const override {
        // Generate code for the entire program
        for (auto unit : units) {
            unit->generate_code(outcode, symbol_to_temp, temp_count, label_count);
            outcode << "\n";
        }
        return "";
    }
};

#endif // AST_H