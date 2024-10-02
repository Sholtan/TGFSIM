#include <iostream>

#include "G4MTRunManager.hh"
//#include "G4RunManager.hh"


#include "G4UImanager.hh"
#include"G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"


#include "TGFDetectorConstruction.hh"
#include "TGFActionInitialization.hh"
#include <QGSP_BERT_HP.hh>

//#include "Randomize.hh"


int main(int argc, char** argv)
{
    if (argc != 5)
    {
        G4cout << G4endl << G4endl  << G4endl << "ERROR, MISSING ARGUMENTS! PROVIDE PRIMARY PARTICLE ENERGY AS FIRST VALUE AND FIELD VALUE ALONG Z AXIS AS 2ND VALUE, INNER SOLID ANGLE AS 3RD VALUE AND OUTTER SOLID ANGLE AS 4TH VALUE " << G4endl << G4endl << G4endl << G4endl;
        return 1;
    }

    G4cout << G4endl<< "Energy = " << argv[1]<<", Field value = "<< argv[2]<<", Inner Solid Angle = "<< argv[3]<<", Outer Solid Angle = "<<argv[4]<< G4endl;


    G4double PrimaryParticleEnergy = atof(argv[1]);
    G4double z_field_value_negative = atof(argv[2]);
    G4double InnerAngle = atof(argv[3]);
    G4double OuterAngle = atof(argv[4]);

    G4MTRunManager* runManager = new G4MTRunManager();     // Multithreaded mode
    //G4RunManager* runManager = new G4RunManager();     //  Single thread mode

    TGFDetectorConstruction *detectorConstruction = new TGFDetectorConstruction();
    
    G4ThreeVector fieldVector(0.0, 0.0, -1 * z_field_value_negative*kilovolt/cm);      // multiplied by -1 so that in field +1.5 kv/cm electrons are accelerated up
    detectorConstruction->SetFieldVector(fieldVector);

    runManager->SetUserInitialization(detectorConstruction);
    runManager->SetUserInitialization(new QGSP_BERT_HP(0));   // ARGUMENT IS VERBOSE LEVEL

    TGFActionInitialization *actionInitialization = new TGFActionInitialization();
    actionInitialization->SetPrimaryParticleEnergy(PrimaryParticleEnergy);
    actionInitialization->SetAngles(InnerAngle, OuterAngle);
    runManager->SetUserInitialization(actionInitialization);




    runManager->SetNumberOfThreads(4);

    G4cout << G4endl << G4endl << "NUMBER THREADS: " << runManager->GetNumberOfThreads() << G4endl<< G4endl;

    runManager->Initialize();


    //executing run.mac
    
    G4UImanager* UI = G4UImanager::GetUIpointer();
    
    UI->ApplyCommand("/control/execute run.mac");
    
    //visualization
    //-----------------------------   
    /*
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 0 1 -1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/add/axes 0 0 100 100 m");

    ui->SessionStart();
    delete ui;
    delete visManager;
    //-----------------------------   
    */
    
    delete runManager;

    return 0;
}