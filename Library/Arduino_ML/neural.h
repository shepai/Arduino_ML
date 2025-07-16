
class Linear {
  private:
    int in;
    int out;
    float** W;
    float* b;
  public:
    Linear(int inp,int outp){
      in=inp;
      out=outp;
      W = new float*[inp];
      for (int i = 0; i < inp; i++) {
          W[i] = new float[out];
      }
      b = new float[out];
      for(int i=0;i<inp;i++){ //populate the linear layers with random float
        for(int j=0;j<out;j++){
          W[i][j]=randomFloat(-1,1);
          if(i==0){
            b[0][j] = randomFloat(-1,1);
          }
        }
      }
    }
    float randomFloat(float minVal, float maxVal) {
      long r = random(0, 10000);  // random int from 0 to 9999
      float scaled = (float)r / 10000.0;  // [0.0, 1.0)
      return minVal + scaled * (maxVal - minVal);
    }
}

class neuralModel {
  private:
    int MAX_LAYERS;
    int pointer;
    Linear** layers;
  public:
    neuralModel(){
      MAX_LAYERS=5;
      pointer=0;
      layers = new Linear*[MAX_LAYERS]; //create the array to have a set maximum
    }
    void addLayer(int in,int out){
      layers[pointer] = new Linear(in, out);
      pointer+=1;
      if(pointer==MAX_LAYERS){ //if we add beyond default increase the total size
        Linear** temp = new Linear*[MAX_LAYERS];
        for (int i = 0; i < MAX_LAYERS; i++) {
            temp[i] = layers[i];
        }
        delete[] layers;
        MAX_LAYERS *= 2;
        layers = new Linear*[MAX_LAYERS];
        for (int i = 0; i < MAX_LAYERS / 2; i++) {
            layers[i] = temp[i];
        }
        delete[] temp;
        }
    }
    
    float** dotProduct(float** A, int A_rows, int A_cols, float** B, int B_rows, int B_cols) {
      if (A_cols != B_rows) {
        Serial.println("Incompatible dimensions for dot product");
        return nullptr;
      }

      float** result = new float*[A_rows]; 
      for (int i = 0; i < A_rows; i++) {
        result[i] = new float[B_cols];
        for (int j = 0; j < B_cols; j++) {
          result[i][j] = 0;
          for (int k = 0; k < A_cols; k++) {
            result[i][j] += A[i][k] * B[k][j];
          }
        }
      }

      return result; // reutn the resuting dot product 
} 

    float ** forward(float** inputs){
      float** x=inputs;
      for (int i=0;i<pointer;i++){
        x = dotProduct(x,i);
      }
      
    }
}