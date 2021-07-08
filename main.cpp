#include "json.hpp"
#include <exception>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main(int argc, char* argv[])
{

#if false
    // create json object in memory
    json j_obj_string = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    std::cout << j_obj_string.dump(4) << std::endl;
    // using raw literal
    json j_obj_rawstring = R"(
        {
            "happy": true,
            "pi": 3.141
        }
    )"_json;
    std::cout << j_obj_rawstring.dump(4) << std::endl;
#endif

    // read json file into string
    std::ifstream inputfile("/home/gpr3hi/Desktop/C++/JSON/sample_extn.json");
    if (!inputfile.is_open()) {
        std::cout << "could not open file ..." << std::endl;
        return -1;
    }

    std::stringstream content;
    // here copy the contents of file into std::string
    content << inputfile.rdbuf();
    std::cout << content.str() << std::endl;

    // parse json data stored in file
    json root;
    try {
        //parse json contents from std::string object
        root = json::parse(content.str());
    } catch (json::parse_error err) {
        std::cout << "Failed to parse, invalid JSON format" << std::endl;
        return -1;
    }

    // validate if we have valid entry in json file
    // capture it by reference in order to make changes and save it
    json& data_School1 = root["School1"];
    if (data_School1.find("Department") == data_School1.end() || !data_School1["Department"].is_string()) {
        std::cout << "Failed to find the \"Department\" in sample_extn.json" << std::endl;
        return -1;
    } else {
        std::cout << "Found \"Department\" in sample.json" << std::endl;
    }

    // read specific entry
    std::string department = data_School1["Department"];
    std::cout << "Department: " << data_School1["Department"] << std::endl;

    // update specific entry to json file
    data_School1["Department"] = "Mechanical";
    std::cout << "Department: " << data_School1["Department"] << std::endl;

    // delete specific entry (reference: key)
    data_School1.erase("Department");
    std::cout << root.dump(4) << std::endl;

    // create new entry
    data_School1.emplace("Department", "Economics");

    // dump all the contents
    // to std::cout with different indentation
    std::cout << root.dump(4) << std::endl;
#if false
    std::cout << root.dump(-1) << std::endl;
    std::cout << root.dump(0) << std::endl;
    std::cout << root.dump(4) << std::endl;
#endif
    // to file
    std::ofstream outfile("sample_extn.json");
    outfile << root.dump(4);

    return 0;
}
