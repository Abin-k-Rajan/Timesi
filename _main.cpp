#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iomanip>
#include "src\time_table\time_table.h"

#define POPULATION_SIZE 100


int main()
{
    srand((unsigned)(time(0)));

    int generation = 0;
    std::vector<table_class*> list_of_table = all_possible_time_table();
    std::vector<time_table*> population;
    bool found = false;

    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        population.push_back(new time_table(create_genome(list_of_table)));
    }

    while(!found)
    {
        sort(population.begin(), population.end(), sort_by_fitness);

        if(population[0]->get_fitness_value() <= 0)
        {
            found = true;
            break;
        }

        std::vector<time_table*> new_generation;

        int s = (10 * POPULATION_SIZE) / 100;

        for(int i = 0; i < s; i++)
        {
            new_generation.push_back(population[i]);
        }

        s = (90 * POPULATION_SIZE) / 100;

        for(int i = 0; i < s; i++)
        {
            int len = population.size();
            int r = random_integer(0, len - 1);
            time_table* parent1 = population[r];
            r = random_integer(0, len - 1);
            time_table* parent2 = population[r];
            new_generation.push_back(new time_table(parent1->mate(parent2->get_chromosome_value(), list_of_table)));
        }
        population = new_generation;
        //std::cout<<generation<<" -> "<<population[0]->get_fitness_value()<<std::endl;
        generation++;
        //found = 1;
        if(generation > 10000)
        {
            std::cout<<"Could not find a solution!";
            return 0;
        }
    }
    std::cout<<generation<<" -> "<<population[0]->get_fitness_value()<<std::endl;
    std::vector<table_class*> final_table = population[0]->get_chromosome_value();
    sort(final_table.begin(), final_table.end(), sort_by_time);
    sort(final_table.begin(), final_table.end(), sort_by_class);

    std::cout<<"Class"<<std::setw(25)<<"9:00"<<std::setw(25)<<"10:00"<<std::setw(25)<<"11:00"<<std::setw(25)<<"12:00"<<std::setw(25)<<"13:00"<<std::endl;
    int line_check = 0;
    for(table_class* x : final_table)
    {
        if(line_check == 0)
        {
            std::cout<<x->get_table_class_value_class()<<std::setw(29);
        }
        std::cout<<x->get_table_class_value_subject();
        line_check++;
        if(line_check == 5)
        {
            std::cout<<std::endl;
            line_check = 0;
            continue;
        }
        std::cout<<std::setw(25);
    }

    return 0;
}