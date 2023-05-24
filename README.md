# **Genetic Algorithm Fitting of Constitutive Models**

Genetic Algorithm Fitting of Strain Rate Dependent Constitutive Models

## Description

The code presented in this repository is used to fit constitutive models to experimental data. The code uses the Galgo-2 library; additinal information on the workings of the genetic-algorithm components of this repository may be found here (

[Here]: https://github.com/olmallet81/GALGO-2.0	"GALGO-2"

). The code takes data as a 4-column array in the Data.dat file; the format is: *strain_rate* `tab` *temperature* `tab` *strain* `tab` *stress*

The code also reads various model parameters and bounds for the constitutive models from the Var.txt file

Currently the code can be used to fit the Johnson-Cook, Zerilli-Armstrong (BCC), Zerilli-Armstrong (FCC), and the Combined Zerilli-Armstrong (FCC and BCC) models. 

### Var.txt Inputs

| Variable Name   | Description                                                  |
| --------------- | ------------------------------------------------------------ |
| e0dot           | Reference Strain Rate                                        |
| Tm              | Melting Temperature (Johnson-Cook)                           |
| T0              | Reference Temperature                                        |
| A               |                                                              |
| B               |                                                              |
| n               |                                                              |
| C               |                                                              |
| m               |                                                              |
| k_h_over_rootl  | Zerilli-Armstrong parameter                                  |
| sigma_g         |                                                              |
| K               |                                                              |
| n_ZA            |                                                              |
| B_ZA            |                                                              |
| Beta_0          |                                                              |
| Beta_1          |                                                              |
| B_0             |                                                              |
| Alpha_0         |                                                              |
| Alpha_1         |                                                              |
| N_Generations   | Number of Generations to run the Genetic Algorithm over      |
| Population_Size | Number of Chromosones, or population, for the Genetic Algorithm to utilise |

![Example Output](https://github.com/micmog/GA_JC/blob/main/images/GAfit_steel.png?raw=true)




## Compilation

The main.cpp file can be compiled on the command line using the following command:

```
$ g++ -std=c++11 -O3 -Wall main.cpp -o run
```

and then running:

```
$ ./run
```

If the objective function is time consuming you can go parallel by compiling with OpenMP enabled:

```
$ g++ -fopenmp -std=c++11 -O3 -Wall main.cpp -o run
```

Note - parallel implementation not extensively tested.
