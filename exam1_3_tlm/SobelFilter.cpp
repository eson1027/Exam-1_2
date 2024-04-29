#include <cmath>
#include <iomanip>

#include "SobelFilter.h"
using namespace std;

SobelFilter::SobelFilter(sc_module_name n)
    : sc_module(n), t_skt("t_skt"), base_offset(0) {
  SC_THREAD(do_filter);
  for(int i = 0 ; i < 9; i++){
    buffer_gray[i]=0;
  }
  t_skt.register_b_transport(this, &SobelFilter::blocking_transport);
}

// sobel mask
const float FIR[9]={
      -0.00006,-0.01265,0.02011,0.50403,0.97714,0.50403,0.02011,-0.01265,-0.00006
    };

void SobelFilter::do_filter() {
  int filled_elements=9;
  while (true) {
      
      for(int i = 8 ; i > 0 ; i--){
        buffer_gray[i]=buffer_gray[i-1];
      }
      //cout<<"filled_element: "<< filled_elements<< endl;
      buffer_gray[0] = my_float_fifo.read();
      filled_elements = std::min(filled_elements + 1, 9);
      bool buffer_full = (filled_elements == 9);
      //cout << buffer_full<< endl;
      float k = 0;
      //val[0] = 0;
      if(buffer_full){
        for(int j = 0 ; j < 9 ; ++j){
          k += buffer_gray[8-j]*FIR[j];
          //cout << "buffer_gray["<<j<<"]"<<"*FIR[" <<j<<"]: "<<buffer_gray[j] << "*" << FIR[j] <<endl;
          //val[0] += buffer_gray[8-j]*FIR[j];
        }
        
        filled_elements=8;

        o_result.write(k);
        
        //cout << "test" << endl;
        //wait();
        wait(10 * CLOCK_PERIOD, SC_NS);
        
      }
      else{
      }
      
    }
}

void SobelFilter::blocking_transport(tlm::tlm_generic_payload &payload,
                                     sc_core::sc_time &delay) {
  sc_dt::uint64 addr = payload.get_address();
  addr = addr - base_offset;
  unsigned char *mask_ptr = payload.get_byte_enable_ptr();
  unsigned char *data_ptr = payload.get_data_ptr();
  word buffer;
  switch (payload.get_command()) {
  case tlm::TLM_READ_COMMAND:
    switch (addr) {
    case SOBEL_FILTER_RESULT_ADDR:
      buffer.uint = o_result.read();
      break;
    case SOBEL_FILTER_CHECK_ADDR:
      buffer.uint = o_result.num_available();
      break;
    default:
      std::cerr << "Error! SobelFilter::blocking_transport: address 0x"
                << std::setfill('0') << std::setw(8) << std::hex << addr
                << std::dec << " is not valid" << std::endl;
      break;
    }
    data_ptr[0] = buffer.uc[0];
    data_ptr[1] = buffer.uc[1];
    data_ptr[2] = buffer.uc[2];
    data_ptr[3] = buffer.uc[3];
    break;

  case tlm::TLM_WRITE_COMMAND:
    switch (addr) {
    case SOBEL_FILTER_R_ADDR:
      if (mask_ptr[0] == 0xff && mask_ptr[1] == 0xff && mask_ptr[2] == 0xff && mask_ptr[3] == 0xff) {
        buffer.uc[0] =  data_ptr[0];
        buffer.uc[1] =  data_ptr[1];
        buffer.uc[2] =  data_ptr[2];
        buffer.uc[3] =  data_ptr[3];
        my_float_fifo.write(buffer.my_float);
        //i_r.write(data_ptr[0]);
      }
      // if (mask_ptr[1] == 0xff) {
      //   i_g.write(data_ptr[1]);
      // }
      // if (mask_ptr[2] == 0xff) {
      //   i_b.write(data_ptr[2]);
      // }
      break;
    default:
      std::cerr << "Error! SobelFilter::blocking_transport: address 0x"
                << std::setfill('0') << std::setw(8) << std::hex << addr
                << std::dec << " is not valid" << std::endl;
      break;
    }
    break;

  case tlm::TLM_IGNORE_COMMAND:
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  default:
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  }
  payload.set_response_status(tlm::TLM_OK_RESPONSE); // Always OK
}
