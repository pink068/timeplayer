int ProcessFile(int );
int Playsound(int );
bool fileExists(const char* file);
int MakeTimeFile(void);
int WriteToFile(char * buffer, char * filename);
int MakeDTGFile(void);
int MakePowerFile(void);
int ProcessScript(char * filename);
int ProcessLine(char * line);
int ProcessFile(int );

int Playsound(int );
bool fileExists(const char* file);

int SayAsGroups(char *);
int Say5Numbers(void);
int Say(char * );

extern bool live_hardware ;
extern bool do_sound;
extern RadioControl Rig;
extern bool saynumbers;
extern char power[6];
