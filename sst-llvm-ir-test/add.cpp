// #pragma sst offload
__attribute__((annotate("sst-offload")))
float add(float a, float b){return a + b;}
