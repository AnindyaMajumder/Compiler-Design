#include "symbol_info.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        int hash = 0;
        for (char ch : name)
        {
            hash += static_cast<int>(ch); 
        }
        return hash % bucket_count; 
    }

public:
    scope_table();
    scope_table(scope_table *parent_scope, int bucket_count, int unique_id);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol);
    bool insert_in_scope(symbol_info* symbol);
    bool delete_from_scope(symbol_info* symbol);
    void print_scope_table(ofstream& outlog);
    ~scope_table();

    // Renamed delete to delete_symbol to avoid keyword conflict
    symbol_info *lookup(string name);
    bool delete_symbol(string name);
    int get_bucket_count();
};

// complete the methods of scope_table class

scope_table::scope_table()
{
    this->bucket_count = 107;
    this->unique_id = 0;
    this->parent_scope = NULL;
    table.resize(107);
}

scope_table::scope_table(scope_table *parent_scope, int bucket_count, int unique_id)
{
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->parent_scope = parent_scope;
    table.resize(bucket_count);
}

scope_table::~scope_table()
{
    for (int i = 0; i < bucket_count; i++)
    {
        for (auto it = table[i].begin(); it != table[i].end(); ++it)
        {
            delete *it;
            *it = NULL;
        }
    }
}

scope_table *scope_table::get_parent_scope()
{
    return parent_scope;
}

int scope_table::get_unique_id()
{
    return unique_id;
}

int scope_table::get_bucket_count()
{
    return bucket_count;
}

symbol_info *scope_table::lookup_in_scope(symbol_info* symbol)
{
    if (symbol == NULL)
    {
        return NULL;
    }
    return lookup(symbol->get_name());
}

symbol_info *scope_table::lookup(string name)
{
    int index = hash_function(name);
    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if ((*it)->get_name() == name)
        {
            return *it;
        }
    }
    return NULL;
}

bool scope_table::insert_in_scope(symbol_info* symbol)
{
    if (symbol == NULL)
    {
        return false;
    }
    
    symbol_info* found = lookup_in_scope(symbol);
    
    if (found == NULL)
    {
        int index = hash_function(symbol->get_name());
        table[index].push_back(symbol);
        return true;
    }
    return false;
}

bool scope_table::delete_from_scope(symbol_info* symbol)
{
    if (symbol == NULL)
    {
        return false;
    }
    return delete_symbol(symbol->get_name());
}

bool scope_table::delete_symbol(string name)
{
    int index = hash_function(name);
    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if ((*it)->get_name() == name)
        {
            delete *it; // Free the memory of the symbol
            table[index].erase(it); // Remove from the list
            return true; // Symbol deleted successfully
        }
    }
    return false; // Symbol not found
}

void scope_table::print_scope_table(ofstream& outlog)
{
    outlog << "ScopeTable # " << unique_id << endl;
    for (int i = 0; i < bucket_count; i++)
    {
        if (!table[i].empty())
        {
            outlog << i << "--> " << endl;
            for (auto it = table[i].begin(); it != table[i].end(); ++it)
            {
                outlog << "< " << (*it)->get_name() << " : " << (*it)->get_type() << " > " << endl;
                outlog << (*it)->get_symbol_type() << endl;
                
                if ((*it)->get_symbol_type() == "Function Definition")
                {
                    outlog << "Return Type : " << (*it)->get_data_type() << endl;
                    
                    auto types = (*it)->get_param_types();
                    auto names = (*it)->get_param_names();
                    
                    outlog << "Number of Parameters: " << types.size() << endl;
                    
                    outlog << "Parameter Details: ";
                    for (size_t j = 0; j < types.size(); j++)
                    {
                        outlog << types[j] << " " << names[j];
                        if (j != types.size() - 1)
                        {
                            outlog << ", ";
                        }
                    }
                    outlog << endl;
                }
                else
                {
                    int array_size = (*it)->get_array_size();
                    if (array_size != 0)
                    {
                        outlog << "Type : " << (*it)->get_data_type() << endl;
                        outlog << "Size : " << array_size << endl;
                    }
                    else
                    {
                        outlog << "Type : " << (*it)->get_data_type() << endl;
                    }
                }
                outlog << endl;
            }
        }
    }
}