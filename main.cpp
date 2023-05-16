
#include "./src/Galgo.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

// objective class example
template <typename T>
class MyObjective
{


//private:
public:

   static std::vector<T> ObjectiveJC(const std::vector<T>& x)
   {

//read();
std::vector<double> strain_rate_data;
std::vector<double> Temp_data;
std::vector<double> strain_data;
std::vector<double> stress_data;


  //std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    double strain_dot,Tstar,pl_strain,stress;
    while (myfile >> strain_dot >> Tstar >> pl_strain >> stress/* getline (myfile,line) */)
    {
       //std::cout << pl_strain<<std::endl;
     // std::cout << line << '\n';
      strain_rate_data.push_back(strain_dot);
      Temp_data.push_back(Tstar);
      strain_data.push_back(pl_strain);
      stress_data.push_back(stress);

    }
    myfile.close();
  }
  else std::cout << "Unable to open file";


const char *fileName="Var.txt";
    std::ifstream paramFile;
    paramFile.open(fileName);
    std::string line;
    std::string key;
    double value;
std::map <std::string, double> params; // errors
while ( paramFile >> key >> value ) {
    params[key] = value; // input them into the map
}
//params["e0dot"];
//params["Tm"];
//params["T0"];


 // std::cout<<params["Tm"]<<std::endl;
 // std::cout<<stress_data[9]<<std::endl;

 //double eps_star = 1000.0;//normalised strain rate
 //double T_m = 1773.0;
 //double T_0 = 50.0;
 //double e_dot_0 = 0.1;

std::vector<double> Result_data;//[strain_data.size()];
T obj = 0.0;
for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{

double result_at_strain = (x[0]+(x[1]*pow(strain_data[i],x[2])))*(1.0+(x[3]*std::log(strain_rate_data[i]/params["e0dot"])))*(1.0-pow(((Temp_data[i]-params["T0"])/(params["Tm"]-params["T0"])),x[4]));
Result_data.push_back(result_at_strain);

//std::cout<<i<<"\t"<<strain_data[i]<<"\t"<<Result_data[i]<<std::endl;

obj+=pow(Result_data[i]-stress_data[i],2.0);
}
//std::cout<<obj<<std::endl;

//Minimise difference so needs to be -ve

     // T obj = (pow(x[0],2)-(x[0]*x[1]) +x[2]);
      return {-sqrt(obj/strain_data.size())};

   }

      static std::vector<T> ObjectiveZA_BCC(const std::vector<T>& x)
   {

//read();
std::vector<double> strain_rate_data;
std::vector<double> Temp_data;
std::vector<double> strain_data;
std::vector<double> stress_data;


  //std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    double strain_dot,Tstar,pl_strain,stress;
    while (myfile >> strain_dot >> Tstar >> pl_strain >> stress)
    {
       //std::cout << pl_strain<<std::endl;
     // std::cout << line << '\n';
      strain_rate_data.push_back(strain_dot);
      Temp_data.push_back(Tstar);
      strain_data.push_back(pl_strain);
      stress_data.push_back(stress);

    }
    myfile.close();
  }
  else std::cout << "Unable to open file";


  const char *fileName="Var.txt";
    std::ifstream paramFile;
    paramFile.open(fileName);
    std::string line;
    std::string key;
    double value;
std::map <std::string, double> params; // errors
while ( paramFile >> key >> value ) {
    params[key] = value; // input them into the map
}

//params["k_h_over_rootl"]
 // double k_h_over_rootl = 1.0;//????

std::vector<double> Result_data;//[strain_data.size()];
T obj = 0.0;
for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{

double result_at_strain = (x[0]+params["k_h_over_rootl"]+(x[1]*pow(strain_data[i],x[2])))+(x[3]*std::exp(-(x[4]-(x[5]*(std::log(strain_rate_data[i]/params["e0dot"]))))*Temp_data[i]));
//std::cout<<"x4: "<<x[4]<<", x5: "<<x[5]<<std::endl;
//double result_at_strain = std::exp(-(x[4]-(x[5]*(std::log(strain_rate_data[i]))))*Temp_data[i]);
Result_data.push_back(result_at_strain);

//std::cout<<i<<"\t"<<strain_data[i]<<"\t"<<Result_data[i]<<std::endl;

obj+=pow(Result_data[i]-stress_data[i],2.0);
}
//std::cout<<obj<<std::endl;

//Minimise difference so needs to be -ve

     // T obj = (pow(x[0],2)-(x[0]*x[1]) +x[2]);
      return {-sqrt(obj/strain_data.size())};

   }

         static std::vector<T> ObjectiveZA_FCC(const std::vector<T>& x)
   {

//read();
std::vector<double> strain_rate_data;
std::vector<double> Temp_data;
std::vector<double> strain_data;
std::vector<double> stress_data;


  //std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    double strain_dot,Tstar,pl_strain,stress;
    while (myfile >> strain_dot >> Tstar >> pl_strain >> stress)
    {
       //std::cout << pl_strain<<std::endl;
     // std::cout << line << '\n';
      strain_rate_data.push_back(strain_dot);
      Temp_data.push_back(Tstar);
      strain_data.push_back(pl_strain);
      stress_data.push_back(stress);

    }
    myfile.close();
  }
  else std::cout << "Unable to open file";


    const char *fileName="Var.txt";
    std::ifstream paramFile;
    paramFile.open(fileName);
    std::string line;
    std::string key;
    double value;
std::map <std::string, double> params; // errors
while ( paramFile >> key >> value ) {
    params[key] = value; // input them into the map
}



std::vector<double> Result_data;//[strain_data.size()];
T obj = 0.0;
for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{

double result_at_strain = (x[0]+params["k_h_over_rootl"]+(x[1]*pow(strain_data[i],x[2])))+(x[3]*std::sqrt(strain_data[i])*std::exp(-(x[4]-(x[5]*(std::log(strain_rate_data[i]/params["e0dot"]))))*Temp_data[i]));
Result_data.push_back(result_at_strain);

//std::cout<<i<<"\t"<<strain_data[i]<<"\t"<<Result_data[i]<<std::endl;

obj+=pow(Result_data[i]-stress_data[i],2.0);
}
//std::cout<<obj<<std::endl;

//Minimise difference so needs to be -ve

     // T obj = (pow(x[0],2)-(x[0]*x[1]) +x[2]);
      return {-sqrt(obj/strain_data.size())};

   }

         static std::vector<T> ObjectiveZA_GENERAL(const std::vector<T>& x)
   {

//read();
std::vector<double> strain_rate_data;
std::vector<double> Temp_data;
std::vector<double> strain_data;
std::vector<double> stress_data;


  //std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    double strain_dot,Tstar,pl_strain,stress;
    while (myfile >> strain_dot >> Tstar >> pl_strain >> stress)
    {
       //std::cout << pl_strain<<std::endl;
     // std::cout << line << '\n';
      strain_rate_data.push_back(strain_dot);
      Temp_data.push_back(Tstar);
      strain_data.push_back(pl_strain);
      stress_data.push_back(stress);

    }
    myfile.close();
  }
  else std::cout << "Unable to open file";


    const char *fileName="Var.txt";
    std::ifstream paramFile;
    paramFile.open(fileName);
    std::string line;
    std::string key;
    double value;
std::map <std::string, double> params; // errors
while ( paramFile >> key >> value ) {
    params[key] = value; // input them into the map
}


std::vector<double> Result_data;//[strain_data.size()];
T obj = 0.0;
for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{

double result_at_strain = (x[0]+params["k_h_over_rootl"]+(x[1]*pow(strain_data[i],x[2])))+(x[3]*std::exp(-(x[4]-(x[5]*(std::log(strain_rate_data[i]/params["e0dot"]))))*Temp_data[i]))
                                                                                +(x[6]*std::sqrt(strain_data[i])*std::exp(-(x[7]-(x[8]*(std::log(strain_rate_data[i]/params["e0dot"]))))*Temp_data[i]));
Result_data.push_back(result_at_strain);

//std::cout<<i<<"\t"<<strain_data[i]<<"\t"<<Result_data[i]<<std::endl;

obj+=pow(Result_data[i]-stress_data[i],2.0);
}
//std::cout<<obj<<std::endl;

//Minimise difference so needs to be -ve

     // T obj = (pow(x[0],2)-(x[0]*x[1]) +x[2]);
      return {-sqrt(obj/strain_data.size())};

   }

};


int main()
{




    const char *fileName="Var.txt";
    std::ifstream paramFile;
    paramFile.open(fileName);
    std::string line;
    std::string key;
    double value;
std::map <std::string, double> params; // errors
while ( paramFile >> key >> value ) {
    params[key] = value; // input them into the map
}

//std::cout<<params["A"]<<std::endl;
std::cout<<params["Bmax"]<<std::endl;

//exit(0);


   galgo::Parameter<double> A({params["Amin"],params["Amax"],params["Aguess"]});//par1({0.0,1.0,1});//last parameter is initial guess
   galgo::Parameter<double> B({params["Bmin"],params["Bmax"],params["Bguess"]});
   galgo::Parameter<double> n({params["nmin"],params["nmax"],params["nguess"]});
   galgo::Parameter<double> C({params["Cmin"],params["Cmax"],params["Cguess"]});
   galgo::Parameter<double> m({params["mmin"],params["mmax"],params["mguess"]});



   // initiliazing genetic algorithm
   galgo::GeneticAlgorithm<double> ga(MyObjective<double>::ObjectiveJC,params["Population_Size"],params["N_Generations"],true,A,B,n,C,m);



  //ga.mutrate=0.01;
 // ga.covrate=0.5;
  //ga.precision=25;
  //ga.Selection=RSP;
   // ga.Selection=TNT;
    //ga.genstep=1;
   // ga.CrossOver=UXO;


   // running genetic algorithm
   ga.run();


   galgo::Parameter<double> sigma_g({params["sigma_gmin"],params["sigma_gmax"],params["sigma_gguess"]});
   galgo::Parameter<double> K({params["Kmin"],params["Kmax"],params["Kguess"]});
   galgo::Parameter<double> n_ZA({params["n_ZAmin"],params["n_ZAmax"],params["n_ZAguess"]});
   galgo::Parameter<double> B_ZA({params["B_ZAmin"],params["B_ZAmax"],params["B_ZAguess"]});
   galgo::Parameter<double> beta_0({params["beta_0min"],params["beta_0max"],params["beta_0guess"]});
   galgo::Parameter<double> beta_1({params["beta_1min"],params["beta_1max"],params["beta_1guess"]});

   galgo::Parameter<double> B_0_ZA({params["B_0_ZAmin"],params["B_0_ZAmax"],params["B_0_ZAguess"]});
   galgo::Parameter<double> alpha_0({params["alpha_0min"],params["alpha_0max"],params["alpha_0guess"]});
   galgo::Parameter<double> alpha_1({params["alpha_1min"],params["alpha_1max"],params["alpha_1guess"]});





    galgo::GeneticAlgorithm<double> ga_ZA_BCC(MyObjective<double>::ObjectiveZA_BCC,params["Population_Size"],params["N_Generations"],true,sigma_g,K,n_ZA,B_ZA,beta_0,beta_1);

    ga_ZA_BCC.run();



    galgo::GeneticAlgorithm<double> ga_ZA_FCC(MyObjective<double>::ObjectiveZA_FCC,params["Population_Size"],params["N_Generations"],true,sigma_g,K,n_ZA,B_0_ZA,alpha_0,alpha_1);

    ga_ZA_FCC.run();



    galgo::GeneticAlgorithm<double> ga_ZA_General(MyObjective<double>::ObjectiveZA_GENERAL,params["Population_Size"],params["N_Generations"],true,sigma_g,K,n_ZA,B_ZA,beta_0,beta_1,B_0_ZA,alpha_0,alpha_1);

    ga_ZA_General.run();

 /*

   //read();
std::vector<double> strain_rate_data;
std::vector<double> Temp_data;
std::vector<double> strain_data;
std::vector<double> stress_data;

std::vector<double> stress_predicted;

  //std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    double strain_dot,Tstar,pl_strain,stress;
    while (myfile >> strain_dot >> Tstar >> pl_strain >> stress)
    {
       //std::cout << pl_strain<<std::endl;
      //std::cout << line << '\n';
      strain_rate_data.push_back(strain_dot);
      Temp_data.push_back(Tstar);
      strain_data.push_back(pl_strain);
      stress_data.push_back(stress);

    }
    myfile.close();
  }
  else std::cout << "Unable to open file";


   std::vector<double> JC_fitted = ga.result()->getParam();
   //<<std::endl;


  //  double eps_star = 1000.0;//normalised strain rate
  //  double T_star = 0.53988;


double RMS_error=0.0;

   for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{

 double Flow_Stress_JC = (JC_fitted[0]+(JC_fitted[1]*pow(strain_data[i],JC_fitted[2])))*(1.0+(JC_fitted[3]*std::log(strain_rate_data[i])))*(1.0-pow(Temp_data[i],JC_fitted[4]));
 stress_predicted.push_back(Flow_Stress_JC) ;

    RMS_error +=pow(stress_predicted[i]-stress_data[i],2.0);
}

RMS_error=sqrt(RMS_error/strain_data.size());

std::cout<<"RMS error on Fit = "<<RMS_error<<std::endl;

//std::cout<<strain_data.size()<<std::endl;
//std::cout<<stress_data.size()<<std::endl;
//std::cout<<stress_predicted.size()<<std::endl;

  std::ofstream Output_Results;
  Output_Results.open ("Results.txt");
  //Output_Results << "Writing this to a file.\n";

Output_Results<<"Johnson-Cook Parameters for this data are:"<<std::endl;
Output_Results<<"A: "<<JC_fitted[0]<<std::endl;
Output_Results<<"B: "<<JC_fitted[1]<<std::endl;
Output_Results<<"n: "<<JC_fitted[2]<<std::endl;
Output_Results<<"C: "<<JC_fitted[3]<<std::endl;
Output_Results<<"m: "<<JC_fitted[4]<<std::endl;
Output_Results<<"Input Data vs mpredicted data using calibrated JC parameters:"<<std::endl;

Output_Results<<"strain_data[i]"<<"\t"<<"stress_data[i]"<<"\t"<<"stress_predicted[i]"<<std::endl;
for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{
Output_Results<<strain_data[i]<<"\t"<<stress_data[i]<<"\t"<<stress_predicted[i]<<std::endl;
std::cout<<strain_data[i]<<"\t"<<stress_data[i]<<"\t"<<stress_predicted[i]<<std::endl;
}

Output_Results.close();
*/


}
