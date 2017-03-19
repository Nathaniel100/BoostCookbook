//
// Created by 吴凡 on 2017/3/2.
//
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <iostream>

namespace opt = boost::program_options;


int main(int argc, const char *const *argv) {
    opt::positional_options_description p;
    p.add("name", -1);
    opt::options_description desc("All options");
    desc.add_options()
            ("apples,a", opt::value<int>()->default_value(10), "apples that you have")
            ("oranges,o", opt::value<int>(), "oranges that you have")
            ("name", opt::value<std::string>(), "your name")
            ("help", "produce help message");
    opt::variables_map vm;
    opt::store(opt::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    opt::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    if(!vm.count("oranges")) {
        std::cout << "oranges required\n";
        return 1;
    }
    if (vm.count("name")) {
        std::cout << "Hi, " << vm["name"].as<std::string>() << "!\n";
    }
    std::cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;
    return 0;
}