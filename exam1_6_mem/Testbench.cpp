#include <cassert>
#include <cstdio>
#include <cstdlib>
using namespace std;
//using std::setw;

#include "Testbench.h"

Testbench::Testbench(sc_module_name n)
    : sc_module(n), initiator("initiator") {
  SC_THREAD(do_sobel);
}

Testbench::~Testbench() = default;

const float x_input_signal[128]={0.493,  0.521,  0.56 ,  0.567,  0.591,  0.624,  0.651,  0.679,  0.68 ,  0.735,
                            0.738,  0.747,  0.787,  0.799,  0.787,  0.836,  0.855,  0.848,  0.888,  0.913,
                            0.918,  0.939,  0.946,  0.962,  0.944,  0.96 ,  0.99 ,  1.003,  1.001,  0.999,
                            1.007,  1.012,  1.017,  0.998,  1.001,  0.988,  0.988,  0.974,  0.986,  0.97 ,
                            0.974,  0.941,  0.936,  0.92 ,  0.9  ,  0.893,  0.9  ,  0.864,  0.848,  0.829,
                            0.8  ,  0.788,  0.787,  0.735,  0.711,  0.704,  0.677,  0.629,  0.642,  0.597,
                            0.584,  0.566,  0.548,  0.5  ,  0.486,  0.464,  0.444,  0.41 ,  0.395,  0.373,
                            0.354,  0.309,  0.293,  0.272,  0.259,  0.229,  0.219,  0.198,  0.19 ,  0.152,
                            0.131,  0.117,  0.091,  0.102,  0.069,  0.06 ,  0.06 ,  0.034,  0.031,  0.035,
                            0.026,  0.018,  0.004,  0.007, -0.003, -0.004,  0.002,  0.012,  0.01 ,  0.038,
                            0.002,  0.013,  0.054,  0.042,  0.036,  0.056,  0.067,  0.075,  0.09 ,  0.113,
                            0.143,  0.147,  0.166,  0.165,  0.184,  0.203,  0.213,  0.272,  0.264,  0.298,
                            0.311,  0.348,  0.369,  0.398,  0.43 ,  0.439,  0.484,  0.502};

void Testbench::do_sobel() {
  float total;
  int i=1,j=1,eww=1;
  //cout << "1" << endl;
  word data;
  unsigned char mask[4];
  //wait(5 * CLOCK_PERIOD, SC_NS);

  float k;
      for(int v = -4; v < 128+4 ; v++){
        if(v>=0 && v<128){
          k = x_input_signal[v];
        }
        else{
          k = 0;
        }
        //wait();// additional it needs to be delete
        //cout << "input_num" << k << endl;
        data.my_float=k;
        mask[0] = 0xff;
        mask[1] = 0xff;
        mask[2] = 0xff;
        mask[3] = 0xff;
        initiator.write_to_socket(SOBEL_MM_BASE + SOBEL_FILTER_R_ADDR, mask, data.uc, 4);
        //wait(1 * CLOCK_PERIOD, SC_NS);

        bool done=false;
        float output_num=0;
        while(!done){
          initiator.read_from_socket(SOBEL_MM_BASE + SOBEL_FILTER_CHECK_ADDR, mask, data.uc, 4);
          output_num = data.sint;
          if(output_num!=0) done=true;
          // cout << "j: " << j << endl;
          // j++;
        }
          // cout << "eww: " << eww << endl;
          // eww++;
        //wait(10 * CLOCK_PERIOD, SC_NS);
        initiator.read_from_socket(SOBEL_MM_BASE + SOBEL_FILTER_RESULT_ADDR, mask, data.uc, 4);
        total = data.sint;
        if(v >= 4){
          cout << "    " << "value "<< i << ": "<< "    " << total << endl;
          i++;
        }
      }
    initiator.write_to_socket(RAM_MM_BASE, mask, data.uc , 4*136);
    // initiator.write_to_socket(RAM_MM_BASE + output_rgb_raw_data_offset, mask,
    //                       target_bitmap, bytes_per_pixel * height * width);
  sc_stop();
}
