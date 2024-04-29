#ifndef _ADDER_H_
#define _ADDER_H_
#define SC_INCLUDE_FX
#include <iostream>
using namespace std;

#include <systemc>
using namespace sc_dt;
using namespace sc_core;

//const int WIDTH = 2;

class adder : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<sc_fixed<11,2,SC_RND,SC_SAT> > i_a_port;
  //sc_fifo_in<sc_fixed<11,2,SC_RND,SC_SAT> > i_b_port;
  sc_fifo_out<sc_fixed<11,2,SC_RND,SC_SAT> > o_sum_port;

  void do_add() {
    const float FIR[9]={
      -0.00006,-0.01265,0.02011,0.50403,0.97714,0.50403,0.02011,-0.01265,-0.00006
    };
    
    int filled_elements=0;
    while (true) {
      
      for(int i = 8 ; i > 0 ; i--){
        buffer_gray[i]=buffer_gray[i-1];
      }

      buffer_gray[0] = i_a_port.read();
      wait();
      filled_elements = std::min(filled_elements + 1, 9);
      bool buffer_full = (filled_elements == 9);

      float k = 0;
      _o_sum = 0;
      if(buffer_full){
        for(int j = 0 ; j < 9 ; ++j){
          k += buffer_gray[8-j]*FIR[j];
          //cout << "buffer_gray["<<j<<"]"<<"*FIR[" <<j<<"]: "<<buffer_gray[j] << "*" << FIR[j] <<endl;
          _o_sum += buffer_gray[8-j]*FIR[j];
        }
        o_sum_port.write(_o_sum);
        //cout << "value: " << k << endl;
        //i++;
        //cout<< i <<endl;
        filled_elements=8;
        wait();
      }
      else{
        wait();
        //i++;
        //cout << i << endl;
      }
      
    }
  }

  SC_HAS_PROCESS(adder);
  adder(sc_module_name name, int i) : id(i) { 
    SC_THREAD(do_add);  
    sensitive << i_clk.pos();
    dont_initialize();
    for(int k=0;k<9;k++){
      buffer_gray[k]=0;
    }
  }

  sc_fixed<11,2,SC_RND,SC_SAT> i_a() { return _i_a; }
  //sc_uint<WIDTH> i_b() { return _i_b; }
  sc_fixed<11,2,SC_RND,SC_SAT> o_sum() { return _o_sum; }

private:
  const int id;
  sc_fixed<11,2,SC_RND,SC_SAT> _i_a;
  //sc_uint<WIDTH> _i_b;
  sc_fixed<11,2,SC_RND,SC_SAT> _o_sum;
  float buffer_gray[9];

 
};

#endif
