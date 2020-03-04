class TON{
  private:
    float PARAM_FORMAT;
    float deltaTime;
    unsigned long auxMicros;
    unsigned long lastMicros;
    bool output;
    bool initializeTimer;
    bool formatting_process;
    float counterOF;
    float OF_FORMATTED;
  public:
    bool Q(){ // Output which will be true after the PRESET_TIME has gone by with IN being true.
      return output;
    }
    float ET(){ //Elapsed time;
      return deltaTime;
    }
    void TimerFormatting(String FORMAT){
          if(!formatting_process){ // This flag is to assign the scales just once.
          if (FORMAT=="Microseconds"){
            PARAM_FORMAT=1.0;
          }
          else if (FORMAT=="Miliseconds"){
            PARAM_FORMAT=1000.0;
          }
          else if (FORMAT=="Seconds"){ 
            PARAM_FORMAT=1000000.0;
          }
          else if (FORMAT=="Minutes"){ 
            PARAM_FORMAT=60000000.0;
          }
          else if (FORMAT=="Hours"){
            PARAM_FORMAT=3600000000.0;
          }
          else if (FORMAT=="Days"){
            PARAM_FORMAT=86400000000.0;
          }
          else if (FORMAT=="Months"){ //Considering 30 days period.
            PARAM_FORMAT=2592000000000.0;
          }
          else if (FORMAT=="Years"){
            PARAM_FORMAT=31104000000000.0;
          }
          OF_FORMATTED=(pow(2,32)-1)/PARAM_FORMAT; // You cannot write ((2^32)-1) That means 0 for Arduino.
          formatting_process=true;
      }
    }
    void Overflowcounter(){
        if (micros()>auxMicros){
          auxMicros=micros();
        }
        else{
          auxMicros=micros();
          counterOF=counterOF+1.0;
        }
    }
    void parameters(bool IN, float PRESET_TIME, String FORMAT){
      TimerFormatting(FORMAT);
      if (IN){
          if (!initializeTimer){
              initializeTimer=true;
              lastMicros=micros();
          }
          if (initializeTimer){
            Overflowcounter();
            if ((counterOF==0)&&(lastMicros<micros())){
              deltaTime=(float(micros()-lastMicros)/PARAM_FORMAT);
            }
            if ((counterOF>0)&&(lastMicros<micros())){
              deltaTime=counterOF*OF_FORMATTED+(float(micros())/PARAM_FORMAT);
            }
            if (deltaTime>=PRESET_TIME){
                  output=true;
            }
          }
            
      }
      else{
        initializeTimer=false;
        output=false;
        counterOF=0;
        deltaTime=0;
        auxMicros=0;
      }
   }
};
