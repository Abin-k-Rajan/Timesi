#ifndef TIME_TABLE_H
#define TIME_TABLE_H


#include <iostream>
#include <cstring>
#include <vector>


#ifdef __cplusplus
    extern "C" {
#endif



#ifdef BUILD_CUSTOM_DLL
    #define SHARED_LIB __declspec(dllexport)
#else
    #define SHARED_LIB __declspec(dllimport)
#endif


class table_class;


class SHARED_LIB table_class
{
    private:
        int _class;
        std::string subject;
        std::string day;
        int time;
    public:
        table_class()
        {

        }
        table_class(int _class, std::string subject, std::string day, int time);
        int update_table_class_values(int _class = 0,
                                      std::string subject = "",
                                      std::string day = "",
                                      int time = -1);
        int get_table_class_value_class();
        std::string get_table_class_value_subject();
        std::string get_table_class_value_day();
        int get_table_class_value_time();
};



class SHARED_LIB time_table
{
    private:
        std::vector<table_class*> chromosome;
        int fitness;
    public:
        time_table(std::vector<table_class*> chromosome);
        int calc_fitness_score();
        std::vector<table_class*> mate(std::vector<table_class*> chromosome2, std::vector<table_class*> list_of_table);

        //  GETTER METHODS FOR PRIVATE MEMBERS
        int get_fitness_value();
        std::vector<table_class*> get_chromosome_value();
};


table_class* SHARED_LIB mutate_gene(std::vector<table_class*> list_of_table);

int SHARED_LIB random_integer(int start, int end);

std::vector<table_class*> SHARED_LIB create_genome(std::vector<table_class*> list_of_table);

//  UTILITY FUNCTIONS

bool SHARED_LIB sort_by_time(table_class* t1, table_class* t2);

bool SHARED_LIB sort_by_fitness(time_table* t1, time_table* t2);

bool SHARED_LIB sort_by_class(table_class* t1, table_class* t2);

std::vector<table_class*> SHARED_LIB all_possible_time_table();

#ifdef __cplusplus
    }
#endif


#endif