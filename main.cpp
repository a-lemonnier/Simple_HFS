#include "include/basic_fracs.hpp"
#include "include/io.hpp"
#include "include/cgwr.hpp"


int main(int argc, char** argv) {

    _io io(argc, argv);

    if (io.compute()) {
        io.print();
        io.write();
    }    

    return EXIT_SUCCESS;
}
