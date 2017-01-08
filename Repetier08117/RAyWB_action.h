#ifndef RAyWB_action_h
#define RAyWB_action_h


/*Eperimente mit UI funktionen*/

   
     
        case UI_ACTION_X_UP001:
        case UI_ACTION_X_DOWN001:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP001) ? 1.0 : -1.0) * (Printer::axisStepsPerMM[X_AXIS]/100), 0, 0, 0, JOGRATE, false,false);
            break;
 
        case UI_ACTION_X_UP01:
        case UI_ACTION_X_DOWN01:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP01) ? 1.0 : -1.0) * (Printer::axisStepsPerMM[X_AXIS]/10), 0, 0, 0, JOGRATE, false,false);
            break;    
      
        case UI_ACTION_X_UP1:
        case UI_ACTION_X_DOWN1:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP1) ? 1.0 : -1.0) * Printer::axisStepsPerMM[X_AXIS], 0, 0, 0, JOGRATE, false,false);
            break;
       
        case UI_ACTION_X_UP10:
        case UI_ACTION_X_DOWN10:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP10) ? 1.0 : -1.0) * (Printer::axisStepsPerMM[X_AXIS]*10), 0, 0, 0, JOGRATE, false,false);
            break;
              
        case UI_ACTION_Y_UP001:
        case UI_ACTION_Y_DOWN001:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP001) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS]/100, 0, 0, JOGRATE, false,false);
            break;
            
        case UI_ACTION_Y_UP01:
        case UI_ACTION_Y_DOWN01:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP01) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS]/10, 0, 0, JOGRATE, false,false);
            break;
            
        case UI_ACTION_Y_UP1:
        case UI_ACTION_Y_DOWN1:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP1) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS], 0, 0, JOGRATE, false,false);
            break;
            
        case UI_ACTION_Y_UP10:
        case UI_ACTION_Y_DOWN10:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP10) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS]*10, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveY manual")); 
            break;
                     
        case UI_ACTION_Z_UP001:
        case UI_ACTION_Z_DOWN001:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, 0, ((action == UI_ACTION_Z_UP001) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Z_AXIS]/100, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveZ manual")); 
            break;
            
        case UI_ACTION_Z_UP01:
        case UI_ACTION_Z_DOWN01:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, 0, ((action == UI_ACTION_Z_UP01) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Z_AXIS]/10, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveZ manual"));           
            break;
            
        case UI_ACTION_Z_UP1:
        case UI_ACTION_Z_DOWN1:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, 0, ((action == UI_ACTION_Z_UP1) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Z_AXIS], 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveZ manual"));           
            break;
     
        case UI_ACTION_X_ZERO:
            if(!allowMoves) return UI_ACTION_X_ZERO;
            Printer::coordinateOffset[X_AXIS] -= Printer::currentPosition[X_AXIS];
            break;
            
        case UI_ACTION_Y_ZERO:
            if(!allowMoves) return UI_ACTION_Y_ZERO;
            Printer::coordinateOffset[Y_AXIS] -= Printer::currentPosition[Y_AXIS];
            break;
            
        case UI_ACTION_Z_ZERO:
            if(!allowMoves) return UI_ACTION_Z_ZERO;
            Printer::coordinateOffset[Z_AXIS] -= Printer::currentPosition[Z_AXIS];
            break;

       case UI_ACTION_Z_PROBE:
            if(!allowMoves) return UI_ACTION_Z_PROBE;
            UI_STATUS_UPD_F(Com::translatedF(UI_TEXT_Z_PROBE_ID));
            GCode::executeFString(PSTR("G29 S2\n"));        
            break;

         
#endif

