



#include <Rcpp.h>
#include "child_weight.h"

// [[Rcpp::export]]
List child_weight_wrapper(NumericVector age, NumericVector sex, NumericVector FFM, NumericVector FM, NumericMatrix input_EIntake, double days, double dt, bool checkValues){
    
    //Create new adult with characteristics
    Child Person (age,  sex, FFM, FM, input_EIntake, dt, checkValues);
    
    //Run model using RK4
    return Person.rk4(days - 1); //days - 1 to account for extra day (c++ indexing starts in 0; R in 1)
    
}

// [[Rcpp::export]]
List child_weight_wrapper_richardson(NumericVector age, NumericVector sex, NumericVector FFM, NumericVector FM, double K, double Q, double A, double B, double nu, double C, double days, double dt, bool checkValues){
    
    //Create new adult with characteristics
    Child Person (age,  sex, FFM, FM, K, Q, A, B, nu, C, dt, checkValues);
    
    //Run model using RK4
    return Person.rk4(days - 1); //days - 1 to account for extra day (c++ indexing starts in 0; R in 1)
    
}

// [[Rcpp::export]]
NumericMatrix intake_reference_wrapper(NumericVector age, NumericVector sex, NumericVector FFM, NumericVector FM, double days,  double dt){
    
    //Energy intake input empty matrix
    NumericMatrix EI(1,1);
    
    //Create new adult with characteristics
    Child Person (age,  sex, FFM, FM, EI, dt, false);
    
    //Energy matrix
    // NumericMatrix EnergyIntake(age.size(), floor(days/dt) + 1);
    
    //Get energy matrix
    for (double i = 0; i < floor(days/dt) + 1; i++){
        EnergyIntake(_,i) = Person.IntakeReference(age + dt*i/365.0);
    }
    
    return EnergyIntake;
    
}

// [[Rcpp::export]]
List mass_reference_wrapper(NumericVector age, NumericVector sex){
    
    //Input empty matrices
    NumericMatrix EI(1,1);
    NumericMatrix inputFM(1,1);
    NumericMatrix inputFFM(1,1);
    
    //Create new adult with characteristics
    Child Person (age,  sex, inputFFM, inputFM, EI, 1.0, false);
    
    //Energy matrix
    NumericVector FM  = Person.FMReference(age);
    NumericVector FFM = Person.FFMReference(age);
    
    return List::create(Named("FM")  = FM,
                        Named("FFM") = FFM);
    
}


