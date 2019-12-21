#define DATA_SIZE 4096
#define BUFFER_SIZE 1024

extern "C"{

  void vadd(
              const unsigned int* vect1, //input read-only pointer
              const unsigned int* vect2, //input read-only pointer
              unsigned int* out_res, //output result read-only pointer
              int size //scalar factor
            )
            {
              //definiton of pragmas for kernel to acces the data from global memory
              #pragma HLS INTERFACE m_axi port=vect1 offset=slave bundle=gmem
              #pragma HLS INTERFACE m_axi port=vect2 offset=slave bundle=gmem
              #pragma HLS INTERFACE m_axi port=out_res offset=slave bundle=gmem

              #pragma HLS INTERFACE s_axilite port=return bundle=control
              #pragma HLS INTERFACE s_axilite port=vect1 bundle=control
              #pragma HLS INTERFACE s_axilite port=vect2 bundle=control
              #pragma HLS INTERFACE s_axilite port=out_res bundle=control
              #pragma HLS INTERFACE s_axilite port=size bundle=control


              //storing in local memory
              unsigned int vect1_buff[BUFFER_SIZE]; //to store vect1 in local_mem
              unsigned int vect2_buff[BUFFER_SIZE]; //to store vect2 in local_mem
              unsigned int vout_buff[BUFFER_SIZE]; //to store out_res in local_mem

              //transfering data in chunks

              for (int i = 0; i < size; i+=BUFFER_SIZE) {
                /* code */
                int chunk_size = BUFFER_SIZE;
                //checking boundaries
                if((i+BUFFER_SIZE)>size)
                chunk_size=size-i;

                read1: for (int j = 0; j < chunk_size; j++) {
                  /* code */
                  vect1_buff[j]=vect1[i+j];
                }
                read2: for (int j = 0; j < chunk_size; j++) {
                  /* code */
                  vect2_buff[j]=vect2[i+j];
                }
                vadd: for (int j = 0; j < chunk_size; j++) {
                  /* code */
                  vout_buff[j]=vect1_buff[j]+vect2_buff[j];
                }
                write:for (int j = 0; j < chunk_size; j++) {
                  /* code */
                  out_res[i+j]=vout_buff[j];
                }
              }

            }
}
