
class Linear {
  private:
    int in
    int out

  public:
    Linear(int inp,int outp){
      in=inp;
      out=outp;
      float W[inp][out] = {};
      float b[1][out] = {};
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
    float MAX_LAYERS
    int pointer
    Linear *layers
  public:
    neuralModel(){
      MAX_LAYERS=5;
      pointer=0;
      Linear *layers[MAX_LAYERS]; //create the array to have a set maximum
    }
    void addLayer(int in,int out){
      layers[pointer]=Linear(in,out);
      pointer+=1;
    }
    
}