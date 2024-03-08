/* Autor: Benjamín R. Marcolongo. FAMAF-UNC.
/* Email: benjaminmarcolongo@gmail.com / benjaminmarcolongo@unc.edu.ar 
 *-----------------------------------------------------------------------------------------------------------
 * Programa para evolucionar un sistema de N agentes en el tiempo.
 *-----------------------------------------------------------------------------------------------------------
 * Agentes:
 *		i.   Las velocidades de los N agentes pueden ser uniformes o tomadas aleatoriamente.
 *		      1. Las distribuciones por defecto son de tipo exponencial o de ley de potencias.
 *		ii.  Pueden interactuar a través de un potencial u otra forma (una red neuronal i.e).
 *			  1. El potencial por defecto es de esferas blandas.
 *		ii.  Están confinados a un toroide topológico-
 *			  1. El tamaño característico del toro se denota con L (lado del cuadrado).
 *		iii. Poseen un estado interno, caracterizado por un número entero.
 *			  1. Este estado puede o no interactaur con la dinámica espacial.
 *		iv.  El estado interno puede evolucionar en el tiempo.
 *			  1. Esta dinámica está regulada, genéricamente, con una distribución de poisson.
 *-----------------------------------------------------------------------------------------------------------
 * Red compleja: (falta programar, esta en versiones anteriores)
 *			i.  El programa trackea todo el sistema de interacciones y guarda la red compleja resultante.
 *			ii. La red compleja puede ser la asociada a la propagación del estado interno o la de contactos
 *-----------------------------------------------------------------------------------------------------------
 * Estuctura de datos para optimizar la búsqueda de interacciones entre agentes:
 *	   i.   Utiliza un red-and-black tree (BST) implementado en c++ como set.
 			Esta estructura es equivalente a un linked list.
 *	   ii.  Cada agente está indexado por un int.
 *	   iii. Se construye una grilla con cuadrículas de tamaño 1x1 y cada a una se le asigna un set.
 *	   iv.  Cada set contiene los agentes que están en cada cuadrícula proyectando su posción sobre la grilla.
 *----------------------------------------------------------------------------------------------------------- 
*/

#include <bits/stdc++.h>
#include "./headers/agentes.h"

#define CHECK(val_1, val_2) if (val_1 % val_2 == 0)
#define TIME(val_1, val_2) static_cast<float>(val_1) * val_2

using namespace std;

int main(void) {
	
	/* DEFINICIÓN DE ARCHIVOS DE SALIDA DEL PROGRAMA */
	ofstream epidemic("data/epidemia.txt", ios_base::app);
	ofstream anim("data/animacion.txt", ios_base::app);
	ofstream metrica("data/metrica.txt", ios_base::app);
	ofstream simulation_data("data/simulation_data.txt", ios_base::app);
	ofstream velocities_data("data/velocites_data.txt", ios_base::app);

	print_simulation_parameters(simulation_data);

	/* METRICA Y PERFORMANCE */
	float  updates = 0;  // Contador de updates.
	size_t start_s = clock();

	/* SIMULACION */
	gen.seed(seed);

	for (KIND vel_crit = 0.01; vel_crit < 0.05; vel_crit += 0.005) {
		
		active_velocity = vel_crit;
		v_min = (k_alpha - 2) / (k_alpha -1) * active_velocity;

		ofstream final_state("data/evolution_" + to_string(vel_crit) + ".txt", ios_base::app);
		cout << "ACTIVE VEL: " << active_velocity << endl;
		cout << "V_MIN     : " << v_min           << endl;
		
		for (size_t n_simulaciones = 0; n_simulaciones < 200; n_simulaciones++) {
			print_header(n_simulaciones);
			/* DECLARACIÓN DE VARIABLES */
			vector<particle> system,
							 system_new;
			vector<bool>     inter;        	// Flag de interacción.
			vector<size_t>   state_vector;  // (S, I, R) vector.
			
			inter.resize(N, false);
			state_vector.resize(spin, 0);

			/* INICIALIZAMOS GRILLA */
			vector<vector<set<size_t>>> grid;
			size_t num_grid = floor(L);
			grid.resize(num_grid);
			for (size_t i = 0; i < grid.size(); i++) grid[i].resize(num_grid);

			/* CONDICIÓN INICIAL */
			init_system(system, state_vector, grid);
			system_new.resize(system.size());
			print_state(state_vector);

			vector<KIND> velocities;

			for (int p=0; p<N; p++) {
				velocities.push_back(system[p].velocity);
				velocities_data << system[p].velocity << " " << active_velocity << endl;
			}

			cout << endl;
			auto maxima_velocidad = max_element(velocities.begin(), velocities.end());
			cout << "MAX VEL = " <<  *maxima_velocidad << endl; 
	 		delta_time = min(0.05, 0.1 / *maxima_velocidad);
	 		cout << "DELTA_TIME = " << delta_time << endl;
			
			/* EVOLUCIÓN DEL SISTEMA */
			int time_step = 0;
			KIND i_max = 0, t_max = 0;
			while (state_vector[1] > 0) {
				CHECK(time_step, (int)2e02) print_epidemic_tofile(epidemic, state_vector, time_step);
				CHECK(time_step, (int)2e04) printf("Time: %0.f\n", TIME(time_step, delta_time));
				time_step++;

				update_system(system, system_new, state_vector, grid, inter, time_step, anim);
				
				if (i_max < state_vector[1]) {
					i_max = state_vector[1];
					t_max = TIME(time_step, delta_time);
				}
			}  // WHILE

			updates += static_cast<float>(time_step);

			/* ESCRITURA DE RESULTADOS */
			print_finalstate_tofile(final_state, state_vector, i_max, t_max, time_step);
			print_result_header();
			print_state(state_vector);
			cout << endl;
		}  // FOR SIMUL
		final_state.close();
	}
	/* IMPRESION EN PANTALLA */
	int   stop_s       = clock();
	float cps          = static_cast<float>(CLOCKS_PER_SEC);
	float time_elapsed = static_cast<float>(clock() - start_s) / cps;
	float metric       = updates*static_cast<float>(N) / time_elapsed;

	cout << "Time[seg]   : " << time_elapsed  << endl;
	cout << "Metrica[pps]: " << metric       << endl;

	metrica  << metric << endl;


	epidemic.close();
	anim.close();
	metrica.close();
	simulation_data.close();
	velocities_data.close();
	return 0;
}

