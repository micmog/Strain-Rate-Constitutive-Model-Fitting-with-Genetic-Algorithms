//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved
//=================================================================================================

#include "./src/Galgo.hpp"


#include <fstream>
#include <string>

// objective class example
template <typename T>
class MyObjective
{


//private:
public:
/*
   static void read(){
  std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << line << '\n';
    }
    myfile.close();
  }

  else std::cout << "Unable to open file";
    }
*/
   static std::vector<T> Objective(const std::vector<T>& x)
   {

//read();
std::vector<double> strain_data;
std::vector<double> stress_data;

  //std::string line;
  std::ifstream myfile ("Data.dat");
  if (myfile.is_open())
  {
    double pl_strain,stress;
    while (myfile >> pl_strain >> stress/* getline (myfile,line) */)
    {
       //std::cout << pl_strain<<std::endl;
      //std::cout << line << '\n';
      strain_data.push_back(pl_strain);
      stress_data.push_back(stress);

    }
    myfile.close();
  }
  else std::cout << "Unable to open file";

 // std::cout<<strain_data[9]<<std::endl;
 // std::cout<<stress_data[9]<<std::endl;

 double eps_star = 1000.0;//normalised strain rate
 double T_star = 0.53988;
 /*
 double A=0.35000;
 double B=0.56980;
 double n=0.37880;
 double c=0.00968;
 double m=1.26700;
*/
std::vector<double> Result_data;//[strain_data.size()];
T obj = 0.0;
for(int i=0;i<strain_data.size();i++)//assemble result array using strain data and parameters
{

double result_at_strain = (x[0]+(x[1]*pow(strain_data[i],x[2])))*(1.0+(x[3]*std::log(eps_star)))*(1.0-pow(T_star,x[4]));
Result_data.push_back(result_at_strain);

//std::cout<<i<<"\t"<<strain_data[i]<<"\t"<<Result_data[i]<<std::endl;

obj+=sqrt(pow(Result_data[i]-stress_data[i],2.0));
}
//std::cout<<obj<<std::endl;

//Minimise difference so needs to be -ve I think

     // T obj = (pow(x[0],2)-(x[0]*x[1]) +x[2]);
      return {-obj};

   }
   // NB: GALGO maximize by default so we will maximize -f(x,y)
};

// constraints example:
// 1) x * y + x - y + 1.5 <= 0
// 2) 10 - x * y <= 0
template <typename T>
std::vector<T> MyConstraint(const std::vector<T>& x)
{
   return {x[0]*x[1]+x[0]-x[1]+1.5,10-x[0]*x[1]};
}
// NB: a penalty will be applied if one of the constraints is > 0
// using the default adaptation to constraint(s) method

int main()
{
   // initializing parameters lower and upper bounds
   // an initial value can be added inside the initializer list after the upper bound

    /*
   //FOR DEBUGGING
   galgo::Parameter<double> A({0.34999999,0.3500001});//par1({0.0,1.0,1});//last parameter is initial guess
   galgo::Parameter<double> B({0.56979,0.56981});
   galgo::Parameter<double> n({0.37879,0.37881});
   galgo::Parameter<double> C({0.00967,0.00969});
   galgo::Parameter<double> m({1.26699,1.26701});
   //FOR DEBUGGING
*/

   galgo::Parameter<double> A({0,1.0,0.3});//par1({0.0,1.0,1});//last parameter is initial guess
   galgo::Parameter<double> B({0.0,1.0,0.5});
   galgo::Parameter<double> n({0.0,1.0,0.4});
   galgo::Parameter<double> C({0.0,0.01,0.008});
   galgo::Parameter<double> m({0.0,2.0,1.3});

   // here both parameter will be encoded using 16 bits the default value inside the template declaration
   // this value can be modified but has to remain between 1 and 64

   // initiliazing genetic algorithm
   galgo::GeneticAlgorithm<double> ga(MyObjective<double>::Objective,1000,5000,true,A,B,n,C,m);

   // setting constraints
  // ga.Constraint = MyConstraint;

  //ga.mutrate=0.33;
  //ga.covrate=0.5;
  //ga.precision=25;
  //ga.Selection=SUS;

   // running genetic algorithm
   ga.run();


//std::cout<<ga.result()<<std::endl;


}
