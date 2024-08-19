#include "TGFEventAction.hh"

TGFEventAction::TGFEventAction(TGFRunAction*)
{
    fparticle_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, };
}
TGFEventAction::~TGFEventAction()
{}

void TGFEventAction::BeginOfEventAction(const G4Event*)
{
	fCount =0;
    fparticle_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, };
}

void TGFEventAction::EndOfEventAction(const G4Event* ev)
{
	G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, 0, fCount);
    man->FillNtupleIColumn(0, 1, fCount>10000);
	man->AddNtupleRow(0);

    int particle_info_size = fparticle_info[0].size();
    for (G4int i = 0; i < particle_info_size; i++)
    {
        man->FillNtupleDColumn(1, 0, fparticle_info[0][i]);
        man->FillNtupleDColumn(1, 1, fparticle_info[1][i]);
        man->FillNtupleDColumn(1, 2, fparticle_info[2][i]);
        man->FillNtupleDColumn(1, 3, fparticle_info[3][i]);
        man->FillNtupleDColumn(1, 4, fparticle_info[4][i]);
        man->AddNtupleRow(1);
    }


    G4int n_event = ev->GetEventID();
    G4cout << "n_event    =   "<< n_event <<G4endl;
}



