 #include "cat.h"

Cat::Cat(std::string name) : name(name) {
    std::cout << "Constructor of Cat : " << name << std::endl;
}

Cat::~Cat()
{
    std::cout << "Deconstructor of Cat " << name << std::endl;
}

void Cat::set_cat_name2(const std::string &name) {
    this->name = name;
};