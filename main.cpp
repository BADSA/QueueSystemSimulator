#include "headers/dist_functions.h"
#include "headers/frecuencies.h"
#include "headers/prob.h"
#include "headers/prob_tests.h"
#include "headers/readers.h"
#include "headers/writers.h"
#include "headers/globals.h"

#include <queue>
#include <vector>
#include <unistd.h>
#include <random>
#include <string.h>
#include <ctime>

#define BIG 999999.99
#define vi vector<int>
#define packs_amount 1000

using namespace std;


struct package{

    int id;
    double wait_time;
    double service_time;
};


package *packs;

queue<double> discharger_queue, area_locator_queue;
queue<double> truck_queue;
queue<int> computer_queue;

int quantities[] = { 3 , 2 , 2 , 1 };


double waits_discharger[packs_amount];
double waits_area[packs_amount];
double waits_computer[packs_amount];
double waits_truck[packs_amount];

int discharger_amount = quantities[0], area_locator_amount = quantities[1];
int computer_amount = quantities[2], truck_amount = quantities[3];
const int phases_amount = 4;
double discharger_cost = 29.4, area_locator_cost = 28.3;
double computer_cost = 12.1, truck_cost = 69.6;

double discharger_wt, area_locator_wt, computer_wt, truck_wt;


int best_dis, best_area, best_com, best_tru;
double best_media = BIG, best_cost;
double best_diff, best_variance;

void *discharger_process(void * args);
void *area_locator_process(void * args);
void *computer_process(void * args);
void *truck_process(void * args);
double simulation(int i, int j, int k, int l);
double getcost(int i, int j, int k, int l);


double getvariance(double media){
    double variance = 0.0;
    for (int i =0; i<packs_amount; i++){
        double totwait = waits_discharger[i] + waits_area[i] +
                waits_computer[i] + waits_truck[i];
        variance += pow(totwait - media , 2.0);
    }
    return  variance / (packs_amount-1);
}

/*
    Genetic Algorithm
*/

int population_amount = 100;
int generations = 1000;


vector< vi > gen_population(){
    vector< vi > population;
    for (int i =0 ; i<population_amount; i++){
        vi ind;
        for(int i=0; i<4; i++){
            int x = rand() % packs_amount + 1;
            ind.push_back(x);
        }
        population.push_back(ind);
    }
    return population;
}


vi mutate(vi indiv){
    int r = rand() % 1000;
    int incordec = rand() % 2;
    if (r>=0 && r<=399){
        // Mutate gen #4 - Trucks amount (most expensive)
        if (incordec) indiv[3] = min(packs_amount, indiv[3] + 1);
        else indiv[3] = max(1, indiv[3] - 1);
    }else if (r>=400 && r<=699){
        // Mutate gen #2 - Area locator amount (higher media)
        if (incordec) indiv[1] = min(packs_amount, indiv[1] + 1);
        else indiv[1] = max(1, indiv[1] - 1);
    }else{
        r = rand() % 2;
        if (r){
            // Mutate gen #1
            if (incordec) indiv[0] = min(packs_amount, indiv[0] + 1);
            else indiv[0] = max(1, indiv[0] - 1);
        }else{
            // Mutate gen #3
            if (incordec) indiv[2] = min(packs_amount, indiv[2] + 1);
            else indiv[2] = max(1, indiv[2] - 1);
        }
    }
    return indiv;
}


/*
Elite = {e1, e2, e3, e4}
Ind   = {i1, i2, i3, i4}
          ==
Res   = {i1, e2, i3, e4}
*/
vi cross(vi elite, vi ind){
    vi result(4);
    result[0] = ind[0];
    result[1] = elite[1];
    result[2] = ind[3];
    result[3] = elite[3];
    return result;
}


void run_generations(){
    best_cost = best_diff = BIG;
    int mutations = 10;
    vi elite(4);
    vector< vi > population = gen_population();
    while(generations--){

        for(int i=0; i<mutations; i++){
            int idx = rand() % population_amount;
            vi ind = population[idx];
            population[idx] = mutate(ind);
        }

        for (int i=0; i<population.size(); i++){
            vi ind = population[i];
            //printf("Ind #%d {%d,%d,%d,%d}\n", i+1,ind[0], ind[1], ind[2], ind[3]);
            double media = simulation(ind[0], ind[1], ind[2], ind[3]);
            double diff = fabs(45-media);
            double cost = getcost(ind[0], ind[1], ind[2], ind[3]);
            if ( diff < best_diff){
                if (cost < best_cost){
                    best_diff = diff;
                    best_cost = cost;

                    best_dis = ind[0];
                    best_area = ind[1];
                    best_com = ind[2];
                    best_tru = ind[3];
                    elite[0] = best_dis;
                    elite[1] = best_area;
                    elite[2] = best_com;
                    elite[3] = best_tru;
                }
            }
        }
        population = gen_population();
        vi ind;
        for (int i=0; i<population.size(); i++){
            ind = population[i];
            population[i] = cross(elite, ind);
        }
    }

}


void run_generations2(){
    best_variance = BIG;
    int mutations = 10;
    vi elite(4);
    vector< vi > population = gen_population();
    while(generations--){

        for(int i=0; i<mutations; i++){
            int idx = rand() % population_amount;
            vi ind = population[idx];
            population[idx] = mutate(ind);
        }

        for (int i=0; i<population.size(); i++){
            vi ind = population[i];

            double media = simulation(ind[0], ind[1], ind[2], ind[3]);
            double variance = getvariance(media);
            if ( variance < best_variance){
                best_variance = variance;

                best_dis = ind[0];
                best_area = ind[1];
                best_com = ind[2];
                best_tru = ind[3];
                elite[0] = best_dis;
                elite[1] = best_area;
                elite[2] = best_com;
                elite[3] = best_tru;
            }
        }
        population = gen_population();
        vi ind;
        for (int i=0; i<population.size(); i++){
            ind = population[i];
            population[i] = cross(elite, ind);
        }
    }

}

/*
    End Genetic Algorithm
*/




double simulation(int i, int j, int k, int l){
    discharger_amount = i;
    area_locator_amount = j;
    computer_amount = k;
    truck_amount = l;
    pthread_t *p;
    p = (pthread_t *) calloc(phases_amount, sizeof(pthread_t));

    pthread_create(&p[0], NULL, &discharger_process, NULL);
    pthread_create(&p[1], NULL, &area_locator_process, NULL);
    pthread_create(&p[2], NULL, &computer_process, NULL);
    pthread_create(&p[3], NULL, &truck_process, NULL);

    for (int i =0; i<phases_amount; i++){
        pthread_join(p[i], NULL);
    }

    double media = (discharger_wt + area_locator_wt +
                    computer_wt + truck_wt) / (packs_amount * 1.0);
    return media;
}



double getcost(int i, int j, int k, int l){
    return i*discharger_cost + j*area_locator_cost +
           k*computer_cost + l*truck_cost;
}

void obj1(){

    for (int i=1 ; i < 31; i++)
        for (int j=1 ; j < 32; j++)
            for (int k=1 ; k < 73; k++)
                for (int l=1 ; l < 14; l++) {
                    double cost = getcost(i,j,k,l);
                    if (cost <= 1000) {
                        double media = simulation(i, j, k, l);
                        printf("#%d Media : %f\n", i * j * k * l, media);
                        if (media < best_media) {
                            best_cost = cost;
                            best_media = media;
                            best_dis = i;
                            best_area = j;
                            best_com = k;
                            best_tru = l;
                        }
                    }
                }
}

void init_packages(){
    for (int i = 0; i < packs_amount; i++){
        packs[i].id = i+1;
        packs[i].wait_time = 0.0;
        packs[i].service_time = 0.0;
    }
}

void printStats(){
    printf("==============================\n");
    printf("Dischargers %d\n",best_dis);
    printf("Area locators %d\n",best_area);
    printf("Computers %d\n",best_com);
    printf("Trucks %d\n",best_tru);
    printf("Media %f\n",best_media);
    printf("Cost %f\n",best_cost);
    printf("==============================\n");
}


void printStats2(){
    printf("==============================\n");
    printf("Dischargers %d\n",best_dis);
    printf("Area locators %d\n",best_area);
    printf("Computers %d\n",best_com);
    printf("Trucks %d\n",best_tru);
    printf("Cost %f\n",best_cost);
    printf("Diff to 45 %f\n",best_diff);
    printf("==============================\n");
}

int findnext(double array[], int size){
    int index = 0;
    for(int i = 1; i < size; i++) {
        if(array[i] < array[index])
            index = i;
    }
    return index;
}

void *discharger_process(void * args){
    double total_wait_time = 0;
    int n = discharger_amount;
    queue<double> q = discharger_queue;
    double servers[n];
    memset(servers, 0 , sizeof servers);

    memset(waits_discharger, 0 , sizeof waits_discharger);

    for (int i = 0; i<n; i++){
        servers[i] = q.front();
        q.pop();
    }
    int curr = n;
    while(q.size()>0){
        int idx = findnext(servers, n);
        total_wait_time += servers[idx];
        waits_discharger[curr++] = servers[idx];
        servers[idx] += q.front();
        q.pop();
    }
    discharger_wt = total_wait_time;

}

void *area_locator_process(void * args){
    double total_wait_time = 0;
    int n = area_locator_amount;
    queue<double> q = area_locator_queue;
    double servers[n];
    memset(servers, 0 , sizeof servers);
    memset(waits_area, 0 , sizeof waits_area);

    for (int i = 0; i<n; i++){
        servers[i] = q.front();
        q.pop();
    }
    int curr = n;
    while(q.size()>0){
        int idx = findnext(servers, n);
        total_wait_time += servers[idx];
        waits_area[curr++] = servers[idx];
        servers[idx] += q.front();
        q.pop();
    }
    area_locator_wt = total_wait_time;
}

void *computer_process(void * args){
    double total_wait_time = 0;
    int n = computer_amount;
    queue<int> q = computer_queue;
    double servers[n];
    memset(servers, 0 , sizeof servers);
    memset(waits_computer, 0 , sizeof waits_computer);

    for (int i = 0; i<n; i++){
        servers[i] = q.front();
        q.pop();
    }
    int curr = n;
    while( q.size() >=1){
        int idx = findnext(servers, n);
        total_wait_time += servers[idx];
        waits_computer[curr++] = servers[idx];
        servers[idx] += q.front();
        q.pop();
    }
    computer_wt = total_wait_time;
}

void *truck_process(void * args){
    double total_wait_time = 0;
    int n = truck_amount;
    queue<double> q = truck_queue;
    double servers[n];
    memset(servers, 0 , sizeof servers);
    memset(waits_truck, 0 , sizeof waits_truck);

    for (int i = 0; i<n; i++){
        servers[i] = q.front();
        q.pop();
    }
    int curr = n;
    while(q.size()>0){
        int idx = findnext(servers, n);
        total_wait_time += servers[idx];
        waits_truck[curr++] = servers[idx];
        servers[idx] += q.front();
        q.pop();
    }
    truck_wt = total_wait_time;
}

int main() {
    time_t start = time(nullptr);
    srand(time(NULL));
    packs = (package *) calloc(packs_amount, sizeof(package));

    random_device rd;
    default_random_engine generator(rd());
    exponential_distribution<double> exp1(1/12.911); // Media for S1.
    normal_distribution<double> normal(85.8763, 11.9308); // Media and Deviation for S2
    poisson_distribution<int> poisson(10.4126); // Media for S3.
    exponential_distribution<double> exp2(1/30.2004); // Media for S4.

    for (int i =0 ; i<packs_amount; i++){
        discharger_queue.push( exp1(generator) );
        area_locator_queue.push( normal(generator) );
        computer_queue.push( poisson(generator) );
        truck_queue.push( exp2(generator) );
    }

    //obj1();
    run_generations2();


    time_t final = time(nullptr);

    double duration = difftime(final,start);
    printf("Duracion %f\n",duration);
    printStats();
    printf("Varianza es: %f\n",best_variance);


    return 0;
}
