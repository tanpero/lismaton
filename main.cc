#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <sstream>

class LispObject {
public:
    virtual ~LispObject() {}
};

class LispInt : public LispObject {
public:
    int value;
    LispInt(int value) : value(value) {}
};

class LispFunction : public LispObject {
public:
    std::function<LispObject*(const std::vector<LispObject*>&)> func;
    LispFunction(std::function<LispObject*(const std::vector<LispObject*>&)> func) : func(func) {}
};

class Environment {
    std::map<std::string, LispObject*> env;
public:
    void define(std::string var, LispObject* value) {
        env[var] = value;
    }

    LispObject* lookup(std::string var) {
        if (env.find(var) != env.end())
            return env[var];
        throw std::runtime_error("Undefined variable");
    }
};

LispObject* eval(LispObject* ast, Environment& env);

LispObject* parse(std::string input) {
    std::istringstream iss(input);
    std::string token;
    iss >> token;
    if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
        return new LispInt(std::stoi(token));
    }
    return nullptr;
}

LispObject* eval(LispObject* ast, Environment& env) {
    if (dynamic_cast<LispInt*>(ast)) {
        return ast;
    }
    return nullptr;
}

int main() {
    Environment env;
    std::string input = "42";
    LispObject* ast = parse(input);
    LispObject* result = eval(ast, env);
    if (LispInt* intResult = dynamic_cast<LispInt*>(result)) {
        std::cout << "Result: " << intResult->value << std::endl;
    }
    delete ast;
    return 0;
}

