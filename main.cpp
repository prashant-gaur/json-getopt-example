#include "json.hpp"
#include <exception>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>

#define PROGRAM_NAME "json-example"
// This will updated via tag version of git repo
//#define APP_VERSION "1.0.0"

using json = nlohmann::json;

static const char* filepath;

static const char app_info[] = PROGRAM_NAME " version " APP_VERSION
                                            " - example application to demo json parsing\n";

static const char usage[] = "usage: " PROGRAM_NAME
                            " [-f <path to json config file>]\n";

static const char optionsstr[] = "\t-f PATH --filelocation=PATH path to json config file\n"
                                 "\t-h --help print application usage\n"
                                 "\t-v --version print application version info\n";

/*
# define no_argument        0
# define required_argument  1
# define optional_argument  2
*/
#ifdef __cplusplus
extern "C" {
#endif

static const struct option long_options[] = {
    { "filelocation", required_argument, NULL, 'f' },
    { "help", no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'v' },
    { NULL, 0, NULL, 0 },
};

#ifdef __cplusplus
} // extern "C"
#endif

static const char* optstring = "f:hv";

static int parse_app_cmdline_config(int argc, char* argv[])
{
    int key = 0;
    if (argc == 1) {
        printf("%s", usage);
        printf("%s", optionsstr);
        exit(EXIT_FAILURE);
    }

    while ((key = getopt_long(argc, argv, optstring, long_options, NULL)) != -1) {
        switch (key) {
        case 'f':
            filepath = optarg;
            break;
        case 'h':
            printf("%s", usage);
            printf("%s", optionsstr);
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            printf("%s", app_info);
            exit(EXIT_SUCCESS);
            break;
        case ':':
            printf("Parameter is missing");
            exit(EXIT_FAILURE);
            break;
        default:
            printf("%s", usage);
            return -1;
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{

    int err = parse_app_cmdline_config(argc, argv);
    if (err)
        exit(EXIT_FAILURE);

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
    std::ifstream inputfile(filepath);
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
