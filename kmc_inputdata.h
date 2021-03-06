/*  KMC Simulation for FCC lattice with diffusion
    by species swap and/or vacancy exchange
    Author: Tegar Wicaksono (tegar@alumni.ubc.ca)
    Written: March 2017

    Check repository below for the most updated version:
    https://github.com/tegarwicaksono/kmc-solute-diffusion-fcc
*/

#ifndef KMC_INPUTDATA_H_INCLUDED
#define KMC_INPUTDATA_H_INCLUDED

#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <regex>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <utility>

using namespace std;

class InputData{
public:
	vector<int>    box_length;		//in unit cell
	vector<double> unit_length;		//in Angstrom
	int number_of_solute_type;
	double abs_temperature; 		//in Kelvin
	double kB;                      //Boltzmann
	double eV;                      //eV
	vector<int> number_of_solute_per_type;

	vector<double> nn_distance;
	vector<vector<vector<double> > >  species_interaction_energy;	//in eV
	vector<vector<vector<double> > >  e_species;	//species_interaction_energy/kT
	//species[0] = matrix;
	//species[1] = solute 1;
	//species[2] = solute 2;

	int eff_ngb_distance, max_ngb_distance;
	vector<bool>            include_ngb;
	vector<double> 			rate_pre_exponential;		//in s^-1
	double					rate_factor;	//minimum of rate_pre_exponential
	vector<double>			solute_rate;	//rate_pre_exponential/rate_factor
	//rate_pre_exponential[1] = preexp_rate for solute 1
	//rate_pre_exponential[2] = preexp_rate for solute 2

	vector<double> 			solute_migration_energy;	//in eV
	vector<double>			e_migrate;	//solute_migration_energy/kT
	//solute_migration_energy[1] = migration energy barrier for solute 1

	double	start_time;
	unsigned long long int  initial_timestep;
	unsigned long long int 	final_timestep;
	unsigned long long int 	restart_timestep;
	unsigned long long int 	total_KMC_steps;
	bool dump_snapshot;
	bool dump_restart;
	bool start_from_restart;

	vector<bool> include_species_in_snapshot;
	unsigned long long int  period_snapshot;
	unsigned long long int 	period_restart;

	vector<string> parameter_name;

	InputData();
    InputData(const InputData& other);
    InputData(InputData&& other);
    InputData& operator= (InputData other);

	virtual ~InputData() = default;
    friend void swap(InputData &a, InputData &b);
	void assign_parameter_name();
	void assign_nearest_neighbour_distance();
	vector<string> split_token(const string &input);
	void assign_parameter(const int &it, const vector<string> &tokens, unordered_set<int> &spec_param);
	bool check_if_parameters_assigned(const unordered_set<int> &spec_param);
	bool process_input_line(const string &input, unordered_set<int> &spec_param);
	bool read_from_file(const string &filename);
	void convert_input_data();
	void initialize(const string &filename);
	void print_scaled_properties();
};


#endif // KMC_INPUTDATA_H_INCLUDED
