#include "TGFSteppingAction.hh"


TGFSteppingAction::TGFSteppingAction(TGFEventAction* eventAction)
{
	fEventAction = eventAction;
}

TGFSteppingAction::~TGFSteppingAction()
{}

void TGFSteppingAction::UserSteppingAction(const G4Step *aStep)
{
	G4Track* track = aStep->GetTrack();
	


	const G4ParticleDefinition* particleDefinition = track->GetParticleDefinition();
	const G4String& particlename = particleDefinition->GetParticleName();	

	G4double pdgcharge = particleDefinition->GetPDGCharge();
	G4int pdg = particleDefinition->GetPDGEncoding();

	G4int CurrentStepNumber = track->GetCurrentStepNumber();
	G4int track_id = track->GetTrackID();
	G4double globalTime = track->GetGlobalTime();

	const G4DynamicParticle* dParticle = track->GetDynamicParticle();
	//G4double depositEnergy = aStep->GetTotalEnergyDeposit();
	G4double kinEnergy = dParticle->GetKineticEnergy();
	G4double Energy = dParticle->GetTotalEnergy();

	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector positionParticle = preStepPoint->GetPosition();


/*	if (track_id != 1)
	{
		track->SetTrackStatus(fStopAndKill);
		return;

	}
*/

	if ((kinEnergy/eV) <= 100.)   //(kinEnergy/eV) <= 100. || globalTime/ microsecond >= 100.  
	{
		track->SetTrackStatus(fStopAndKill);
		return;

	}

	if (CurrentStepNumber == 1)  // CurrentStepNumber == 1   track_id == 1
	{	
		fEventAction->AddCount();
		//G4cout<< "positionParticle: " << positionParticle[2]/m << ", globalTime  =  "<< globalTime/ microsecond << "	, CurrentStepNumber: " << CurrentStepNumber << ", name: " << particlename << ", id: " << track_id << G4endl;
		//G4cout <<"	kinEnergy		= "<< kinEnergy << "		total Energy     =   "<< Energy  << G4endl;
	}

	if(pdg == 11)
	{
		fEventAction->fparticle_info[0].push_back(kinEnergy / MeV);
		fEventAction->fparticle_info[1].push_back(positionParticle[0]);
		fEventAction->fparticle_info[2].push_back(positionParticle[1]);
		fEventAction->fparticle_info[3].push_back(positionParticle[2]);
		fEventAction->fparticle_info[4].push_back(globalTime / microsecond);
	}

}



