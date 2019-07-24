#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <stack>
#include <algorithm>

static std::vector<std::string> Keywords {
            std::string("add"),
            std::string("sub"),
            std::string("mul"),
            std::string("concat")
};

class Instruction
{
public:
    virtual std::string name() const = 0;
    virtual std::string operator()(std::stack<std::string>&) = 0;
    virtual ~Instruction();
};

class InstructionAdd : public Instruction
{
public:
    virtual std::string name() const { return _name; }
    virtual std::string operator()(std::stack<std::string> &stack) {
        std::string tmp;
        int add = 0;
        while (stack.size() != 0) {
            tmp  = stack.top();
            tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c){if(c == '"') return true; return false;}), tmp.end());
            add += std::stoi(tmp);
            stack.pop(); 
        }
        return std::to_string(add);
    }
private:
    const std::string _name = "add";
};

class InstructionSub : public Instruction
{
public:
    virtual std::string name() const { return _name; }
    virtual std::string operator()(std::stack<std::string>& stack) {
        std::string tmp = stack.top();
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c){if(c == '"') return true; return false;}), tmp.end());
        int sub = std::stoi(tmp);
        stack.pop();
        while (stack.size() != 0) {
            tmp  = stack.top();
            tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c){if(c == '"') return true; return false;}), tmp.end());
            sub -= std::stoi(tmp);
            stack.pop();
        }
        return std::to_string(sub);
    }
private:
    const std::string _name = "sub";
};

class InstructionMul : public Instruction
{
public:
    virtual std::string name() const { return _name; }
    virtual std::string operator()(std::stack<std::string>& stack) {
        std::string tmp = stack.top();
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c){if(c == '"') return true; return false;}), tmp.end());
        int mul = std::stoi(tmp);
        stack.pop();
        while (stack.size() != 0) {
            tmp = stack.top();
            tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c){if(c == '"') return true; return false;}), tmp.end());
            mul *= std::stoi(tmp);
            stack.pop();
        }
        return std::to_string(mul);
    }

private:
    const std::string _name = "mul";
};

class InstructionConcat : public Instruction
{
public:
    virtual std::string name() const { return _name; }
    virtual std::string operator()(std::stack<std::string>& stack) {
        std::string concat("");
        while (stack.size() != 0) {
            std::string tmp = stack.top();
            tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c){if(c == '"') return true; return false;}), tmp.end());
            concat += tmp;
            stack.pop();
        }
        return concat;
    }
private:
    const std::string _name = "concat";
};


#endif // INSTRUCTION_H
