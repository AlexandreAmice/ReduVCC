#ifndef CLI_H
#define CLI_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <QTime>
#include "graphs.h"
#include "random_generator.h"
#include "algorithm_brelaz_ccp.h"
#include "algorithm_iggcc.h"
#include "algorithm_greedyindset.h"
#include "problem_ccp.h"
#include "time.h"
#include "statistics.h"

class cli
{
private:
    long i,succ_rate;
    unsigned long max_deg,min_deg;
    unsigned long long current_time,avg_time,avg_iter;
    double avg_deg,stdev_deg;
    char filename[PATH_MAX];
    double avg_brelaz;
    double avg_iggcc;
    double avg_gis;
    double avg_rls_is;
    refer min_iggcc;
    unsigned long w,n_max;
    bool is_optimal;
    QTime timer;    
    FILE *source;
    graph G;
    refer max_label;
    int choose_instance();
    int generate_instance();
    int choose_algorithm();
    int compute_statistics();
    void sleep(unsigned long long milisec);
    void try_all_permutations();
    void generate_permutation(long permutation[], bool occupied[], refer level, algorithm *alg);
    refer result_for_permutation[MAX_VERTICES];
    refer histogram[MAX_VERTICES];
    refer sizes[MAX_VERTICES];
    long bad_scenario_counter;
    long degree_distrib[MAX_VERTICES];
    problem_ccp *prob;
    double approx;
    long discrep;
public:
    cli();
    int start_cli();
};

#endif // CLI_H
