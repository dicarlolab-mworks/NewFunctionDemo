//
//  NewFunctionDemoPlugin.cpp
//  NewFunctionDemo
//
//  Created by Christopher Stawarz on 6/28/13.
//  Copyright (c) 2013 The MWorks Project. All rights reserved.
//


using namespace mw;


static Datum get_num_trials(const stx::SymbolTable::paramlist_type& paramlist) {
    if (!(paramlist[0].isString())) {
        throw stx::BadFunctionCallException("First parameter to function get_num_trials() must be a string");
    }
    
    if (!(paramlist[1].isInteger()) || (paramlist[1].getInteger() < 1)) {
        throw stx::BadFunctionCallException("Second parameter to function get_num_trials() must be a positive integer");
    }
    
    std::string filename = paramlist[0].getString();
    int lineNumber = paramlist[1].getInteger();
    
    mprintf("Reading number of trials from line %d of file \"%s\"", lineNumber, filename.c_str());
    
    // TODO: Replace random number generation with real line-reading code
    static boost::random::mt19937 gen;
    int result = boost::random::uniform_int_distribution<>(1, lineNumber)(gen);
    
    return Datum(result);
}


class NewFunctionDemoPlugin : public Plugin {
    
    void registerComponents(boost::shared_ptr<ComponentRegistry> registry) MW_OVERRIDE {
        // Register function 'get_num_trials' taking 2 parameters
        global_variable_registry->setFunction("get_num_trials", 2, get_num_trials);
    }
    
};


MW_SYMBOL_PUBLIC
extern "C" Plugin* getPlugin() {
    return new NewFunctionDemoPlugin();
}
