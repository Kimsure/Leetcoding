# ifndef CAT_H
# define CAT_H
#include <string>
#include <iostream>

class Cat {
    public:
    Cat(std::string name);
    Cat() = default;
    ~Cat();

    void cat_info() const {
        std::cout << "cat info name : " << name << std::endl;
    }
    std::string get_name() const {
        return name;
    }
    void set_cat_name(const std::string &name) {
        this->name = name;
    }    
    void set_cat_name2(const std::string &name);
    private:
    std::string name{"Mimi"};
};

Cat::Cat(std::string name) : name(name) {
    std::cout << "Constructor of Cat : " << name << std::endl;
}

Cat::~Cat()
{
    std::cout << "Deconstructor of Cat " << name << std::endl;
}
#endif
