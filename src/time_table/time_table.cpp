#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "time_table.h"



//  UTILITY FUNCTIONS STARTS HERE

bool sort_by_time(table_class* t1, table_class* t2)
{
    if(t1->get_table_class_value_time() == t2->get_table_class_value_time())
    {
        return t1->get_table_class_value_class() < t2->get_table_class_value_class();
    }
    return t1->get_table_class_value_time() < t2->get_table_class_value_time();
}


bool sort_by_fitness(time_table* t1, time_table* t2)
{
    return t1->get_fitness_value() < t2->get_fitness_value();
}


bool sort_by_class(table_class* t1, table_class* t2)
{
    if(t1->get_table_class_value_class() == t2->get_table_class_value_class())
    {
        return t1->get_table_class_value_time() < t2->get_table_class_value_time();
    }
    return t1->get_table_class_value_class() < t2->get_table_class_value_class();
}


//  UTILITY FUNCTION ENDS HERE


time_table::time_table(std::vector<table_class*> chromosome)
{
    this->chromosome = chromosome;
    fitness = calc_fitness_score();
}





int time_table::calc_fitness_score()
{
    int fitness = 0;
    sort(this->chromosome.begin(), this->chromosome.end(), sort_by_time);
    int time = 0;
    int _class = 0;
    std::string subject = "";
    int len = this->chromosome.size();
    for(int i = 0; i < len; i++)
    {
        time = this->chromosome[i]->get_table_class_value_time();
        _class = this->chromosome[i]->get_table_class_value_class();
        subject = this->chromosome[i]->get_table_class_value_subject();

        int skip_count = 0;

        for(int j = i + 1; j < len; j++)
        {
            if(this->chromosome[j]->get_table_class_value_time() > time)
            {
                break;
            }
            if(this->chromosome[j]->get_table_class_value_class() == _class || this->chromosome[j]->get_table_class_value_subject() == subject)
            {
                skip_count++;
                fitness++;
            }
        }
        i += skip_count;
    }
    return fitness;
}






std::vector<table_class*> time_table::mate(std::vector<table_class*> chromosome2, std::vector<table_class*> list_of_table)
{
    std::vector<table_class*> child;
    int len = this->chromosome.size();
    for(int i = 0; i < len; i++)
    {
        float p = random_integer(0, 100) / 100;

        if(p < 0.45)
        {
            child.push_back(this->chromosome[i]);
            continue;
        }

        if(p < 0.90)
        {
            child.push_back(chromosome2[i]);
            continue;
        }
        child.push_back(mutate_gene(list_of_table));
    }
    return child;
}




int time_table::get_fitness_value()
{
    return this->fitness;
}


std::vector<table_class*> time_table::get_chromosome_value()
{
    return this->chromosome;
}



//  TABLE CLASS FUNCTION IMPLEMENTATION


table_class::table_class(int _class, std::string subject, std::string day, int time)
{
    this->_class = _class;
    this->subject = subject;
    this->day = day;
    this->time = time;
}






int table_class::get_table_class_value_class()
{
    return this->_class;
}

std::string table_class::get_table_class_value_subject()
{
    return this->subject;
}

std::string table_class::get_table_class_value_day()
{
    return this->day;
}

int table_class::get_table_class_value_time()
{
    return this->time;
}


int table_class::update_table_class_values(int _class, std::string subject, std::string day, int time)
{
    if(_class != 0)
        this->_class = _class;
    if(subject != "")
        this->subject = subject;
    if(day != "")
        this->day = day;
    if(time != -1)
        this->time = time;
    return 1;
}



std::vector<table_class*> all_possible_time_table()
{
    std::vector<table_class*> res;
    std::string subjects[] = {"Math", "Science", "English", "Social", "French", "CPP", "Java"};
    int _class[5] = {6, 7, 8, 9, 10};
    int time[5] = {9, 10, 11, 12, 13};
    for(int __class : _class)
    {
        for(std::string _subject : subjects)
        {
            for(int _time : time)
            {
                res.push_back(new table_class(__class, _subject, "Monday", _time));
            }
        }
    }
    return res;
}



int random_integer(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (std::rand() % range);
    return random_int;
}




table_class* mutate_gene(std::vector<table_class*> list_of_table)
{
    int len = list_of_table.size();
    int random_int = random_integer(0, len - 1);
    return list_of_table[random_int];
}



std::vector<table_class*> create_genome(std::vector<table_class*> list_of_table)
{
    int len = 25;
    std::vector<table_class*> res;
    for(int i = 0; i < len; i++)
    {
        res.push_back(mutate_gene(list_of_table));
    }
    return res;
}