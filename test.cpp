#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <omp.h>
#include <fftw3.h>
#include "fielddata.hpp"

int main(int argc, char **argv){
    std::string FileName = argv[1];

    int ng(2000);
    double boxsize(4000.);

    fftwf_init_threads();
    fftwf_plan_with_nthreads(omp_get_max_threads());
    std::cout << omp_get_max_threads() << " threads will be used in FFT." << std::endl;
    //fftwf_import_wisdom_from_filename(wisdom_file.c_str());

    FieldData overdensity(ng,boxsize,false);
    overdensity.load(FileName);
    overdensity.put_window_order(2); // Matter overdensity field based on CIC interpolation
    //fftwf_export_wisdom_to_filename(wisdom_file.c_str());
    std::cout << "File loaded successfully." << std::endl;

    overdensity.do_fft();
    overdensity.deconvolve(); // Comment this out when power spectra are computed.
    // overdensity.apply_filter(ここは自分で好きな数値とフィルターの種類を入れる);
    overdensity.do_ifft();

/*
    for(int i=0;i<ng;i++)
        for(int j=0;j<ng;j++)
            for(int k=0;k<ng;k++){
                // ここに処理を書く。
            }
*/
    exit(0);
}
