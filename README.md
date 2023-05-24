# **Genetic Algorithm Fitting of Constitutive Models**

Genetic Algorithm Fitting of Strain Rate Dependent Constitutive Models

## Description

The code presented in this repository is used to fit constitutive models to experimental data. The code uses the Galgo-2 library; additinal information on the workings of the genetic-algorithm components of this repository may be found here:

[GALGO-2](https://github.com/olmallet81/GALGO-2.0)

The code takes data as a 4-column array in the Data.dat file; the format is: $\dot{\varepsilon_{eff}^{p}}$ `tab` $T$ `tab` $\varepsilon_{eff}^{p}$ `tab` $\sigma_{y}$. The code can be used with data of any strain rate and temperature, or combination thereof.

The code also reads the various model parameters and bounds for the constitutive models from the Var.txt file

Currently the code can be used to fit the Johnson-Cook, Zerilli-Armstrong (BCC), Zerilli-Armstrong (FCC), and the Combined Zerilli-Armstrong (FCC and BCC) models. 

## Johnson-Cook Constitutive Model

Johnson-Cook's constitutive model. The von Mises flow stress is defined as:

$\sigma_{y}=\left(A+B\left(\varepsilon_{eff}^{p}\right)^{n}\right)\left(1+C\ln\left(\frac{\dot{\varepsilon_{eff}^{p}}}{\dot{\varepsilon_{0}}}\right)\right)\left(1-\left(\frac{T-T_{0}}{T_{m}-T_{0}}\right)^{m}\right)$

## Zerilli-Armstrong Constitutive Model

This is the Zerilli-Armstrong constitutive model in its general form. The von Mises flow stress is defined as:
$\sigma_{y}=\sigma_{a}+Be^{-\beta T}+B_{0}\sqrt{\varepsilon_{eff}^{p}}e^{-\alpha T}$

Where the athermal part of the flow stress is defined as:
$\sigma_{a}=\sigma_{g}+\frac{k_{h}}{\sqrt{l}}+K\varepsilon_{p}^{n}$

Where $\frac{k_{h}}{\sqrt{l}}$ is the Hall-Petch strengthening limit. The exponents $\alpha$ and $\beta$ are defined as:

$\alpha=\alpha_{0}-\alpha_{1}\ln\left(\frac{\dot{\varepsilon_{eff}^{p}}}{\dot{\varepsilon_{0}}}\right)$
$\beta=\beta_{0}-\beta_{1}\ln\left(\frac{\dot{\varepsilon_{eff}^{p}}}{\dot{\varepsilon_{0}}}\right)$

where $\dot{\varepsilon_{eff}^{p}}$ is the current effective plastic strain rate. The used parameters depend on the crystal structure of the material. Generally, materials with FCC structure are described as:

$\sigma_{y}=\sigma_{a}+B_{0}\sqrt{\varepsilon_{eff}^{p}}e^{-\alpha T}$

and BCC materials as:
$\sigma_{y}=\sigma_{a}+Be^{-\beta T}$

The code will fit to the FCC, BCC and total combined Zerilli-Armstrong models.

### Var.txt Inputs

The code expects the following variables to be present in the Var.txt file in order to fit the various constitutive models:

| Variable Name   | Description                                                  | Symbol in Above Equations|
| --------------- | ------------------------------------------------------------ |---------------------------|
| e0dot           | Reference Strain Rate                                        |$\dot{\varepsilon_{0}}$|
| Tm              | Melting Temperature (Johnson-Cook)                           |$T_m$|
| T0              | Reference Temperature                                        |$T_0$|
| A               | Initial yield strength (Johnson-Cook)                                       |$A$|
| B               | Hardening parameter  (Johnson-Cook)                                         |$B$|
| n               |  	Hardening parameter(Johnson-Cook)                                       |$n$|
| C               |    	Strain rate hardening parameter  (Johnson-Cook)                         |$C$|
| m               |    Thermal softening parameter  (Johnson-Cook)                              |$m$|
| k_h_over_rootl  | Combines Microstructural stress intensity and average grain diameter ($\frac{k_{h}}{\sqrt{l}}$) |$\frac{k_{h}}{\sqrt{l}}$|
| sigma_g         |  Athermal flow stress (Zerilli-Armstrong)                                                           |$\sigma_{g}$|
| K               |   	Crystal structure dependent parameter (Zerilli-Armstrong)                                                           |$K$|
| n_ZA            |   	Strain hardening parameter (Zerilli-Armstrong)                                                           |$n$|
| B_ZA            |       	Strain rate hardening/thermal softening parameter (Zerilli-Armstrong)                                                     |$B$|
| Beta_0          |    	Thermal softening parameter (Zerilli-Armstrong)                                                         |$\beta_{0}$|
| Beta_1          |      	Strain rate hardening/thermal softening parameter (Zerilli-Armstrong)                                                        |$\beta_{1}$|
| B_0             |     	Strain rate hardening/thermal softening parameter (Zerilli-Armstrong)                                                        |$B_{0}$|
| Alpha_0         |  	Thermal softening parameter (Zerilli-Armstrong)                                                            |$\alpha_{0}$|
| Alpha_1         |   	Strain rate hardening/thermal softening parameter  (Zerilli-Armstrong)                                                          |$\alpha_{1}$|
| N_Generations   | Number of Generations to run the Genetic Algorithm over      |....|
| Population_Size | Number of Chromosones, or population, for the Genetic Algorithm to utilise |....|


The code will fit the 4 constitutive models to the data provided. Following completion the user will be provided with a series of optimised fitting parameters that minimised the RMS error between the relative constitutive models and supplied data. Below shows how the RMS error evolves as a function of generation number:

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
