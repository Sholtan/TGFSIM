#include "TGFEventAction.hh"

TGFEventAction::TGFEventAction(TGFRunAction*)
{
    felectron_info = { {0, {}}, {1, {}}, {2, {}},{3, {}}, {4, {}}, {5, {}}};
    fpositron_info = { {0, {}}, {1, {}}, {2, {}},{3, {}}, {4, {}}, {5, {}}};
    fphoton_info = { {0, {}}, {1, {}}, {2, {}},{3, {}}, {4, {}}, {5, {}}};
}
TGFEventAction::~TGFEventAction()
{}

void TGFEventAction::BeginOfEventAction(const G4Event* anEvent)
{
//-------------------------------------------
    G4cout << "************** TGFEventAction::BeginOfEventAction" << G4endl;
    TGFEventInformation *eventInformation = (TGFEventInformation*)anEvent->GetUserInformation();
    fPrimaryMomentumVector = eventInformation->GetPrimaryMomentumVector();

    G4cout << "************** from TGFEventAction::BeginOfEventAction mom: " << fPrimaryMomentumVector << G4endl;
    //G4cout << "************** from TGFEventAction::BeginOfEventAction mom   0: " << fPrimaryMomentumVector[0] << G4endl;
    //G4cout << "************** from TGFEventAction::BeginOfEventAction mom   1: " << fPrimaryMomentumVector[1] << G4endl;

//-------------------------------------------

    fCount =0;
    felectron_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, {5, {}}};
    fpositron_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, {5, {}}};
    fphoton_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, {5, {}}};
}

void TGFEventAction::EndOfEventAction(const G4Event* ev)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, 0, fCount);
    man->FillNtupleIColumn(0, 1, fCount>10000);
    man->AddNtupleRow(0);

    
    int electron_info_size = felectron_info[0].size();
    int positron_info_size = fpositron_info[0].size();
    int photon_info_size = fphoton_info[0].size();

    for (G4int i = 0; i < electron_info_size; i++)
    {
        man->FillNtupleDColumn(1, 0, felectron_info[0][i]);
        man->FillNtupleDColumn(1, 1, felectron_info[1][i]); //X
        man->FillNtupleDColumn(1, 2, felectron_info[2][i]); //Y
        man->FillNtupleDColumn(1, 3, felectron_info[3][i]); //Z
        man->FillNtupleDColumn(1, 4, felectron_info[4][i]);
        man->AddNtupleRow(1);
    }

    for (G4int i = 0; i < positron_info_size; i++)
    {
        man->FillNtupleDColumn(2, 0, fpositron_info[0][i]);
        man->FillNtupleDColumn(2, 1, fpositron_info[1][i]); //X
        man->FillNtupleDColumn(2, 2, fpositron_info[2][i]); //Y
        man->FillNtupleDColumn(2, 3, fpositron_info[3][i]); //Z
        man->FillNtupleDColumn(2, 4, fpositron_info[4][i]);
        man->AddNtupleRow(2);
    }

    for (G4int i = 0; i < photon_info_size; i++)
    {
        man->FillNtupleDColumn(3, 0, fphoton_info[0][i]);
        man->FillNtupleDColumn(3, 1, fphoton_info[1][i]); //X
        man->FillNtupleDColumn(3, 2, fphoton_info[2][i]); //Y
        man->FillNtupleDColumn(3, 3, fphoton_info[3][i]); //Z
        man->FillNtupleDColumn(3, 4, fphoton_info[4][i]);
        man->AddNtupleRow(3);       
    }


    
   


    G4int n_event = ev->GetEventID();
    G4cout << "n_event    =   "<< n_event <<G4endl;
}


