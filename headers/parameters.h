#pragma once
#define KIND float  

//Parametros principales:
const size_t N = 10000; //Cantidad de agentes.
const KIND   L = 475;   //Largo del sistema. Area = L*L.

//Parametros de evolución del sistema.
//Pre-condición para estos parámetros (dt * v < 0.1):
KIND delta_time = 0.05;
KIND active_velocity  = 0.01; //Velocidad de las partículas cuando no interactúan.

//0 -> dist. exponencial, 1 -> dist. power law. Cualquier otro dist. uniforme.
const int velocity_distribution = 2;

const KIND delta = 50; // wave profile change
const KIND x_wave = 20; // wave profile change

//Condición inicial SIR
const KIND   p_init  = 0.0, //Infectadas iniciales.
			 p_rinit = 0.0, //Refractarias iniciales (elegidas al azar).
			 p_dinit = 0.0; //Refractarias iniciales (elegidas a partir de lista de velocidades).

const int spin = 3; //Estados internos.

const bool animation = false;
const int  anim_step = 50;

/*Tiempos característicos y probabilidades por unidad de tiempo*/
const KIND  tau_t = 0  , p_transmision = 1, //p_transmision = (1 / tau_t) * delta_time, //sane---->infected
			tau_i = 200, p_infection   = (1 / tau_i) * delta_time, //infected--->refractary
			tau_r = 500, p_recfractary = (1 / tau_r) * delta_time; //refractary--->sane


const KIND alpha = 100, p_rotation = (1 / alpha) * delta_time;    // tumbling rates angle_1 -> angle_2


/* Para distribución power-law hay que fitear las constantes */
// 1.7713537054317126, //  v=0.1
// 1.8663355897425058, //  v=0.08
// 2.0960715631010567, //  v=0.05
// 2.2303794574079356, //  v=0.04

// k_alpha for case(2) velocity distribution
const KIND  k_powerl = 2.09600,
			k_alpha  = 4,            
            v_max    = 4.;

KIND v_min  = 0.01;


//Constantes:
const KIND  Pi       = 3.14159265358979323846,
			dos_Pi   = 2 * Pi,
			infinity = 1000000000;

//Características geométricas de agentes.
const KIND  radio    = 1.,
			diameter = 2. * radio;

//Características del medio en el que se mueven los agentes.
const KIND beta           = 1;                    //comentario sobre qué representa.
const KIND gamma_friction = 3.92 * active_velocity; //transforma: vel -> fuerza.
