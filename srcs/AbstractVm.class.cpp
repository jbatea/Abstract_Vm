#include "../includes/AbstractVm.class.hpp"

// Default constructor
AbstractVm::AbstractVm( void ) {
    return;
}

 // Copy constructor
 AbstractVm::AbstractVm(AbstractVm const & src) {
     *this = src;
     return;
 }

 // Destructor
AbstractVm::~AbstractVm( void ) {
    return;
}

// Assignement
AbstractVm & AbstractVm::operator=( AbstractVm const & rhs) {

    if (this != &rhs)
        *this = rhs;
    return *this;
}

void AbstractVm::checkArg( int ac, char **av) {

    if (ac == 2)
        this->isFiles(av[1]);
    else if (ac == 1)
        this->isLines();
    else
        std::cout << "Too much arguments, waiting for one or zero" << std::endl;
    return;
}

void AbstractVm::isFiles(char *av) {

    (void)av;
    return;
}

void AbstractVm::isLines() {
        return;
}
