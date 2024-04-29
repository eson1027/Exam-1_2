#ifndef _STIM_H_
#define _STIM_H_

#include <iomanip>
using std::setw;
#include "adder.h"

// WIDTH is defined in adder.h
//const int DEPTH = (1 << WIDTH);

SC_MODULE(stim) {

  sc_in_clk i_clk;
  sc_out<bool> o_rst;
  sc_fifo_out<sc_fixed<11,2,SC_RND,SC_SAT> > o_a;
  //sc_fifo_out<sc_fixed<11,2,SC_RND,SC_SAT> > o_b;
  sc_fifo_in<sc_fixed<11,2,SC_RND,SC_SAT> > i_sum;
  //Store the previous inputs to FIFOs
  sc_fixed<11,2,SC_RND,SC_SAT> t_k;
  //sc_fixed<11,2,SC_RND,SC_SAT> t_b;
  sc_fixed<11,2,SC_RND,SC_SAT> t_sum;
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
  
  
  void stim_gen() {
    cout << setw(12) << "time" << setw(12) << "a" << endl;
    // for (int a = 0; a < DEPTH; a++) {
    //   for (int b = 0; b < DEPTH; b++) {
    //     o_a.write(a);
    //     o_b.write(b);
    //     t_a=a;
    //     t_b=b;
    //     cout << setw(12) << sc_time_stamp();
    //     cout << setw(12) << t_a.to_string(SC_BIN);
    //     cout << setw(12) << t_b.to_string(SC_BIN) << endl;
    //     wait();
    //   }
    // }

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
        o_a.write(k);
        t_k = k;
        cout << setw(12) << sc_time_stamp();
        cout << setw(12) << "Input data: " << t_k.to_string(SC_DEC)<<endl;
        wait();
      }
      //wait();

  }

  void sink() {
    int i=1;
    cout << setw(12) << "time" << setw(12) << "sum" << endl;
    while (true) {
      t_sum=i_sum.read();
      cout << setw(12) << sc_time_stamp();
      cout << setw(12) << "value "<< i << ": "<< setw(12) << t_sum.to_string(SC_DEC) << endl;
      i++;
      wait();
    }
  }

  // void monitor() {
  //   cout << setw(12) << "time" << setw(12) << "a" << setw(12) << "b" << setw(12)
  //        << "sum" << endl;
  //   while (true) {
  //     wait();
  //     cout << setw(12) << sc_time_stamp();
  //     cout << setw(12) << t_a.to_string(SC_BIN);
  //     cout << setw(12) << t_b.to_string(SC_BIN);
  //     cout << setw(12) << t_sum.to_string(SC_BIN) << endl;
  //     cout << "======================================================" << endl;
  //   }
  // }

  SC_CTOR(stim) {
    SC_THREAD(stim_gen);
    sensitive << i_clk.pos();
    dont_initialize();

    SC_THREAD(sink);
    sensitive << i_clk.pos();
    
    //SC_THREAD(monitor);
    // sensitive << i_clk.pos();
 
  }
};

#endif
