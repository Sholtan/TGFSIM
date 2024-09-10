#include "TGFEventAction.hh"

TGFEventAction::TGFEventAction(TGFRunAction*)
{
    fparticle_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, };
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
    fparticle_info = { {0, {}}, {1, {}}, {2, {}},{3, {}},{4, {}}, };
}

void TGFEventAction::EndOfEventAction(const G4Event* ev)
{
	G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, 0, fCount);
    man->FillNtupleIColumn(0, 1, fCount>10000);
	man->AddNtupleRow(0);


    double r=0;
    double z=0;
    double comp1=0; //ay*bz-az*by
    double comp2=0;   //az*bx-ax*bz
    double comp3=0;   //ax*by-ay*bx
    int particle_info_size = fparticle_info[0].size();
    for (G4int i = 0; i < particle_info_size; i++)
    {
        man->FillNtupleDColumn(1, 0, fparticle_info[0][i]);
        man->FillNtupleDColumn(1, 1, fparticle_info[1][i]); //X
        man->FillNtupleDColumn(1, 2, fparticle_info[2][i]); //Y
        man->FillNtupleDColumn(1, 3, fparticle_info[3][i]); //Z
        man->FillNtupleDColumn(1, 4, fparticle_info[4][i]);
        man->AddNtupleRow(1);


       
        //G4cout <<"  X  =   "<<   fparticle_info[1][i] <<  "         Y    = " << fparticle_info[2][i]<< "         Z   =  " <<fparticle_info[3][i] <<G4endl;
        comp1 =(fparticle_info[2][i]*fPrimaryMomentumVector[2]-fparticle_info[3][i]*fPrimaryMomentumVector[1]);
        comp2 =(fparticle_info[3][i]*fPrimaryMomentumVector[0]-fparticle_info[1][i]*fPrimaryMomentumVector[2]);
        comp3 =(fparticle_info[1][i]*fPrimaryMomentumVector[1]-fparticle_info[2][i]*fPrimaryMomentumVector[0]);
        //G4cout <<"  comp1  =   "<<   comp1 <<  "         comp2    = " << comp2<< "         comp3   =  " <<comp3 <<G4endl;
        r = sqrt(comp1*comp1+comp2*comp2+comp3*comp3);
        //G4cout <<"  r  =   "<<   r << G4endl;
        z = sqrt (fparticle_info[1][i]*fparticle_info[1][i]+fparticle_info[2][i]*fparticle_info[2][i]+fparticle_info[3][i]*fparticle_info[3][i]-r*r);
        //G4cout <<"  r  =   "<<   r << "     z  =   "<<   z << G4endl;
        man->FillNtupleDColumn(2, 0, r);
        man->FillNtupleDColumn(2, 1, z);
        man->AddNtupleRow(2);

        
    }
    //G4cout << fPrimaryMomentumVector <<G4endl;

  
   


    G4int n_event = ev->GetEventID();
    G4cout << "n_event    =   "<< n_event <<G4endl;
}



