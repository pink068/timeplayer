class RadioControl
{
  public: 
    int Initialise(void);
    int Transmit(void);
    int Receive(void);
    int Command( int command, char * value);
    int Close(void);
};

#define RADIO_FREQ 1
#define RADIO_POWER 2

