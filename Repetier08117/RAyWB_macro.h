#ifndef RAyWB_macro_h
#define RAyWB_macro_h


/*Eperimente mit macro funktionen*/


#define HomeX   "G28 x\nM117 Home X " 
#define HomeY   "G28 y\nM117 Home Y " 
#define HomeZ   "G28 z\nM117 Home Z "  
#define HomeAll "G28 \nM117 Home All"  
#define ZeroX   "G92 x0\nM117 Reset X coord "
#define ZeroY   "G92 y0\nM117 Reset Y coord "
#define ZeroZ   "G92 z0\nM117 Reset Z coord "
#define ZProbe  "G30 \nM117 Z-Probe "
#define Clear   GCode::executeFString(PSTR("M117                       "))

#endif //RAyWB_macro_h

