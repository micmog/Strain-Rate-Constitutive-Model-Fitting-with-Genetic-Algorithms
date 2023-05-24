# **Genetic Algorithm Fitting of Constitutive Models**

Genetic Algorithm Fitting of Strain Rate Dependent Constitutive Models

## Description

The code presented in this repository is used to fit constitutive models to experimental data. The code uses the Galgo-2 library; additinal information on the workings of the genetic-algorithm components of this repository may be found here (

[Here]: https://github.com/olmallet81/GALGO-2.0	"GALGO-2"

). The code takes data as a 4-column array in the Data.dat file; the format is: $\dot{\varepsilon_{eff}^{p}}$ `tab` $T$ `tab` $\varepsilon_{eff}^{p}$ `tab` $\sigma_{y}$

The code also reads various model parameters and bounds for the constitutive models from the Var.txt file

Currently the code can be used to fit the Johnson-Cook, Zerilli-Armstrong (BCC), Zerilli-Armstrong (FCC), and the Combined Zerilli-Armstrong (FCC and BCC) models. 

## Johnson-Cook Constitutive Model

Johnson-Cook's constitutive model. The von Mises flow stress is defined as:

$\sigma_{y}=\left(A+B\left(\varepsilon_{eff}^{p}\right)^{n}\right)\left(1+C\ln\left(\frac{\dot{\varepsilon_{eff}^{p}}}{\dot{\varepsilon_{0}}}\right)\right)\left(1-\left(\frac{T-T_{0}}{T_{m}-T_{0}}\right)^{m}\right)$

## Zerilli-Armstrong Constitutive Model

This is the Zerilli-Armstrong constitutive model in its general form. The von Mises flow stress is defined as:
$\sigma_{y}=\sigma_{a}+Be^{-\beta T}+B_{0}\sqrt{\varepsilon_{eff}^{p}}e^{-\alpha T}$

Where the athermal part of the flow stress is defined as:
$\sigma_{a}=\sigma_{g}+\frac{k_{h}}{\sqrt{l}}+K\varepsilon_{p}^{n}$

Where $frac{k_{h}}{\sqrt{l}}$ is the Hall-Petch strengthening limit. The exponents $\alpha$ and $\beta$ are defined as:

$\alpha=\alpha_{0}-\alpha_{1}\ln\left(\frac{\dot{\varepsilon_{eff}^{p}}}{\dot{\varepsilon_{0}}}\right)$
$\beta=\beta_{0}-\beta_{1}\ln\left(\frac{\dot{\varepsilon_{eff}^{p}}}{\dot{\varepsilon_{0}}}\right)$

where $\dot{\varepsilon_{eff}^{p}}$ is the current effective plastic strain rate. The used parameters depend on the crystal structure of the material. Generally, materials with FCC structure are described as:

$\sigma_{y}=\sigma_{a}+B_{0}\sqrt{\varepsilon_{eff}^{p}}e^{-\alpha T}$

and BCC materials as:
$\sigma_{y}=\sigma_{a}+Be^{-\beta T}$

The code will fit to the FCC, BCC and total combined Zerilli-Armstrong models.

### Var.txt Inputs

The code expects the following variables to be present in the Var.txt file in order to fit the various constitutive models:

| Variable Name   | Description                                                  |
| --------------- | ------------------------------------------------------------ |
| e0dot           | Reference Strain Rate                                        |
| Tm              | Melting Temperature (Johnson-Cook)                           |
| T0              | Reference Temperature                                        |
| A               | Initial yield strength                                       |
| B               | Hardening parameter                                                |
| n               |  	Hardening parameter                                          |
| C               |    	Strain rate hardening parameter                                                           |
| m               |    Thermal softening parameter                                                          |
| k_h_over_rootl  | Combines Microstructural stress intensity and average grain diameter ($k_{h}/sqrt{l}$)                                |
| sigma_g         |  Athermal flow stress                                                            |
| K               |   	Crystal structure dependent parameter                                                            |
| n_ZA            |   	Strain hardening parameter                                                            |
| B_ZA            |       	Strain rate hardening/thermal softening parameter                                                      |
| Beta_0          |    	Thermal softening parameter                                                          |
| Beta_1          |      	Strain rate hardening/thermal softening parameter                                                         |
| B_0             |     	Strain rate hardening/thermal softening parameter                                                         |
| Alpha_0         |  	Thermal softening parameter                                                             |
| Alpha_1         |   	Strain rate hardening/thermal softening parameter                                                            |
| N_Generations   | Number of Generations to run the Genetic Algorithm over      |
| Population_Size | Number of Chromosones, or population, for the Genetic Algorithm to utilise |

#### Example RMS Error Trend for the Various Constitutive Models Fitted by the Genetic Algorithm

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
