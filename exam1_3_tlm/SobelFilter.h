#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "tlm"
#include "tlm_utils/simple_target_socket.h"

#include "filter_def.h"

class SobelFilter : public sc_module {
public:
  tlm_utils::simple_target_socket<SobelFilter> t_skt;

  //sc_fifo<float> i_r;
  //sc_fifo<unsigned char> i_g;
  //sc_fifo<unsigned char> i_b;
  sc_fifo<float> my_float_fifo;
  sc_fifo<float> o_result;

  SC_HAS_PROCESS(SobelFilter);
  SobelFilter(sc_module_name n);
  ~SobelFilter() = default;

private:
  void do_filter();
  float buffer_gray[9];

  unsigned int base_offset;
  void blocking_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay);
};
#endif
