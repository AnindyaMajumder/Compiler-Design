#include "scope_table.h"
#include <iostream>
#include <fstream>

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;
    int new_scope_id; // Added new_scope_id

public:
    symbol_table(int bucket_count);
    ~symbol_table();
    void enter_scope();
    void exit_scope();
    bool insert(symbol_info* symbol);
    symbol_info* lookup(symbol_info* symbol);
    void print_current_scope(ofstream& outlog); // Updated parameter
    void print_all_scopes(ofstream& outlog);
    int getCurrentScopeID() const; // Added new method

    // you can add more methods if you need 
    symbol_info* lookup(string name);
    bool remove(symbol_info* symbol); // Renamed from delete_symbol
    bool remove(string name); // Renamed from delete_symbol
};

// complete the methods of symbol_table class

symbol_table::symbol_table(int bucket_count) : bucket_count(bucket_count), current_scope_id(1), new_scope_id(2)
{
    current_scope = new scope_table(NULL, bucket_count, current_scope_id);
    // No need to call enter_scope() here
}

symbol_table::~symbol_table()
{
    while (current_scope != NULL)
    {
        exit_scope();
    }
}

void symbol_table::enter_scope()
{
    scope_table* new_scope = new scope_table(current_scope, bucket_count, new_scope_id);
    current_scope_id = new_scope_id;
    new_scope_id++;
    current_scope = new_scope;
}

int symbol_table::getCurrentScopeID() const
{
    return current_scope_id;
}

void symbol_table::exit_scope()
{
    if (current_scope != NULL)
    {
        scope_table *temp = current_scope;
        current_scope = current_scope->get_parent_scope();
        delete temp;
        temp = NULL;
        if (current_scope != NULL) {
            current_scope_id = current_scope->get_unique_id();
        }
    }
}

bool symbol_table::insert(symbol_info* symbol)
{
    if (current_scope != NULL)
    {
        return current_scope->insert_in_scope(symbol);
    }
    return false;
}

symbol_info* symbol_table::lookup(symbol_info* symbol)
{
    if(symbol == NULL)
    {
        return NULL;
    }
    return lookup(symbol->get_name());
}

symbol_info* symbol_table::lookup(string name)
{
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        symbol_info *found = temp->lookup(name);
        if (found != NULL)
        {
            return found;
        }
        temp = temp->get_parent_scope();
    }
    return NULL;
}

bool symbol_table::remove(symbol_info* symbol)
{
    if (current_scope != NULL && symbol != NULL)
    {
        return current_scope->delete_from_scope(symbol);
    }
    return false;
}

bool symbol_table::remove(string name)
{
    if (current_scope != NULL)
    {
        return current_scope->delete_symbol(name);
    }
    return false;
}

void symbol_table::print_current_scope(ofstream& outlog)
{
    if (current_scope != NULL)
    {
        current_scope->print_scope_table(outlog);
    }
    else
    {
        outlog << "No current scope." << endl;
    }
}

void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog<<"################################"<<endl<<endl;
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        temp->print_scope_table(outlog);
        outlog << endl<<endl;
        temp = temp->get_parent_scope();
    }
    outlog<<"################################"<<endl<<endl;
}