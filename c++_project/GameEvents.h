//
// Created by Lucas_Ulibarri2 on 4/10/2024.
//

#ifndef CSI1430_THE_BYTE_BRIGADE__GAMEEVENTS_H
#define CSI1430_THE_BYTE_BRIGADE__GAMEEVENTS_H


class GameEvents {
public:
    GameEvents();                   // Constructor
    void underpopulationRule();     // Rule for underpopulation
    void overpopulationRule();      // Rule for overpopulation
    void reproductionRule();        // Rule for reproduction
    void nextGenerationRule();      // Rule for next generation

};


#endif //CSI1430_THE_BYTE_BRIGADE__GAMEEVENTS_H
