#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;     /// Token type or the non_terminal
    
    // Write necessary attributes to store what type of symbol it is (variable/array/function)
    string symbol_type;   // Var or Arr or Func
    // Write necessary attributes to store the type/return type of the symbol (int/float/void/...)
    string data_type;
    // Write necessary attributes to store the parameters of a function
    vector<string> parameter_types; 
    vector<string> parameter_names;
    // Write necessary attributes to store the array size if the symbol is an array
    int array_size;

public:
    symbol_info(string name, string type, string symbol_type = "", vector<string> parameter_types = vector<string>(), vector<string> parameter_names = vector<string>())
    {
        this->name = name;
        this->type = type;
        this->symbol_type = symbol_type;
        this->array_size = 0;
        this->parameter_types = parameter_types;
        this->parameter_names = parameter_names;
    }
    
    // Name getter and setter
    string get_name()
    {
        return name;
    }
    
    void set_name(string name)
    {
        this->name = name;
    }

    // Type getter and setter
    string get_type()
    {
        return type;
    }
    
    void set_type(string type)
    {
        this->type = type;
    }

    // Symbol type getter and setter
    string get_symbol_type()
    {
        return symbol_type;
    }
    
    void set_symbol_type(string symbol_type)
    {
        this->symbol_type = symbol_type;
    }
    
    // Data type getter and setter
    string get_data_type()
    {
        return data_type;
    }
    
    void set_data_type(string data_type)
    {
        this->data_type = data_type;
    }
    
    // Array size getter and setter
    int get_array_size()
    {
        return array_size;
    }
    
    void set_array_size(int size)
    {
        this->array_size = size;
    }
    
    // Parameter types getter and setter
    vector<string> get_param_types()
    {
        return parameter_types;
    }
    
    void set_param_types(const vector<string>& types)
    {
        this->parameter_types = types;
    }
    
    // Parameter names getter and setter
    vector<string> get_param_names()
    {
        return parameter_names;
    }
    
    void set_param_names(const vector<string>& names)
    {
        this->parameter_names = names;
    }
    
    // Add a parameter to the parameter lists
    void add_parameter(string type, string name)
    {
        parameter_types.push_back(type);
        parameter_names.push_back(name);
    }

    ~symbol_info()
    {
        // Write necessary code to deallocate memory, if necessary
    }
};